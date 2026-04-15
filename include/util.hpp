#ifndef UTIL_HPP
#define UTIL_HPP

#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 textureCoord;
};

struct MVP
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

extern Vertex gVertices[36];

void glfwErrorCallbackFun(int errorCode, const char* description);
void glfwKeyCallbackFun(GLFWwindow* pWindow, int key, int scanCode, int action, int mods);
void glErrorCallbackFun(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);

#endif