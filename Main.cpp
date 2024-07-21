#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

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

    const char* vertex_source =
        "#version 330 core\n"
        "layout (location = 0) in vec2 aPosition;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "}\n";

    const char* fragment_source =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

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

    //  VERTEX BUFFER OBJECT
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //  VERTEX ARRAY OBJECT
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint position_location = glGetAttribLocation(program, "aPosition");

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

        glUseProgram(program);
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