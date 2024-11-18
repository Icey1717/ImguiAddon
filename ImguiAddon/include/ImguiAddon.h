#pragma once

#include <string>
#include <functional>

namespace ImguiAddon {
	struct WindowProperties {
		int width = 800;
		int height = 600;
		int targetFPS = 60;
		std::string title;
		bool showFrameTime = true;
	};

	class Window {
	public:
		using UpdateFunction = std::function<void(void)>;
		Window(const WindowProperties& properties, const UpdateFunction& update);
		~Window();
	};
}