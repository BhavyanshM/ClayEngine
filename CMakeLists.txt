cmake_minimum_required(VERSION 3.16)
project(ClayEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(src/ClayEngine/)
include_directories(Vendor/spdlog/include/)
include_directories(Vendor/glfw/include/)
include_directories(Vendor/GLAD/include/)
include_directories(Vendor/ImGui/imgui/)
include_directories(Vendor/glm/glm/)
include_directories(Vendor/std_image)
include_directories(/usr/include/CL/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/GLAD)
add_subdirectory(Vendor/ImGui)
add_subdirectory(Vendor/glm)

add_subdirectory(src/ClayEngine/Core/)
add_subdirectory(src/ClayEngine/Events/)
add_subdirectory(src/ClayEngine/Renderer/)
add_subdirectory(src/ClayEngine/Platforms/)
add_subdirectory(src/ClayEngine/ImGui/)
add_subdirectory(src/ClayEngine/Scene/)
add_subdirectory(src/ClayEngine/Tools/)
add_subdirectory(src/ClayEngine/Manifolds/)

set(HEADERS
        Vendor/std_image/stb_image.h)

set(SOURCES
        ${CORE_SOURCES} ${EVENTS_SOURCES} ${RENDERER_SOURCES} ${PLATFORMS_SOURCES} ${IMGUI_SOURCES} ${SCENE_SOURCES} ${TOOLS_SOURCES}
        ${MANIFOLDS_SOURCES} Vendor/std_image/stb_image.cpp )

add_library(ClayEngine ${HEADERS} ${SOURCES})
target_include_directories(ClayEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(ClayEngine PUBLIC "Vendor/spdlog/include/")
target_include_directories(ClayEngine PUBLIC "Vendor/glfw/include/")
target_include_directories(ClayEngine PUBLIC "Vendor/GLAD/include/")
target_include_directories(ClayEngine PUBLIC "Vendor/ImGui/imgui/")
target_include_directories(ClayEngine PUBLIC "Vendor/glm/glm/")
target_include_directories(ClayEngine PUBLIC "Vendor/std_image")
target_precompile_headers(ClayEngine PUBLIC src/ClayEngine/Core/ClayHeaders.h)

target_link_libraries(ClayEngine PUBLIC
        ${OPENGL_LIBRARIES}
        glfw glad imgui glm::glm
        /usr/lib/x86_64-linux-gnu/libOpenCL.so )

if(BUILD_LOCAL)
    target_compile_definitions(ClayEngine PUBLIC -DASSETS_PATH="../src/ClayEngine/Assets/")
else()
    target_compile_definitions(ClayEngine PUBLIC -DASSETS_PATH="/usr/local/include/ClayEngine/Assets/")
endif()

message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")


message(STATUS "SOURCES: ${RENDERER_SOURCES}")

install(TARGETS ClayEngine DESTINATION lib)
install(TARGETS glad DESTINATION lib)
install(TARGETS imgui DESTINATION lib)

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine DESTINATION include FILES_MATCHING PATTERN "*.h")
INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine DESTINATION include FILES_MATCHING PATTERN "*.hpp")

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.h")
INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.hpp")
INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/Vendor DESTINATION include/ClayEngine FILES_MATCHING PATTERN "*.inl")

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/ClayEngine/Assets DESTINATION include/ClayEngine)

add_executable(ClayEditor
        src/ClayEditor/ClayEditorApp.cpp
        src/ClayEditor/ClayEditorApp.h
        src/ClayEditor/EditorLayer.cpp
        src/ClayEditor/EditorLayer.h)
target_link_libraries(ClayEditor
        ClayEngine)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "BM") #required
INCLUDE(CPack)



