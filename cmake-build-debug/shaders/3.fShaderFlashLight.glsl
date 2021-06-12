#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float outerCutOff;
    float cutOff;
    bool enabled;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


uniform Light light;

out vec4 FragColor;
in vec3 FragPos;
in vec2 TexCoords;
smooth in vec3 NormalSmooth;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;

void main()
{
    vec3 result;
    vec3 lightDir = normalize(light.position-FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);
    float distance = length(light.position - FragPos);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance*distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));

    vec3 norm = normalize(NormalSmooth);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse*(diff*vec3(texture(material.diffuse,TexCoords))) * intensity;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    vec3 specular = light.specular*(spec * vec3(texture(material.specular,TexCoords)))*intensity;

    result = (diffuse+specular+ambient)*objectColor*attenuation;

    FragColor = vec4(result,1.0);
}