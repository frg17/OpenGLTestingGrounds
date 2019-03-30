#ifndef _fgshader_h_
#define _fgshader_h_

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
    private:
        GLuint ID;
        char error;
    public:
        /**
         * Main constructor.
         */
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

        /**
         * Tells gl to use this shader
         */
        void use();

        /**
         * Sets a uniform location.
         */
        void uniform1f(GLuint location, float value);
        void uniform4fv(GLuint location, float value[]);
        void uniformMat4fv(GLuint location, glm::mat4);

        /**
         * Returns uniform location
         */
        GLuint getUniformLoc(const char* uniformName);
};

#endif