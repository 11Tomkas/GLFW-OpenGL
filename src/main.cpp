#include <iostream>
#include "glfw.hpp"
#include "glad.hpp"
#include "glm.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "delta.hpp"
#include "mvp.hpp"
#include "material.hpp"
#include "cube.hpp"
#include "light.hpp"

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

    Shader cubeShader;

    cubeShader.compileVertexShader("shader\\cube.vs");
    cubeShader.compileFragmentShader("shader\\cube.fs");
    cubeShader.linkProgram();

    Shader lightShader;

    lightShader.compileVertexShader("shader\\light.vs");
    lightShader.compileFragmentShader("shader\\light.fs");
    lightShader.linkProgram();

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
    material.diffuse.image2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE, "image\\diffuse.png");
    material.diffuse.generateMipmap(GL_TEXTURE_2D);
    material.diffuse.unbind(GL_TEXTURE_2D);

    material.specular.bind(GL_TEXTURE_2D);
    material.specular.image2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE, "image\\specular.png");
    material.specular.generateMipmap(GL_TEXTURE_2D);
    material.specular.unbind(GL_TEXTURE_2D);

    Cube cubes[10];

    cubes[0].setPosition({ 0.0f, 0.0f, 0.0f });
    cubes[1].setPosition({ 2.0f, 5.0f,-15.0f });
    cubes[2].setPosition({-1.5f,-2.2f,-2.5f });
    cubes[3].setPosition({-3.8f,-2.0f,-12.3f });
    cubes[4].setPosition({ 2.4f,-0.4f,-3.5f });
    cubes[5].setPosition({-1.7f, 3.0f,-7.5f });
    cubes[6].setPosition({ 1.3f,-2.0f,-2.5f });
    cubes[7].setPosition({ 1.5f, 2.0f,-2.5f });
    cubes[8].setPosition({ 1.5f, 0.2f,-1.5f });
    cubes[9].setPosition({-1.3f, 1.0f,-1.5f });

    for (unsigned int i{ 0 }; i < 10; ++i)
        cubes[i].setRotation((36.0f * static_cast<float>(i)), { 1.0f, 0.3f, 0.5f});

    Light light
    {
        DirectionLight
        {
            { 0.0f, -0.5f, -1.0f },
            { 0.1f,  0.1f,  0.1f },
            { 0.5f,  0.5f,  0.5f },
            { 0.8f,  0.8f,  0.8f }
        },
        {
            PointLight{},
            PointLight{},
            PointLight{},
            PointLight{}
        },
        SpotLight
        {
            {},
            {},
            glm::cos(glm::radians(12.5f)),
            glm::cos(glm::radians(17.5f)),
            1.0f,
            0.09f,
            0.032f,
            { 0.1f, 0.1f, 0.1f },
            { 0.5f, 0.5f, 0.5f },
            { 0.8f, 0.8f, 0.8f }
        }
    };

    light.pointLights[0].setPosition({ 0.7f, 0.2f, 2.0f });
    light.pointLights[1].setPosition({ 2.3f,-3.3f,-4.0f });
    light.pointLights[2].setPosition({-4.0f, 2.0f,-12.0f });
    light.pointLights[3].setPosition({ 0.0f, 0.0f,-3.0f });

    for (unsigned int i{ 0 }; i < 4; ++i)
    {
        light.pointLights[i].setScale({ 0.2f, 0.2f, 0.2f });
        light.pointLights[i].constant = 1.0f;
        light.pointLights[i].linear = 0.09f;
        light.pointLights[i].quadratic = 0.032f;
        light.pointLights[i].ambient = { 0.1f, 0.1f, 0.1f };
        light.pointLights[i].diffuse = { 0.5f, 0.5f, 0.5f };
        light.pointLights[i].specular = { 0.8f, 0.8f, 0.8f };
    }

    while (!window.shouldClose())
    {
        glfwPollEvents();

        camera.update(window);
        delta.update();

        light.spotLight.position = camera.position();
        light.spotLight.direction = camera.front();

        cubeShader.use();
        cubeShader.uniform3fv("uCameraPosition", 1, &camera.position()[0]);
        cubeShader.unuse();

        mvp.view = camera.view();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i{ 0 }; i < 10; ++i)
            cubes[i].draw(cubeShader, mvp, material, light);

        for (unsigned int i{ 0 }; i < 4; ++i)
            light.pointLights[i].draw(lightShader, mvp);

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