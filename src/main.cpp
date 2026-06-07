#include <iostream>
#include "glfw.hpp"
#include "glad.hpp"
#include "glm.hpp"
#include "assimp.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "delta.hpp"
#include "mvp.hpp"
#include "material.hpp"
#include "model.hpp"

void glfwErrorCallback(int errorCode, const char* description);
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mods);

void glErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

int main()
{
    glfwSetErrorCallback(&glfwErrorCallback);

    glfwInit();

    Window window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "C++ GLFW OpenGL", nullptr, nullptr);
    window.makeContextCurrent();

    glfwSwapInterval(1);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    window.setKeyCallback(&glfwKeyCallback);

    gladLoadGL(&glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(&glErrorCallback, nullptr);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 640, 480);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Shader shader;

    shader.compileVertexShader("shader\\vertex_shader.glsl");
    shader.compileFragmentShader("shader\\fragment_shader.glsl");
    shader.linkProgram();

    Camera camera;

    MVP mvp
    {
        glm::mat4{ 1.0f },
        glm::mat4{ 1.0f },
        glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 0.1f, 100.0f)
    };

    Material material
    {
        Texture{},
        Texture{},
        32.0f
    };

    material.diffuse.bind(GL_TEXTURE_2D);
    material.diffuse.image2D(GL_TEXTURE_2D, 0, GL_RGB, 0, GL_RGB, GL_UNSIGNED_BYTE, "model\\backpack\\diffuse.jpg");
    material.diffuse.generateMipmap(GL_TEXTURE_2D);
    material.diffuse.unbind(GL_TEXTURE_2D);

    material.specular.bind(GL_TEXTURE_2D);
    material.specular.image2D(GL_TEXTURE_2D, 0, GL_RGB, 0, GL_RGB, GL_UNSIGNED_BYTE, "model\\backpack\\specular.jpg");
    material.specular.generateMipmap(GL_TEXTURE_2D);
    material.specular.unbind(GL_TEXTURE_2D);

    Model model{ "model\\backpack\\backpack.obj" };

    while (!window.shouldClose())
    {
        glfwPollEvents();

        camera.update(window);
        delta.update();

        mvp.view = camera.view();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model.draw(shader, mvp, material);

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}

void glfwErrorCallback(int, const char* description)
{
    std::cerr << "GLFW ERROR: " << description << '\n';
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}

void glErrorCallback(unsigned int, unsigned int, unsigned int, unsigned int, int, const char* message, const void*)
{
    std::cerr << "GL ERROR: " << message << '\n';
}