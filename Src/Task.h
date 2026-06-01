#ifndef TODOAPP_TASK_H
#define TODOAPP_TASK_H
#include <string>

#include "json.hpp"

struct Task {
    int id;
    std::string title;
    bool isCompleted;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task,id,title,isCompleted);

#endif