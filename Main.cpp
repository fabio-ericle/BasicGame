#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shader.h"
#include "Utils/ResourceFile.h"
#include "Shaders/SpriteRenderer.h"
#include "Shaders/Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Utils/stb_image.h"

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

    Shader* shader = new Shader(ResourceFile::FileToString(VERTEX_PATH), ResourceFile::FileToString(FRAGMENT_PATH));

    int width, height, channels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &channels, 0);

    SpriteRenderer* render = new SpriteRenderer(*shader);
    Texture2D* texture = new Texture2D();

    if (data)
    {
        texture->generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glm::vec2 position = glm::vec2(1.0);

    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position.x -= 0.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position.x += 0.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position.y -= 0.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position.y += 0.2f;
        }

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
        shader->setInt("fTexture", 0);
        shader->setMat4("projection", projection);

        render->drawSprite(*texture, glm::vec2(position), glm::vec2(100.f, 100.0f), 0.0f, glm::vec3(0.5f, 0.5f, 0.5f));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}