#include "ImguiAddon.h"

#include <imgui.h>

static void Update() {
	// Example ImGui content
	ImGui::Begin("Hello, Multithreading!");
	ImGui::Text("This window is running on its own thread.");
	ImGui::End();
}

int main() {

	ImguiAddon::Window window{ {1200, 800, 60, "Demo Window"}, Update};

	while (true) {
		// Main loop
	}

	return 0;
}