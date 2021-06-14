#include "header/mainheader.h"
#include "header/Texture.h"

Texture texture0 = Texture("textures/Dirt.png");
Texture texture1 = Texture("textures/awesomeface.png", GL_RGBA);
Texture texture2 = Texture("textures/container2.png",GL_RGBA);
Texture texture3 = Texture("textures/container2_specular.png",GL_RGBA);

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