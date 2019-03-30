#ifndef _fgcamera_h_
#define _fgcamera_h_

#include <glad/glad.h>
#include <entity.hpp>
#include <glm/mat4x4.hpp>



class FreeCamera : public Entity {
    private:
        double originX = 0;
        double originY = 0;
        double currX = 0;
        double currY = 0;
        float camMoveSpeed = 0.02;
        glm::mat4 projection;
    public:
        FreeCamera(GLFWwindow *window);
        void update();
        glm::mat4 getViewMatrix();
        void setCamMoveSpeed(float speed);
};

#endif