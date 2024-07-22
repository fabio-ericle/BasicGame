#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shader.h"
#include "Utils/ResourceFile.h"

constexpr const char* VERTEX_PATH = "Shaders/Sources/vertex.glsl";
constexpr const char* FRAGMENT_PATH = "Shaders/Sources/fragment.glsl";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "game", NULL, NULL);
    if (!window)
    {
        std::cout << "\nERROR::GLFW::FAILED_TO_CREATE_A_WINDOW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int gladVersion = gladLoadGL(glfwGetProcAddress);
    if (gladVersion == 0)
    {
        std::cout << "\nERROR::GLAD::FAILED_TO_LOAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] =
    {
        -0.5f,  0.5f,   // Top left
        -0.5f, -0.5f,   // Bottom left
         0.5f, -0.5f,   // Bottom right
         0.5f,  0.5f    // Top right
    };

    int indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    Shader* shader = new Shader(ResourceFile::FileToString(VERTEX_PATH), ResourceFile::FileToString(FRAGMENT_PATH));

    //  VERTEX BUFFER OBJECT
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //  VERTEX ARRAY OBJECT
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint position_location = glGetAttribLocation(shader->programID, "aPosition");

    glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position_location);

    //  ELEMENT BUFFER OBJECT
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}