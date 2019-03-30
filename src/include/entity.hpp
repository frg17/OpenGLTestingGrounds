#ifndef _fgentity_h_
#define _fgentity_h_

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Entity {
    protected:
        GLFWwindow *window;
        glm::vec3 position;
        glm::quat orientation;

    public:
        Entity(GLFWwindow *context);
        void setOrientation(glm::quat);
        void setPosition(glm::vec3);
        void rotate(glm::quat);
        void move(glm::vec3);
};

#endif