#include "TodoManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr) return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;
    return true;
}
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(800, 600, "C++ To-Do App", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    TodoManager manager;
    GLuint bgTexture = 0;
    int bgWidth = 0, bgHeight = 0;
    bool hasBg = LoadTextureFromFile("papers.png", &bgTexture, &bgWidth, &bgHeight);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (hasBg) {
            ImGui::GetBackgroundDrawList()->AddImage(
                (void*)(intptr_t)bgTexture,
                viewport->WorkPos,
                ImVec2(viewport->WorkPos.x + viewport->WorkSize.x, viewport->WorkPos.y + viewport->WorkSize.y)
            );
        }
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.6f));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
        ImGui::Begin("My To-Do List", nullptr, flags);
        static char buffer[256] = "";
        ImGui::SetNextItemWidth(400.0f);
        ImGui::InputText("##TaskName", buffer, sizeof(buffer));
        ImGui::SameLine();

        if (ImGui::Button("Add Task")) {
            manager.addTask(buffer);
            buffer[0] = '\0';
        }

        ImGui::Separator();

        ImGui::Columns(2, "TaskColumns", true); // true adds a nice visible dividing line
        ImGui::SetColumnWidth(0, 310.0f);
        ImGui::SetColumnWidth(1, 310.0f);
        ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "Active Tasks:");
        ImGui::Spacing();

        for (const auto& task : manager.getActiveTasks()) {
            ImGui::PushID(task.id);
            bool isDone = task.isCompleted;
            if (ImGui::Checkbox(task.title.c_str(), &isDone)) {
                manager.toggleTask(task.id);
                ImGui::PopID();
                break;
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete")) {
                manager.deleteTask(task.id);
                ImGui::PopID();
                break;
            }
            ImGui::PopID();
        }

        ImGui::NextColumn();
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Completed Tasks:");
        ImGui::Spacing();

        for (const auto& task : manager.getCompletedTasks()) {
            ImGui::PushID(task.id);
            bool isDone = task.isCompleted;
            if (ImGui::Checkbox(task.title.c_str(), &isDone)) {
                manager.toggleTask(task.id);
                ImGui::PopID();
                break;
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete")) {
                manager.deleteTask(task.id);
                ImGui::PopID();
                break;
            }
            ImGui::PopID();
        }
        ImGui::Columns(1);
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::Render();
        glClearColor(0.15f, 0.15f, 0.15f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    return 0;
}