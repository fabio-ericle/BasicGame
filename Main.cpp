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

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    if (!glfwInit())
    {
        std::cout << "\nERROR::GLFW::FAILED_TO_LOAD\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
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

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader = Shader(ResourceFile::FileToString(VERTEX_PATH), ResourceFile::FileToString(FRAGMENT_PATH));
    SpriteRenderer render = SpriteRenderer(shader);
    Texture2D texture = Texture2D();

    int width, height, channels;
    unsigned char* data = stbi_load("./container.jpg", &width, &height, &channels, 0);

    if (data)
    {
        texture.generate(width, height, data);
    }
    else
    {
        std::cout << "\nERROR::STB_IMAGE::FALED_TO_LOAD_IMAGE\n";
    }

    stbi_image_free(data);

    glm::vec2 position = glm::vec2(1.0);

    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position.x -= 1.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position.x += 1.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position.y -= 1.2f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position.y += 1.2f;
        }

        int screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        // Terrain generator test
        float r = 0.0f, g = 0.0f, b = 0.0f;
        for (GLuint i = 0; i < 15; i++)
        {
            for (GLuint j = 0; j < 50; j++)
            {
                if (i == 6)
                {
                    r = 0.0f;
                    g = 1.0f;
                    b = 0.0f;
                }
                else if(i > 6 || i < 8)
                {
                    r = 1.0f;
                    g = 0.7f;
                    b = 0.5f;
                }
                else
                {
                    r = 0.8f;
                    g = 0.8f;
                    b = 0.8f;
                }

                glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
                shader.setInt("fTexture", 0);
                shader.setMat4("projection", projection);

                if (i > 5)
                {
                    render.drawSprite(texture, glm::vec2(j * 50.0f, i * 50.0f), glm::vec2(50.f, 50.0f), 0.0f, glm::vec3(r, g, b));
                }
            }
        }

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
        shader.setInt("fTexture", 0);
        shader.setMat4("projection", projection);

        render.drawSprite(texture, glm::vec2(position), glm::vec2(50.f, 50.0f), 0.0f, glm::vec3(1.0f, 0.5f, 0.5f));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}