#include <entity.hpp>

#include <fgutils/logs.h>

Entity::Entity(GLFWwindow *window) {
    this->window = window;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Entity::setPosition(glm::vec3 pos) {
    this->position = pos;
}

void Entity::setOrientation(glm::quat orientation) {
    this->orientation = orientation;
}

void Entity::move(glm::vec3 translation) {
    this->position = this->position + translation;
}

void Entity::rotate(glm::quat rotation) {
    this->orientation = rotation * this->orientation;
}

