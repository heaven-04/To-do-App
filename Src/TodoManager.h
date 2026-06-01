#ifndef TODOAPP_TODOMANAGER_H
#define TODOAPP_TODOMANAGER_H
#include "Task.h"
#include <vector>
#include <string>
class TodoManager {
    std::vector<Task> activeTasks , completedTasks;
    int nextId{1};
    const std::string filename{"todo.json"};
    void saveToFile();
    void loadFromFile();
public :
    TodoManager();
    void toggleTask(int id);
    void deleteTask(int id);
    [[nodiscard]] std::vector<Task> getActiveTasks()const;
    [[nodiscard]] std::vector<Task> getCompletedTasks()const;
    void addTask(const std::string& title);
};
#endif