#define STB_IMAGE_IMPLEMENTATION

#include "math.h"
#include "header/mainheader.h"
#include "header/Shader.h"
#include "header/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "header/MVP.h"
int id;
GLFWwindow* window;
float green;
Shader* ShaderNoColor = nullptr;
Shader* LightingShader = nullptr;
Shader* LightShader = nullptr;

MVP mvp;

void MainDisplay(){

    float timeValue = glfwGetTime()*2;

    auto view = glm::lookAt(glm::vec3(0,2,-3),glm::vec3(0,0,2),glm::vec3(0,1,0));

    mvp.SetView(view);
    mvp.SetModel(glm::identity<glm::mat4>());

    glClearColor(.2f,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LightingShader->use();
    unsigned int transformLoc = glGetUniformLocation(LightingShader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp.GetMVP()));
    LightingShader->setVec3("objectColor",.3,.5,.2);
    LightingShader->setVec3("lightColor",1,1,1);
;
    glBindVertexArray(cubeBufferObject);
    glDrawArrays(GL_TRIANGLES,0,36);

    glm::mat4 trans = glm::identity<glm::mat4>();
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    trans = glm::translate(trans,lightPos);
    trans = glm::scale(trans,glm::vec3(.2));
    mvp.SetModel(trans);
    LightShader->use();
    transformLoc = glGetUniformLocation(LightShader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp.GetMVP()));
    glBindVertexArray(lightSourceVAO);
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
    InitShader();
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
