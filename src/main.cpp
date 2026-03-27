#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GLFW\glfw3.h"
#include "glad\gl.h"
#include "stb_image.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

GLvoid glfwErrorCallback(GLint errorCode, const GLchar* description);
GLvoid glfwkeyCallback(GLFWwindow* pWindow, GLint key, GLint scancode, GLint action, GLint mods);
GLvoid glfwCursorposCallback(GLFWwindow* pWindow, GLdouble xpos, GLdouble ypos);

GLvoid glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);
std::string glLoadShaderCode(const GLchar* fileName);

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

bool gCursorMove;

int main()
{
    glfwInit();

    GLFWwindow* pWindow;

    pWindow = glfwCreateWindow(640, 480, "GLFW OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(pWindow);

    glfwSetErrorCallback(&glfwErrorCallback);
    glfwSetKeyCallback(pWindow, &glfwkeyCallback);
    glfwSetCursorPosCallback(pWindow, &glfwCursorposCallback);

    gladLoadGL(&glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(&glMessageCallback, nullptr);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 640, 480);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::string shaderCode;
    const GLchar* pShaderCode;

    GLuint vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    shaderCode = glLoadShaderCode("shaders\\vertex_shader.txt");
    pShaderCode = shaderCode.c_str();
    glShaderSource(vertexShader, 1, &pShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    shaderCode = glLoadShaderCode("shaders\\fragment_shader.txt");
    pShaderCode = shaderCode.c_str();
    glShaderSource(fragmentShader, 1, &pShaderCode, nullptr);
    glCompileShader(fragmentShader);

    GLuint program;

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glUseProgram(program);

    GLuint vertexArray;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint vertexBuffer;
    Vertex vertices[]
    {
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} },
        { { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
        { { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
        { {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} },

        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },

        { {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },
        { {-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },

        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },

        { {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },

        { {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} },
        { { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f} },
        { {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} }
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const GLvoid*>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const GLvoid*>(12));

    GLint width;
    GLint height;
    GLint channels;
    GLubyte* data;

    stbi_set_flip_vertically_on_load(1);

    data = stbi_load("images\\container.jpg", &width, &height, &channels, 0);

    GLuint texture0;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    data = stbi_load("images\\awesomeface.png", &width, &height, &channels, 0);

    GLuint texture1;

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    GLint uTexSampler0;
    GLint uTexSampler1;

    uTexSampler0 = glGetUniformLocation(program, "uTexSampler0");
    uTexSampler1 = glGetUniformLocation(program, "uTexSampler1");
    glUniform1i(uTexSampler0, 0);
    glUniform1i(uTexSampler1, 1);

    glm::vec3 modelPositions[10];
    GLfloat modelAngle;
    glm::vec3 modelRotationAxis;
    glm::mat4 modelMat;

    modelPositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
    modelPositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
    modelPositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
    modelPositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
    modelPositions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
    modelPositions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
    modelPositions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
    modelPositions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
    modelPositions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
    modelPositions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);
    modelRotationAxis = glm::vec3( 1.0f,  0.3f,  0.5f);

    glm::vec3 viewPosition;
    glm::vec3 viewRight;
    glm::vec3 viewUp;
    glm::vec3 viewFront;
    GLfloat viewYaw;
    GLfloat viewPitch;
    glm::vec3 viewDirection;
    glm::mat4 viewMat;

    viewPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    viewRight = glm::vec3(1.0f, 0.0f, 0.0f);
    viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
    viewFront = glm::vec3(0.0f, 0.0f, -1.0f);
    viewYaw = -90;
    viewPitch = 0;
    viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);

    glm::mat4 projectionMat;

    projectionMat = glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 0.1f, 100.0f);

    glm::vec3 worldUp;

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    GLint uModelMat;
    GLint uViewMat;
    GLint uProjectionMat;

    uModelMat = glGetUniformLocation(program, "uModelMat");
    uViewMat = glGetUniformLocation(program, "uViewMat");
    uProjectionMat = glGetUniformLocation(program, "uProjectionMat");
    glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(uProjectionMat, 1, GL_FALSE, glm::value_ptr(projectionMat));

    GLdouble cursorXd;
    GLdouble cursorYd;
    GLfloat cursorX0;
    GLfloat cursorY0;
    GLfloat cursorX1;
    GLfloat cursorY1;
    GLfloat cursorOffsetX;
    GLfloat cursorOffsetY;

    glfwGetCursorPos(pWindow, &cursorXd, &cursorYd);
    cursorX0 = static_cast<GLfloat>(cursorXd);
    cursorY0 = static_cast<GLfloat>(cursorYd);

    GLfloat time0;
    GLfloat time1;
    const GLfloat fps{ 1.0f / 30.0f };

    time0 = 0.0f;

    while (!glfwWindowShouldClose(pWindow))
    {
        time1 = static_cast<GLfloat>(glfwGetTime());

        if ((time1 - time0) >= fps)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (glfwGetKey(pWindow, GLFW_KEY_LEFT))
            {
                viewPosition -= viewRight * 0.1f;
                viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);
                glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
            }
            else
            if (glfwGetKey(pWindow, GLFW_KEY_RIGHT))
            {
                viewPosition += viewRight * 0.1f;
                viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);
                glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
            }

            if (glfwGetKey(pWindow, GLFW_KEY_UP))
            {
                viewPosition += viewFront * 0.1f;
                viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);
                glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
            }
            else
            if (glfwGetKey(pWindow, GLFW_KEY_DOWN))
            {
                viewPosition -= viewFront * 0.1f;
                viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);
                glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
            }

            if (gCursorMove)
            {
                glfwGetCursorPos(pWindow, &cursorXd, &cursorYd);
                cursorX1 = static_cast<GLfloat>(cursorXd);
                cursorY1 = static_cast<GLfloat>(cursorYd);
                cursorOffsetX = cursorX1 - cursorX0;
                cursorOffsetY = cursorY1 - cursorY0;

                viewYaw += cursorOffsetX * 0.1f;
                viewPitch += -cursorOffsetY * 0.1f;

                if (viewPitch > 89.0f)
                    viewPitch = 89.0f;
                else
                if (viewPitch < -89.0f)
                    viewPitch = -89.0f;

                viewDirection.x = glm::cos(glm::radians(viewYaw)) * glm::cos(glm::radians(viewPitch));
                viewDirection.y = glm::sin(glm::radians(viewPitch));
                viewDirection.z = glm::sin(glm::radians(viewYaw)) * glm::cos(glm::radians(viewPitch));

                viewFront = glm::normalize(viewDirection);
                viewRight = glm::normalize(glm::cross(viewFront, worldUp));
                viewUp = glm::normalize(glm::cross(viewRight, viewFront));
                viewMat = glm::lookAt(viewPosition, (viewPosition + viewFront), viewUp);
                glUniformMatrix4fv(uViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

                cursorX0 = cursorX1;
                cursorY0 = cursorY1;

                gCursorMove = false;
            }

            for (GLuint i{ 0 }; i < 10; ++i)
            {
                modelMat = glm::mat4(1.0f);
                modelMat = glm::translate(modelMat, modelPositions[i]);
                modelAngle = 36.0f * static_cast<GLfloat>(i);
                modelMat = glm::rotate(modelMat, glm::radians(modelAngle), modelRotationAxis);
                glUniformMatrix4fv(uModelMat, 1, GL_FALSE, glm::value_ptr(modelMat));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            glfwSwapBuffers(pWindow);

            time0 = time1;
        }

        glfwPollEvents();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);

    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);

    glDeleteTextures(1, &texture0);
    glDeleteTextures(1, &texture1);

    glfwTerminate();

    return 0;
}

GLvoid glfwErrorCallback(GLint errorCode, const GLchar* description)
{
    std::cout << "GLFW error " << errorCode << ": " << description << '\n';
}

GLvoid glfwkeyCallback(GLFWwindow* pWindow, GLint key, GLint, GLint action, GLint)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}

GLvoid glfwCursorposCallback(GLFWwindow*, GLdouble, GLdouble)
{
    gCursorMove = true;
}

GLvoid glMessageCallback(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const GLvoid*)
{
    std::cerr << "GL CALLBACK: " << ((type == GL_DEBUG_TYPE_ERROR) ? "** GL ERROR **" : "") << " type = 0x" << type << ", severity = 0x" << severity << ", message = " << message << '\n';
}

std::string glLoadShaderCode(const GLchar* fileName)
{
    std::ifstream file;

    file.open(fileName);

    if (file.is_open())
    {
        std::ostringstream stream;

        stream << file.rdbuf();

        file.close();

        return stream.str();
    }

    return std::string("");
}