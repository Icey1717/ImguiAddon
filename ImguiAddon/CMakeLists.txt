cmake_minimum_required(VERSION 3.14)
project(ImguiAddOn VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent to pull dependencies from GitHub
include(FetchContent)

# GLFW
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

set(GLFW_USE_WAYLAND OFF CACHE BOOL "Disable Wayland support")

# ImGui
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG master  # Use "master" for stable; "docking" for docking branch
)
FetchContent_MakeAvailable(imgui)

find_package(OpenGL REQUIRED)

add_library(ImguiAddOn STATIC src/ImguiAddon.cpp)
target_include_directories(ImguiAddOn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ImguiAddOn PRIVATE glfw OpenGL::GL)

# Link ImGui with its backends
set(IMGUI_BACKEND_SOURCES
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_sources(ImguiAddOn PRIVATE ${IMGUI_BACKEND_SOURCES})

target_include_directories(ImguiAddOn PUBLIC
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
	${CMAKE_CURRENT_LIST_DIR}/include
)