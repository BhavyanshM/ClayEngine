cmake_minimum_required(VERSION 3.19)
project(ClayEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(spdlog/include/)
include_directories(glfw/include/)
include_directories(GLAD/include/)
include_directories(src/ClayEngine/)
include_directories(ImGui/imgui/)
include_directories(glm/glm/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(GLAD)
add_subdirectory(ImGui)
add_subdirectory(glm)

add_executable(ClayEngine
        src/ClayEngine/main.cpp
        src/ClayEngine/Application.cpp
        src/ClayEngine/Application.h
        src/ClayEngine/Log.cpp
        src/ClayEngine/Log.h
        src/ClayEngine/Events/Event.h
        src/ClayEngine/Events/KeyEvent.h
        src/ClayEngine/Events/MouseEvent.h
        src/ClayEngine/Events/ApplicationEvent.h
        src/ClayEngine/Window.h
        src/ClayEngine/Core.h
        src/ClayEngine/Platforms/Linux/LinuxWindow.cpp
        src/ClayEngine/Platforms/Linux/LinuxWindow.h
        src/ClayEngine/Layer.cpp
        src/ClayEngine/Layer.h
        src/ClayEngine/LayerStack.cpp
        src/ClayEngine/LayerStack.h
        src/ClayEngine/ImGui/ImGuiLayer.cpp
        src/ClayEngine/ImGui/ImGuiLayer.h
        src/ClayEngine/ImGui/ImGuiBuild.cpp
        src/ClayEngine/Input.h
        src/ClayEngine/Platforms/Linux/LinuxInput.cpp
        src/ClayEngine/Platforms/Linux/LinuxInput.h
        src/ClayEngine/KeyCodes.h
        src/ClayEngine/MouseButtonCodes.h
        src/ClayEngine/Renderer/GraphicsContext.h
        src/ClayEngine/Platforms/OpenGL/OpenGLContext.cpp
        src/ClayEngine/Platforms/OpenGL/OpenGLContext.h src/ClayEngine/Renderer/Shader.h src/ClayEngine/Renderer/Shader.cpp)

target_link_libraries(ClayEngine
        ${OPENGL_LIBRARIES}
        glfw
        glad
        imgui
        glm::glm
        )
