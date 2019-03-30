#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fgutils/logs.h>
#include <fgutils/fileio.h>
#include <shader.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.hpp>

unsigned int VAO, VBO;
unsigned int uniformLocMV, uniformLocColor;

typedef void (*eventFunc)(GLFWwindow *window);

int pressed = 0;
float spinX = 0;
float spinY = 0;

FreeCamera camera = NULL;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5, -0.5, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5, -0.5, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};

uint16_t quad[] = {
    0, 1, 2, 0, 2, 3,
    1, 5, 6, 1, 6, 2,
    5, 7, 6, 5, 7, 4,
    4, 0, 3, 4, 3, 7,
    3, 2, 6, 3, 6, 7,
    0, 5, 1, 0, 4, 5
};


float *unpackElements(uint16_t indices[], int indicesCount, float attributes[], int count) {
    uint16_t size = indicesCount;
    float *outArray = (float *) malloc(size * count *sizeof(float));

    for (int i = 0; i < size; i++) {
        for(int j = 0; j < count; j++) {
            outArray[(count * i) + j] = attributes[count * indices[i] + j];
        }
    }

    return outArray;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int initBuffers() {
    int indiceCount = sizeof(quad)/sizeof(uint16_t);
    float *unpackedVertices = unpackElements(quad, indiceCount, vertices, 3);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3*indiceCount*sizeof(float), unpackedVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 0;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        fgLog("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fgLog("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    
    glfwSetCursorPos(window, 0.0f, 0.0f);
    glfwSwapInterval(1);

    Shader shader = Shader("./shaders/vertex-shader.glsl", "./shaders/fragment-shader.glsl");
    uniformLocMV = shader.getUniformLoc("mv");
    uniformLocColor = shader.getUniformLoc("color");

    camera = FreeCamera(window);
    camera.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));


    if(initBuffers()) return 1;

    float time = 0;
    int verticeCount = sizeof(quad)/sizeof(uint16_t);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        time = glfwGetTime();


        shader.use();
        glBindVertexArray(VAO);

        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 mv = view;
        mv = glm::rotate(mv, time, glm::vec3(1.0f, 0.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(0.0f, 0.0f, -1.0f));
        mv = glm::scale(mv, glm::vec3(0.2f, 0.2f, 0.2f));
        shader.uniformMat4fv(uniformLocMV, mv);
        float color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
        shader.uniform4fv(uniformLocColor, color);
        glDrawArrays(GL_TRIANGLES, 0, verticeCount);

        mv = view;
        mv = glm::translate(mv, glm::vec3(0.5f, 0.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(-1.0f, 0.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(0.0f, 0.0f, -1.0f));
        mv = glm::scale(mv, glm::vec3(0.1f, 0.1f, 0.1f));
        shader.uniformMat4fv(uniformLocMV, mv);
        float color2[] = { 0.0f, 1.0f, 0.0f, 1.0f};
        shader.uniform4fv(uniformLocColor, color2);
        glDrawArrays(GL_TRIANGLES, 0, verticeCount);

        mv = view;
        mv = glm::translate(mv, glm::vec3(0.5f, -1.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(-1.0f, 0.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(0.0f, 0.0f, -1.0f));
        mv = glm::scale(mv, glm::vec3(0.1f, 0.1f, 0.1f));
        shader.uniformMat4fv(uniformLocMV, mv);
        float color3[] = { 1.0f, 0.0f, 1.0f, 1.0f};
        shader.uniform4fv(uniformLocColor, color3);
        glDrawArrays(GL_TRIANGLES, 0, verticeCount);

        mv = view;
        mv = glm::translate(mv, glm::vec3(1.5f, -0.5f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(-1.0f, 0.0f, 0.0f));
        mv = glm::rotate(mv, time, glm::vec3(0.0f, 0.0f, -1.0f));
        mv = glm::scale(mv, glm::vec3(0.1f, 0.1f, 0.1f));
        shader.uniformMat4fv(uniformLocMV, mv);
        float color4[] = { 1.0f, 1.0f, 0.0f, 1.0f};
        shader.uniform4fv(uniformLocColor, color4);
        glDrawArrays(GL_TRIANGLES, 0, verticeCount);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

    camera.update();
}

