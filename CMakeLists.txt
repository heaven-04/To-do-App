cmake_minimum_required(VERSION 3.15)
project(ToDoApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)



# 3. Create the executable
add_executable(ToDoApp WIN32 Src/main.cpp
        Src/TodoManager.cpp
        External/Im_Gui/imgui.cpp
        External/Im_Gui/imgui_draw.cpp
        External/Im_Gui/imgui_tables.cpp
        External/Im_Gui/imgui_widgets.cpp
        External/Im_Gui/imgui_demo.cpp
        External/Im_Gui/backends/imgui_impl_glfw.cpp
        External/Im_Gui/backends/imgui_impl_opengl3.cpp
        Src/stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)
target_include_directories(ToDoApp PRIVATE
        Src
        External/Im_Gui
        External/Im_Gui/backends
        External/Json
)
target_link_libraries(ToDoApp PRIVATE glfw opengl32)