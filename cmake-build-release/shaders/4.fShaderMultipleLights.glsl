#version 330 core

#define POINT_NUM 20
#define DIRECTIONAL_NUM 10
#define SPOT_NUM 5

struct Material {
    sampler2D diffuse;
    sampler2D specular;

    vec3 diffuseColor;
    vec3 specularColor;

    bool hasDiffuseMap;
    bool hasSpecularMap;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float outerCutOff;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;
in vec3 FragPos;
in vec2 TexCoords;
smooth in vec3 NormalSmooth;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;

uniform PointLight pointLights[POINT_NUM];
uniform DirectionalLight directionalLights[DIRECTIONAL_NUM];
uniform SpotLight spotLights[SPOT_NUM];

uniform int pointNum;
uniform int directionalNum;
uniform int spotNum;

vec3 diffuseColor;
vec3 specularColor;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir,normal),0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    return (light.ambient * diffuseColor + light.diffuse * diffuseColor * diff + light.specular * specularColor * spec);
}
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);
    float diff = max(dot(lightDir,normal),0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance*distance));

    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diffuseColor * diff;
    vec3 specular = light.specular * specularColor * spec;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient+diffuse+specular);
}
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(light.position-FragPos);
    float diff = max(dot(lightDir,normal),0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance*distance));

    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diffuseColor * diff;
    vec3 specular = light.specular * specularColor * spec;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient+diffuse+specular);
}

void main()
{
    if(material.hasDiffuseMap){
        diffuseColor = vec3(texture(material.diffuse,TexCoords));
    }
    else{
        diffuseColor = material.diffuseColor;
    }
    if(material.hasSpecularMap){
        specularColor = vec3(texture(material.specular,TexCoords));
    }
    else{
        specularColor = material.specularColor;
    }

    vec3 norm = normalize(NormalSmooth);
    vec3 result = vec3(0);
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0;i<directionalNum;i++){
        result += CalculateDirectionalLight(directionalLights[i],norm,viewDir);
    }
    for(int i = 0;i<pointNum;i++){
        result += CalculatePointLight(pointLights[i],norm,viewDir);
    }
    for(int i = 0;i<spotNum;i++){
        result += CalculateSpotLight(spotLights[i],norm,viewDir);
    }

    result *= objectColor;

    FragColor = vec4(result,1.0);
}