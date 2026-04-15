#version 460 core

struct DirectionLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTextureCoord;

out vec4 oFragment;

uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;
uniform float uShininess;

uniform vec3 uCameraPosition;

uniform DirectionLight uDirectionLight;
uniform PointLight uPointLights[4];
uniform SpotLight uSpotLight;

vec3 diffuseTexture = texture(uDiffuse, fTextureCoord).rgb;
vec3 specularTexture = texture(uSpecular, fTextureCoord).rgb;
vec3 normal = normalize(fNormal);
vec3 cameraDirection = normalize(uCameraPosition - fPosition);

vec3 calculateDirectionLight();
vec3 calculatePointLight(PointLight pointLight);
vec3 calculateSpotLight();

void main()
{
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    // color += calculateDirectionLight();

    for (uint i = 0; i < 4; ++i)
        color += calculatePointLight(uPointLights[i]);

    color += calculateSpotLight();

    oFragment = vec4(color, 1.0f);
}

vec3 calculateDirectionLight()
{
    vec3 ambient = diffuseTexture * uDirectionLight.ambient;

    vec3 lightDirection = normalize(uDirectionLight.direction);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTexture * diffuseStrength * uDirectionLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTexture * specularStrength * uDirectionLight.specular;

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight pointLight)
{
    vec3 lightDirection = normalize(fPosition - pointLight.position);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTexture * diffuseStrength * pointLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTexture * specularStrength * pointLight.specular;

    float distance = length(pointLight.position - fPosition);
    float attenuation = 1.0f / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}

vec3 calculateSpotLight()
{
    vec3 lightDirection = normalize(fPosition - uSpotLight.position);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTexture * diffuseStrength * uSpotLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTexture * specularStrength * uSpotLight.specular;

    float distance = length(uSpotLight.position - fPosition);
    float attenuation = 1.0f / (uSpotLight.constant + uSpotLight.linear * distance + uSpotLight.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    float theta = dot(lightDirection, normalize(uSpotLight.direction));
    float epsilon = uSpotLight.innerCutOff - uSpotLight.outerCutOff;
    float intensity = clamp(((theta - uSpotLight.outerCutOff) / epsilon), 0.0f, 1.0f);

    diffuse *= intensity;
    specular *= intensity;

    return diffuse + specular;
}