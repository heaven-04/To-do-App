# ToDoApp 📝

A lightweight, high-performance desktop ToDo application written in modern **C++20**. It features a clean graphical user interface built with **Dear ImGui** and offers local data persistence using **nlohmann/json**.

---

## ✨ Features

* **Dual-Column Layout:** Easily view and manage your **Active Tasks** and **Completed Tasks** side-by-side.
* **Instant Persistence:** Tasks are automatically saved to and loaded from a local `todo.json` file.
* **Seamless Task Toggling:** Use checkboxes to move tasks instantly between active and completed states.
* **Hardware Accelerated:** Rendered using **OpenGL 3** and managed via **GLFW** for smooth desktop performance.
* **Embedded Assets:** Custom application styling with icon support powered by `stb_image`.

---

## 🛠️ Tech Stack

| Component | Technology | Description |
| :--- | :--- | :--- |
| **Language** | C++20 | Leverages modern C++ standards and type-safety. |
| **GUI Framework** | [Dear ImGui](https://github.com/ocornut/imgui) | Bloat-free, immediate-mode graphical user interface. |
| **Window & Input** | [GLFW 3.3.8](https://github.com/glfw/glfw) | Multi-platform windowing and input handling (fetched automatically). |
| **Graphics API** | OpenGL 3 | Low-level hardware-accelerated rendering. |
| **Serialization** | [nlohmann/json](https://github.com/nlohmann/json) | Modern JSON parsing for saving task states. |
| **Image Loading** | `stb_image.h` | Single-header library for texture and icon handling. |
| **Build System** | CMake 3.15+ | Cross-platform build automation. |

---

## 📁 Project Structure

```text
├── External/
│   ├── Im_Gui/         # Dear ImGui source files & backends (GLFW/OpenGL3)
│   └── Json/           # nlohmann/json header files
├── Src/
│   ├── main.cpp        # Application entry point & main UI loop
│   ├── Task.h          # Task structure & JSON serialization macros
│   ├── TodoManager.h   # Task management business logic header
│   ├── TodoManager.cpp # Task CRUD logic and JSON I/O implementation
│   └── stb_image.h     # Image loader utility
├── checklist-icon.ico  # Application icon asset
├── resources.rc        # Windows resource file for the executable icon
└── CMakeLists.txt      # Build configuration file
