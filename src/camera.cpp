#include <camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <fgutils/logs.h>

FreeCamera::FreeCamera(GLFWwindow *window) : Entity(window){
    this->projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 30.0f);
};

void FreeCamera::update() {
    //Handle mouse movement
    glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);
    glfwGetCursorPos(this->window, &(this->currX), &(this->currY));
    rot.x = 0.1 * glm::radians((this->currY - this->originY));
    rot.y = 0.1 * glm::radians((this->currX - this->originX));

    this->originX = this->currX;
    this->originY = this->currY;

    this->rotate(glm::quat(rot));

    //Handle keyboard
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        velocity += glm::vec3(0.0f, 0.0f, -1.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        velocity += glm::vec3(0.0f, 0.0f, 1.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        velocity += glm::vec3(1.0f, 0.0f, 0.0f);    
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        velocity += glm::vec3(-1.0f, 0.0f, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        velocity += glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if(glm::length(velocity) > 0)
        this->move(this->camMoveSpeed * glm::normalize(velocity * this->orientation));
}

glm::mat4 FreeCamera::getViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4_cast(this->orientation);
    view = glm::translate(view, this->position * (-1.0f));
    return projection * view;
}

void FreeCamera::setCamMoveSpeed(float speed) {
    this->camMoveSpeed = speed;
}