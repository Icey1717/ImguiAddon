#include "ImguiAddon.h"

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdexcept>
#include <iostream>
#include <thread>
#include <atomic>

namespace ImguiAddon {
	static std::thread renderThread;
	static std::atomic<bool> running{ false };
	static WindowProperties windowProperties;
	static Window::UpdateFunction updateFunction;

	void RenderLoop() {
		// Initialize GLFW
		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}

		const auto targetFrameDuration = std::chrono::milliseconds(1000 / windowProperties.targetFPS);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(windowProperties.width, windowProperties.height, windowProperties.title.c_str(), nullptr, nullptr);
		if (!window) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);  // Disable vsync

		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		running = true;

		double deltaMs = 0.0;

		// Rendering loop
		while (running && !glfwWindowShouldClose(window)) {
			const auto frameStart = std::chrono::high_resolution_clock::now();

			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			updateFunction();

			// Render the framerate counter
			if (windowProperties.showFrameTime) {
				ImGui::SetNextWindowSize(ImVec2(90.0f, 10.0f));
				ImGui::SetNextWindowPos(ImVec2(windowProperties.width - 100.0f, 10.0f), ImGuiCond_Always);
				ImGui::Begin("Framerate", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
				ImGui::Text("%.2f ms", deltaMs);
				ImGui::End();
			}

			ImGui::Render();
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);

			// Throttling
			const auto frameEnd = std::chrono::high_resolution_clock::now();
			const auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);

			// Sleep for the remaining time to meet the target frame duration
			if (frameDuration < targetFrameDuration) {
				std::this_thread::sleep_for(targetFrameDuration - frameDuration);
			}

			deltaMs = std::chrono::duration <double, std::milli>(std::chrono::high_resolution_clock::now() - frameStart).count();
		}

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

ImguiAddon::Window::Window(const WindowProperties& properties, const UpdateFunction& update) {
	if (running) {
		std::cerr << "Sorry, only one window is supported!" << std::endl;
		return;
	}

	windowProperties = properties;
	updateFunction = update;
	renderThread = std::thread(RenderLoop);
}

ImguiAddon::Window::~Window() {
	if (running) {
		running = false;
		if (renderThread.joinable()) {
			renderThread.join();
		}
	}
}