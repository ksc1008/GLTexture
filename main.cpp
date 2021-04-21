#define STB_IMAGE_IMPLEMENTATION

#include "math.h"
#include "header/mainheader.h"
#include "header/Shader.h"
#include "header/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "header/MVP.h"
//#include "GL/glu.h"
int id;
GLFWwindow* window;
float green;
Shader* myShader = nullptr;
Shader* ShaderNoColor = nullptr;

MVP mvp;

void MainDisplay(){

    float timeValue = glfwGetTime()*2;

    glm::mat4 trans = glm::identity<glm::mat4>();
    trans = glm::translate(trans,glm::vec3(timeValue*0.1,0,0));
    trans = glm::rotate(trans,timeValue*3,glm::vec3(0.5,0.5,1));
    float size = fmax(0,1-timeValue*0.1);
    trans= glm::scale(trans,glm::vec3(size,size,size));
    mvp.SetModel(trans);


    glClearColor(.2f,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ShaderNoColor->setInt("texture1",0);
    ShaderNoColor->setInt("texture2",1);
    unsigned int transformLoc = glGetUniformLocation(ShaderNoColor->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp.GetMVP()));


    glActiveTexture(GL_TEXTURE0);
    texture0.Bind();
    glActiveTexture(GL_TEXTURE1);
    texture1.Bind();
    //glBindVertexArray(triangleBufferObject);
    //glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
    //glBindVertexArray(0);
    ShaderNoColor->use();
    glBindVertexArray(cubeBufferObject);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(int argc, char**argv) {
    stbi__vertically_flip_on_load =true;
    InitGlfw();
    window = glfwCreateWindow(800,600,"HAHA",NULL,NULL);
    if(window == NULL){
        std::cout <<"OOPS"<<"\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    myShader = new Shader("shaders/vertexShader.glsl","shaders/fragmentShader.glsl");
    ShaderNoColor = new Shader("shaders/vertexShaderNoColor.glsl","shaders/fragmentShaderNoColor.glsl");
    InitTexture();
    InitObject();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 600);
    mvp.SetPerspective(glm::radians(45.0f),4.0f/3.0f,0.1f,100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
    mvp.SetView(view);
    while(!glfwWindowShouldClose(window))
    {
        MainDisplay();
    }
    glfwTerminate();
    return 0;
}
