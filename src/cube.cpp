#include "cube.hpp"

#include "glad.hpp"
#include "vertex_buffer.hpp"
#include "light.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 textureCoord;
};

Cube::Cube()
    : m_vertexArray{}
    , m_position{ 0.0f, 0.0f, 0.0f }
    , m_angle{ 0.0f }
    , m_rotationAxis{ 0.0f, 0.0f, 1.0f }
    , m_scale{ 1.0f, 1.0f, 1.0f }
{
    static bool cubeInit{ true };
    static VertexBuffer arrayBuffer;

    if (cubeInit)
    {
        Vertex vertices[]
        {
            {{-0.5f, -0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},

            {{-0.5f, -0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},

            {{-0.5f,  0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},

            {{ 0.5f,  0.5f,  0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},

            {{-0.5f, -0.5f, -0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},

            {{-0.5f,  0.5f, -0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}}
        };

        arrayBuffer.bind(GL_ARRAY_BUFFER);
        arrayBuffer.data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        arrayBuffer.unbind(GL_ARRAY_BUFFER);

        cubeInit = false;
    }

    m_vertexArray.bind();
    arrayBuffer.bind(GL_ARRAY_BUFFER);
    arrayBuffer.enableVertexAttribArray(0);
    arrayBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    arrayBuffer.enableVertexAttribArray(1);
    arrayBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(12));
    arrayBuffer.enableVertexAttribArray(2);
    arrayBuffer.vertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(24));
    arrayBuffer.enableVertexAttribArray(3);
    arrayBuffer.vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(36));
    arrayBuffer.unbind(GL_ARRAY_BUFFER);
    m_vertexArray.unbind();
}

void Cube::setPosition(const glm::vec3& position)
{
    m_position = position;
}

void Cube::setRotation(float angle, const glm::vec3& rotationAxis)
{
    m_angle = glm::radians(angle);
    m_rotationAxis = rotationAxis;
}

void Cube::setScale(const glm::vec3& scale)
{
    m_scale = scale;
}

void Cube::draw(const Shader& shader, MVP& mvp, const Material& material, const Light& light)
{
    mvp.model = glm::mat4{ 1.0f };
    mvp.model = glm::translate(mvp.model, m_position);
    mvp.model = glm::rotate(mvp.model, m_angle, m_rotationAxis);
    mvp.model = glm::scale(mvp.model, m_scale);

    glActiveTexture(GL_TEXTURE0);
    material.diffuse.bind(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    material.specular.bind(GL_TEXTURE_2D);
    shader.use();
    shader.uniform1i("uDiffuse", 0);
    shader.uniform1i("uSpecular", 1);
    shader.uniform1f("uShininess", material.shininess);
    shader.uniformMatrix4fv("uModel", 1, GL_FALSE, &mvp.model[0][0]);
    shader.uniformMatrix4fv("uView", 1, GL_FALSE, &mvp.view[0][0]);
    shader.uniformMatrix4fv("uProjection", 1, GL_FALSE, &mvp.projection[0][0]);
    shader.uniform3fv("uDirectionLight.direction", 1, &light.directionLight.direction[0]);
    shader.uniform3fv("uDirectionLight.ambient", 1, &light.directionLight.ambient[0]);
    shader.uniform3fv("uDirectionLight.diffuse", 1, &light.directionLight.diffuse[0]);
    shader.uniform3fv("uDirectionLight.specular", 1, &light.directionLight.specular[0]);
    shader.uniform3fv("uPointLights[0].position", 1, &light.pointLights[0].m_position[0]);
    shader.uniform1f("uPointLights[0].constant", light.pointLights[0].constant);
    shader.uniform1f("uPointLights[0].linear", light.pointLights[0].linear);
    shader.uniform1f("uPointLights[0].quadratic", light.pointLights[0].quadratic);
    shader.uniform3fv("uPointLights[0].ambient", 1, &light.pointLights[0].ambient[0]);
    shader.uniform3fv("uPointLights[0].diffuse", 1, &light.pointLights[0].diffuse[0]);
    shader.uniform3fv("uPointLights[0].specular", 1, &light.pointLights[0].specular[0]);
    shader.uniform3fv("uPointLights[1].position", 1, &light.pointLights[1].m_position[0]);
    shader.uniform1f("uPointLights[1].constant", light.pointLights[1].constant);
    shader.uniform1f("uPointLights[1].linear", light.pointLights[1].linear);
    shader.uniform1f("uPointLights[1].quadratic", light.pointLights[1].quadratic);
    shader.uniform3fv("uPointLights[1].ambient", 1, &light.pointLights[1].ambient[0]);
    shader.uniform3fv("uPointLights[1].diffuse", 1, &light.pointLights[1].diffuse[0]);
    shader.uniform3fv("uPointLights[1].specular", 1, &light.pointLights[1].specular[0]);
    shader.uniform3fv("uPointLights[2].position", 1, &light.pointLights[2].m_position[0]);
    shader.uniform1f("uPointLights[2].constant", light.pointLights[2].constant);
    shader.uniform1f("uPointLights[2].linear", light.pointLights[2].linear);
    shader.uniform1f("uPointLights[2].quadratic", light.pointLights[2].quadratic);
    shader.uniform3fv("uPointLights[2].ambient", 1, &light.pointLights[2].ambient[0]);
    shader.uniform3fv("uPointLights[2].diffuse", 1, &light.pointLights[2].diffuse[0]);
    shader.uniform3fv("uPointLights[2].specular", 1, &light.pointLights[2].specular[0]);
    shader.uniform3fv("uPointLights[3].position", 1, &light.pointLights[3].m_position[0]);
    shader.uniform1f("uPointLights[3].constant", light.pointLights[3].constant);
    shader.uniform1f("uPointLights[3].linear", light.pointLights[3].linear);
    shader.uniform1f("uPointLights[3].quadratic", light.pointLights[3].quadratic);
    shader.uniform3fv("uPointLights[3].ambient", 1, &light.pointLights[3].ambient[0]);
    shader.uniform3fv("uPointLights[3].diffuse", 1, &light.pointLights[3].diffuse[0]);
    shader.uniform3fv("uPointLights[3].specular", 1, &light.pointLights[3].specular[0]);
    shader.uniform3fv("uSpotLight.position", 1, &light.spotLight.position[0]);
    shader.uniform3fv("uSpotLight.direction", 1, &light.spotLight.direction[0]);
    shader.uniform1f("uSpotLight.innerCutOff", light.spotLight.innerCutOff);
    shader.uniform1f("uSpotLight.outerCutOff", light.spotLight.outerCutOff);
    shader.uniform1f("uSpotLight.constant", light.spotLight.constant);
    shader.uniform1f("uSpotLight.linear", light.spotLight.linear);
    shader.uniform1f("uSpotLight.quadratic", light.spotLight.quadratic);
    shader.uniform3fv("uSpotLight.ambient", 1, &light.spotLight.ambient[0]);
    shader.uniform3fv("uSpotLight.diffuse", 1, &light.spotLight.diffuse[0]);
    shader.uniform3fv("uSpotLight.specular", 1, &light.spotLight.specular[0]);
    m_vertexArray.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_vertexArray.unbind();
    shader.unuse();
    material.diffuse.unbind(GL_TEXTURE_2D);
    material.specular.unbind(GL_TEXTURE_2D);
}