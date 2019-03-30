#include <shader.h>

#include <fgutils/fileio.h>
#include <fgutils/logs.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(
    const char* vertexShaderSourceFile, 
    const char* fragmentShaderSourceFile) 
{
    int  success;
    char infoLog[512];

    this->ID = glCreateProgram();

    //Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = fgReadFile(vertexShaderSourceFile);
    fgLog("%s", vertexSource);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fgLog("%s", infoLog);
        error = 1;
    }

    //Compile Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fgReadFile(fragmentShaderSourceFile);
    fgLog("%s", fragmentSource);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fgLog("%s", infoLog);
    }

    //Attach shaders and link program
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        fgLog("%s", infoLog);
    }

}

void Shader::use() {
    glUseProgram(this->ID);
}

GLuint Shader::getUniformLoc(const char *name) {
    return glGetUniformLocation(this->ID, name);
}

void Shader::uniform1f(GLuint loc, float value) {
    glUniform1f(loc, value);
}

void Shader::uniform4fv(GLuint location, float color[]) {
    glUniform4fv(location, 1, color);
}

void Shader::uniformMat4fv(GLuint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}