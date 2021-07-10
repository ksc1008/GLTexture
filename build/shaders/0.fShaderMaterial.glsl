#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

out vec4 FragColor;
in vec3 FragPos;
smooth in vec3 NormalSmooth;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform Material material;

void main()
{
    vec3 ambient = lightColor* material.ambient;

    vec3 norm = normalize(NormalSmooth);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = (diff*material.diffuse)*lightColor;

    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = (specularStrength * spec * material.specular) * lightColor;



    vec3 result = (ambient+diffuse+specular)*objectColor;
    FragColor = vec4(result,1.0);
}