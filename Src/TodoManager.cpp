#include "TodoManager.h"
#include <fstream>
#include <algorithm>
TodoManager::TodoManager() {
    loadFromFile();
}
void TodoManager::addTask(const std::string &title) {
    Task task;
    task.id=nextId;
    nextId++;
    task.title=title;
    task.isCompleted=false;
    activeTasks.push_back(task);
    saveToFile();
}

void TodoManager::deleteTask(int id) {
    for (int i=0;i<activeTasks.size();i++) {
        if (activeTasks[i].id==id) {
            activeTasks.erase(activeTasks.begin()+i);
            break;
        }
    }
    for (int i=0;i<completedTasks.size();i++) {
        if (completedTasks[i].id==id) {
            completedTasks.erase(completedTasks.begin()+i);
            break;
        }
    }
    saveToFile();
}
void TodoManager::toggleTask(int id) {
    bool existsinActiveTasks=false;
    for (int i=0;i<activeTasks.size();i++) {
        if (activeTasks[i].id==id) {
            activeTasks[i].isCompleted=true;
            completedTasks.push_back(activeTasks[i]);
            activeTasks.erase(activeTasks.begin()+i);
            existsinActiveTasks=true;
            break;
        }
    }
    if (!existsinActiveTasks) {
        for (int i=0;i<completedTasks.size();i++) {
            if (completedTasks[i].id==id) {
                completedTasks[i].isCompleted=false;
                activeTasks.push_back(completedTasks[i]);
                completedTasks.erase(completedTasks.begin()+i);
                break;
            }
        }
    }
    saveToFile();
}
void TodoManager::saveToFile() {
    std::ofstream out(filename);
    std::vector<Task> allTasks;
    for (auto& task : activeTasks) {
        allTasks.push_back(task);
    }
    for (auto& task : completedTasks) {
        allTasks.push_back(task);
    }
    using nlohmann::json;
    json j=allTasks;
    out<<j.dump(4);
}

void TodoManager::loadFromFile() {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return;
    }
    using nlohmann::json;
    json j;
    in>>j;
    auto allTasks=j.get<std::vector<Task>>();
    activeTasks.clear();
    completedTasks.clear();
    for (auto& task : allTasks) {
        if (task.id >= nextId) {
            nextId = task.id + 1;
        }
        if (!task.isCompleted) {
            activeTasks.push_back(task);
        }
        else {
            completedTasks.push_back(task);
        }
    }
}

std::vector<Task> TodoManager::getActiveTasks() const {
    return this->activeTasks;
}
std::vector<Task> TodoManager::getCompletedTasks() const {
    return this->completedTasks;
}
