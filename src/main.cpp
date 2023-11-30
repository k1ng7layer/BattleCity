#include <glad/glad.h>
#include <GLFW/glfw3.h.>
#include <iostream>
#include "../src/Renderer/Include/ShaderProgram.h"
#include "../src/Resources/include/ResourceManager.h"

GLfloat vertexes[] {
    0.0, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0
};

GLfloat vertexColors[]{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

int g_windowSizeX = 640;
int g_windowSizeY = 480;


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;

    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, true);
    }
}

int main(int argc, char** argv)
{

    //GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        std::cout << "glfwInit failed" << std::endl;

        return -1;
    }

    //specify OpenGl version for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Hello World", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed" << std::endl;

        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()){
        std::cout << "Cant load glad" << std::endl;
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    std::cout << "Renderer "<< glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version "<< glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);


    {
        ResourceManager resourceManager(argv[0]);

        auto pDefaultShaderProgram = resourceManager.LoadShaderProgram("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

        if (!pDefaultShaderProgram){
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }


        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram -> Use();

            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    glfwTerminate();

    return 0;
}
