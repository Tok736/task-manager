#include "Project.h"


std::string Project::getName() const {
    return name;
}
void Project::setName(std::string name) {
    this->name = name;
}
void Project::setDescription(std::string description) {
    this->description = description;
}

std::string Project::getDescription() const {
    return description;
}
