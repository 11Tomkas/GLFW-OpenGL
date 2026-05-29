#version 460 core

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 oColor;

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

uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;
uniform float uShininess;
uniform vec3 uCameraPosition;
uniform DirectionLight uDirectionLight;
uniform PointLight uPointLights[4];
uniform SpotLight uSpotLight;

vec3 normal = normalize(fNormal);
vec3 diffuseTex = texture(uDiffuse, fTexCoord).rgb;
vec3 specularTex = texture(uSpecular, fTexCoord).rgb;
vec3 cameraDirection = normalize(uCameraPosition - fPosition);

vec3 calculateDirectionLight(DirectionLight directionLight);
vec3 calculatePointLight(PointLight pointLight);
vec3 calculateSpotLight(SpotLight spotLight);

void main()
{
    vec3 color = vec3(0.0f);

    color += calculateDirectionLight(uDirectionLight);
    for (uint i = 0; i < 4; ++i)
        color += calculatePointLight(uPointLights[i]);
    color += calculateSpotLight(uSpotLight);

    oColor = vec4(color, 1.0f);
}

vec3 calculateDirectionLight(DirectionLight directionLight)
{
    vec3 ambient = diffuseTex.rgb * directionLight.ambient;

    vec3 lightDirection = normalize(directionLight.direction);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTex * diffuseStrength * directionLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTex * specularStrength * directionLight.specular;

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight pointLight)
{
    vec3 lightDirection = normalize(fPosition - pointLight.position);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTex * diffuseStrength * pointLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTex * specularStrength * pointLight.specular;

    float _distance = length(pointLight.position - fPosition);
    float attenuation = 1.0f / (pointLight.constant + _distance * pointLight.linear + (_distance * _distance) * pointLight.quadratic);

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}

vec3 calculateSpotLight(SpotLight spotLight)
{
    vec3 lightDirection = normalize(fPosition - spotLight.position);
    float diffuseStrength = max(dot(-lightDirection, normal), 0.0f);
    vec3 diffuse = diffuseTex * diffuseStrength * spotLight.diffuse;

    vec3 reflectDirection = reflect(lightDirection, normal);
    float specularStrength = pow(max(dot(cameraDirection, reflectDirection), 0.0f), uShininess);
    vec3 specular = specularTex * specularStrength * spotLight.specular;

    float _distance = length(spotLight.position - fPosition);
    float attenuation = 1.0f / (spotLight.constant + _distance * spotLight.linear + (_distance * _distance) * spotLight.quadratic);

    float theta = dot(lightDirection, normalize(spotLight.direction));
    float epsilon = spotLight.innerCutOff - spotLight.outerCutOff;
    float intensity = clamp(((theta - spotLight.outerCutOff) / epsilon), 0.0f, 1.0f);

    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return diffuse + specular;
}