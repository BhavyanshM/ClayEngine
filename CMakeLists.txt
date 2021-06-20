cmake_minimum_required(VERSION 3.19)
project(ClayEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(src/ClayEngine/)
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

add_library(ClayEngine
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
        src/ClayEngine/Platforms/OpenGL/OpenGLContext.h src/ClayEngine/Renderer/Shader.h src/ClayEngine/Renderer/Shader.cpp src/ClayEngine/Renderer/Buffer.h src/ClayEngine/Renderer/Buffer.cpp src/ClayEngine/ClayHeaders.h src/ClayEngine/Platforms/OpenGL/OpenGLBuffer.cpp src/ClayEngine/Platforms/OpenGL/OpenGLBuffer.h src/ClayEngine/Platforms/OpenGL/OpenGLBuffer.cpp src/ClayEngine/Renderer/Renderer.h src/ClayEngine/Renderer/Renderer.cpp src/ClayEngine/Renderer/VertexArray.cpp src/ClayEngine/Renderer/VertexArray.h src/ClayEngine/Platforms/OpenGL/OpenGLVertexArray.cpp src/ClayEngine/Platforms/OpenGL/OpenGLVertexArray.h src/ClayEngine/Renderer/RendererAPI.cpp src/ClayEngine/Renderer/RendererAPI.h src/ClayEngine/Renderer/RenderCommand.cpp src/ClayEngine/Renderer/RenderCommand.h src/ClayEngine/Platforms/OpenGL/OpenGLRendererAPI.cpp src/ClayEngine/Platforms/OpenGL/OpenGLRendererAPI.h src/ClayEngine/Renderer/OrthographicCamera.cpp src/ClayEngine/Renderer/OrthographicCamera.h src/Example/GameSandbox.cpp src/Example/GameSandbox.h src/ClayEngine/Clay.h src/Example/ExampleLayer.cpp src/Example/ExampleLayer.h)

target_precompile_headers(ClayEngine PUBLIC src/ClayEngine/ClayHeaders.h)

target_link_libraries(ClayEngine
        ${OPENGL_LIBRARIES}
        glfw
        glad
        imgui
        glm::glm
        )

add_executable(ClayGameApp src/Example/GameSandbox.cpp src/Example/GameSandbox.h)
target_link_libraries(ClayGameApp
        ClayEngine)


