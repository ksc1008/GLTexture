#include "header/mainheader.h"
#include "header/_Texture.h"

_Texture texture0 = _Texture("textures/Dirt.png");
_Texture texture1 = _Texture("textures/awesomeface.png", GL_RGBA);
_Texture texture2 = _Texture("textures/container2.png", GL_RGBA);
_Texture texture3 = _Texture("textures/container2_specular.png", GL_RGBA);

unsigned int cubeBufferArray;
unsigned int cubeBufferObject;
unsigned int lightSourceVAO;
unsigned int sphereBufferArray;
unsigned int sphereVAO;

int vertNum;
int width, height, nrChannels;

float* SphereVertices;

void InitTexture(){
    texture0.LoadTexture();
    texture1.LoadTexture();
    texture2.LoadTexture();
    texture3.LoadTexture();
}

void InitShader(){
    MainShader = new Shader("shaders/4.vShaderMultipleLights.glsl","shaders/4.fShaderMultipleLights.glsl");
    TextureShader = new Shader("shaders/3.vShaderFlashLight.glsl","shaders/3.fShaderFlashLight.glsl");
    LightShader = new Shader("shaders/vLightingShader.glsl","shaders/fLightSourceShader.glsl");
    ModelShader = new Shader("shaders/5.vShaderWithMesh.glsl","shaders/5.fShaderWithMesh.glsl");
}

void InitLights(){
    FlashLight = new Light();

    FlashLight->type = SPOT;
    FlashLight->constant = 1.0;
    FlashLight->linear = 0.14;
    FlashLight->quadratic = 0.07;
    FlashLight->ambient = glm::vec3(.1f,.1f,.1f);
    FlashLight->specular = glm::vec3(1.0f,1.0f,1.0f);
    FlashLight->diffuse = glm::vec3(1,1,1);
    FlashLight->cutOff = glm::cos(glm::radians(12.5f));
    FlashLight->outerCutOff = glm::cos(glm::radians(17.5f));

    PointLight0 = new Light();
    PointLight0->type = POINT;
    PointLight0->constant = 1.0;
    PointLight0->linear = 0.14;
    PointLight0->quadratic = 0.07;
    PointLight0->ambient = glm::vec3(.1f,.0f,.0f);
    PointLight0->specular = glm::vec3(1.0f,.0,0);
    PointLight0->diffuse = glm::vec3(1,0,0);
    PointLight0->position = glm::vec3(0.5,0.5,-2);

    PointLight1 = new Light();
    PointLight1->type = POINT;
    PointLight1->constant = 1.0;
    PointLight1->linear = 0.14;
    PointLight1->quadratic = 0.07;
    PointLight1->ambient = glm::vec3(0,0,0.1f);
    PointLight1->specular = glm::vec3(0,0,1);
    PointLight1->diffuse = glm::vec3(0,0,1);
    PointLight1->position = glm::vec3(0.5,0.5,2);
    FlashLight->AddToShader(MainShader);
    FlashLight->AddToShader(ModelShader);
    PointLight0->AddToShader(MainShader);
    PointLight0->AddToShader(ModelShader);
    PointLight1->AddToShader(MainShader);
    PointLight1->AddToShader(ModelShader);
}

void InitObject(){
    SphereVertices = CreateSphereWithNormal(50,50,.5,&vertNum);
    glGenBuffers(1,&cubeBufferArray);
    glGenBuffers(1,&sphereBufferArray);
    glGenVertexArrays(1,&lightSourceVAO);
    glGenVertexArrays(1,&sphereVAO);
    glGenVertexArrays(1,&cubeBufferObject);

    glBindVertexArray(cubeBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER,cubeBufferArray);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVerticesTexture),cubeVerticesTexture,GL_STATIC_DRAW);
    //vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER,sphereBufferArray);
    glBufferData(GL_ARRAY_BUFFER,vertNum*sizeof(float),SphereVertices,GL_STATIC_DRAW);
    //vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //Light Source Cube
    glBindVertexArray(lightSourceVAO);
    glBindBuffer(GL_ARRAY_BUFFER,cubeBufferArray);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}

void InitGlfw(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
}