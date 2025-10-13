cmake_minimum_required(VERSION 4.0)
project(CppSandbox)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
# --- GLFW ---
FETCHCONTENT_DECLARE(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FETCHCONTENT_MAKEAVAILABLE(glfw)

# --- GLAD ---
FETCHCONTENT_DECLARE(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        master
)
FETCHCONTENT_MAKEAVAILABLE(glad)

find_package(OpenGL REQUIRED)

include_directories(HumbuckerEngine)
include_directories(HumbuckerEngine/DiningPhilosophers)

add_executable(HumbuckerEngine
        HumbuckerEngine/Application.cpp
        HumbuckerEngine/AlgorithmsImplementations.cpp
        HumbuckerEngine/Rendering/OpenGLRenderer/OpenGLRenderer.cpp
        HumbuckerEngine/Rendering/OpenGLRenderer/GL_Window.cpp
        HumbuckerEngine/Rendering/OpenGLRenderer/GL_Window.h)

target_link_libraries(HumbuckerEngine PRIVATE glfw glad OpenGL::GL)