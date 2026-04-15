#include "GLFW\glfw3.h"
#include "glad\gl.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "util.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "cube.hpp"
#include "light.hpp"

int main()
{
    glfwSetErrorCallback(&glfwErrorCallbackFun);

    glfwInit();

    Window window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "GLFW OpenGL", nullptr, nullptr);
    window.makeContextCurrent();

    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    window.setKeyCallback(&glfwKeyCallbackFun);

    glfwSwapInterval(1);

    gladLoadGL(reinterpret_cast<GLADloadfunc>(&glfwGetProcAddress));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(&glErrorCallbackFun, nullptr);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 640, 480);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Shader cubeShader;

    cubeShader.compileVertexShader("shader\\vsCube.glsl");
    cubeShader.compileFragmentShader("shader\\fsCube.glsl");
    cubeShader.linkProgram();

    Shader lightShader;

    lightShader.compileVertexShader("shader\\vsLight.glsl");
    lightShader.compileFragmentShader("shader\\fsLight.glsl");
    lightShader.linkProgram();

    VertexBuffer arrayBuffer;

    arrayBuffer.bind(GL_ARRAY_BUFFER);
    arrayBuffer.data(GL_ARRAY_BUFFER, sizeof(gVertices), gVertices, GL_STATIC_DRAW);
    arrayBuffer.unbind(GL_ARRAY_BUFFER);

    Texture diffuse;

    diffuse.bind(GL_TEXTURE_2D);
    diffuse.image2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE, "image\\diffuse.png");
    diffuse.generateMipmap(GL_TEXTURE_2D);
    diffuse.unbind(GL_TEXTURE_2D);

    Texture specular;

    specular.bind(GL_TEXTURE_2D);
    specular.image2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE, "image\\specular.png");
    specular.generateMipmap(GL_TEXTURE_2D);
    specular.unbind(GL_TEXTURE_2D);

    Camera camera;

    MVP mvp
    {
        glm::mat4{ 1.0f },
        camera.view(),
        glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 0.1f, 100.0f)
    };

    Material material
    {
        diffuse,
        specular,
        32.0f
    };

    glm::vec3 cubePositions[]
    {
        { 0.0f, 0.0f, 0.0f },
        { 2.0f, 5.0f, -15.0f },
        { -1.5f, -2.2f, -2.5f },
        { -3.8f, -2.0f, -12.3f },
        { 2.4f, -0.4f, -3.5f },
        { -1.7f, 3.0f, -7.5f },
        { 1.3f, -2.0f, -2.5f },
        { 1.5f, 2.0f, -2.5f },
        { 1.5f, 0.2f, -1.5f },
        { -1.3f, 1.0f, -1.5f }
    };

    Cube cubes[]
    {
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer },
        Cube{ arrayBuffer }
    };

    for (unsigned int i{ 0 }; i < 10; ++i)
        cubes[i].setPosition(cubePositions[i]);

    glm::vec3 pointLightPositions[]
    {
        { 0.7f, 0.2f, 2.0f },
        { 2.3f, -3.3f, -4.0f },
        { -4.0f, 2.0f, -12.0f },
        { 0.0f, 0.0f, -3.0f }
    };

    Lights lights
    {
        DirectionLight
        {
            { 0.0f, -0.5f, -1.0f },
            { 0.1f, 0.1f, 0.1f },
            { 0.5f, 0.5f, 0.5f },
            { 0.8f, 0.8f, 0.8f }
        },
        {
            PointLight{ arrayBuffer },
            PointLight{ arrayBuffer },
            PointLight{ arrayBuffer },
            PointLight{ arrayBuffer }
        },
        SpotLight
        {
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
            glm::cos(glm::radians(12.5f)),
            glm::cos(glm::radians(17.5f)),
            1.0f,
            0.09f,
            0.032f,
            { 0.1f, 0.1f, 0.1f },
            { 1.0f, 1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f }
        }
    };

    for (unsigned int i{ 0 }; i < 4; ++i)
    {
        lights.pointLights[i].position = pointLightPositions[i];
        lights.pointLights[i].scale = glm::vec3{ 0.2f, 0.2f, 0.2f };
        lights.pointLights[i].constant = 1.0f;
        lights.pointLights[i].linear = 0.09f;
        lights.pointLights[i].quadratic = 0.032f;
        lights.pointLights[i].ambient = glm::vec3{ 0.1f, 0.1f, 0.1f };
        lights.pointLights[i].diffuse = glm::vec3{ 1.0f, 1.0f, 1.0f };
        lights.pointLights[i].specular = glm::vec3{ 1.0f, 1.0f, 1.0f };
    }

    while (!window.shouldClose())
    {
        glfwPollEvents();

        gTime.updateDelta();

        camera.updatePosition(window);
        camera.updateFront(window);

        cubeShader.use();
        cubeShader.uniform3fv("uCameraPosition", 1, &camera.position()[0]);
        cubeShader.unuse();

        mvp.view = camera.view();

        lights.spotLight.position = camera.position();
        lights.spotLight.direction = camera.front();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i{ 0 }; i < 10; ++i)
        {
            float angle{ glm::radians(36.0f * static_cast<float>(i)) };
            glm::vec3 rotationAxis{ 1.0f, 0.3f, 0.5f };

            mvp.model = glm::mat4{ 1.0f };
            mvp.model = glm::translate(mvp.model, cubes[i].position());
            mvp.model = glm::rotate(mvp.model, angle, rotationAxis);
            cubes[i].draw(cubeShader, mvp, material, lights);
        }

        for (unsigned int i{ 0 }; i < 4; ++i)
        {
            mvp.model = glm::mat4{ 1.0f };
            mvp.model = glm::translate(mvp.model, lights.pointLights[i].position);
            mvp.model = glm::scale(mvp.model, lights.pointLights[i].scale);
            lights.pointLights[i].draw(lightShader, mvp);
        }

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}