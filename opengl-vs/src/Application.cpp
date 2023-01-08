#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"

void processInput();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double scrollX, double scrollY);

// window settings
const char* TITLE = "OpenGL Template";
const unsigned int SCREEN_W = 800;
const unsigned int SCREEN_H = 600;

// globals
GLFWwindow* window;
Camera camera;

float deltaTime, lastDelta = 0;
float lastXPos, lastYPos = 0;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCREEN_W, SCREEN_H, TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // events and buffer swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

bool doesPress(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void processInput()
{
    if (doesPress(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (doesPress(GLFW_KEY_W))
        camera.move(FRONT);
    if (doesPress(GLFW_KEY_S))
        camera.move(BACK);
    if (doesPress(GLFW_KEY_A))
        camera.move(LEFT);
    if (doesPress(GLFW_KEY_D))
        camera.move(RIGHT);
    if (doesPress(GLFW_KEY_SPACE))
        camera.move(UP);
}

/* callbacks definitions */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double scrollX, double scrollY)
{
    camera.updateFOV(scrollY);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    float xOffset = xPos - lastXPos;
    float yOffset = lastYPos - yPos;
    lastXPos = xPos;
    lastYPos = yPos;

    camera.updateDirection(xOffset, yOffset);
}