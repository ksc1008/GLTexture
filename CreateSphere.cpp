#include <vector>
#include "header/mainheader.h"
#include "glm/glm.hpp"
#define _USE_MATH_DEFINES
#include <math.h>


int oldindex = -1;
int newindex = -1;

typedef struct vec3{
    double x;
    double y;
    double z;
    vec3(float _x,float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }
    vec3 cross(vec3 vector){
        return vec3(y*vector.z-z-vector.y,z*vector.x-x*vector.z,x*vector.y-y*vector.x);
    }
}vec3;

void AllocVec3(float* arr, std::vector<vec3>&vector, int fromi, int toi){
    newindex = toi;
    arr[toi] = vector[fromi].x;
    arr[toi+1] = vector[fromi].y;
    arr[toi+2] = vector[fromi].z;

    oldindex = toi+2;
}

void AllocNormal(float* arr, std::vector<vec3>&vector, int from, int toi){
    vec3 vec = vector[from];
    glm::vec3 v = glm::vec3(vec.x,vec.y,vec.z);
    glm::vec3 norm = glm::normalize(v);
    arr[toi] = norm.x;
    arr[toi+1] = norm.y;
    arr[toi+2] = norm.z;
}

void AllocVec3WithNormal(float* arr, std::vector<vec3>&vector, int from1,int from2,int from3, int toi){
    AllocVec3(arr,vector,from1,2*toi);
    AllocNormal(arr,vector,from1,2*toi+3);
    AllocVec3(arr,vector,from2,2*toi+6);
    AllocNormal(arr,vector,from2,2*toi+9);
    AllocVec3(arr,vector,from3,2*toi+12);
    AllocNormal(arr,vector,from3,2*toi+15);
}

float* CreateSphereWithNormal(int stack, int slice, float radius,int* vertexNum){
    *vertexNum = (stack-1)*slice*36;
    float* vertices = new float[(stack-1)*slice*36];
    double _z;
    double _r;
    double _x;
    double _y;
    std::vector<vec3>vertex = std::vector<vec3>();

    vertex.emplace_back(0,radius,0);
    for(int i = 1;i<stack;i++){
        _z = radius-(2*radius)/stack*i;
        _r = sqrt(radius*radius-_z*_z);
        float theta = M_PI * 2 / slice;
        for(int s = 0;s<slice;s++){
            _x = cos(theta*s)*_r;
            _y = sin(theta*s)*_r;
            vertex.emplace_back(_x,_z,_y);
        }
    }
    vertex.emplace_back(0,-radius,0);

    //맨 위 slice 개의 삼각형 할당
    for(int i = 0;i<slice-1;i++){
        AllocVec3WithNormal(vertices,vertex,0,i+1,i+2,9*i);
    }
    AllocVec3WithNormal(vertices,vertex,0,slice,1,9*(slice-1));
    int indexi;
    int indexj;
    //그 아래로 stack-1 층의 사각형을 삼각형으로 나누어 할당
    for(int i = 1;i<stack-1;i++){
        indexi = 9*slice + (i-1)*(slice*18);
        for(int j = 0;j<slice-1;j++){
            indexj = j*18;
            AllocVec3WithNormal(vertices,vertex,1+slice*(i-1)+j,1+slice*(i)+j,1+slice*(i)+j+1,indexi+indexj);
            AllocVec3WithNormal(vertices,vertex,1+slice*(i-1)+j,1+slice*(i)+j+1,1+slice*(i-1)+j+1,indexi+indexj+9);
        }
        int j = slice-1;
        indexj = j*18;
        AllocVec3WithNormal(vertices,vertex,1+slice*(i-1)+j,1+slice*(i)+j,1+slice*(i),indexi+indexj);
        AllocVec3WithNormal(vertices,vertex,1+slice*(i-1)+j,1+slice*(i),1+slice*(i-1),indexi+indexj+9);
    }
    int index = 9*(slice) + (stack-2)*slice*18;
    //맨 아래 slice 개의 삼각형 할당
    for(int i = 0;i<slice-1;i++){
        AllocVec3WithNormal(vertices,vertex,1+slice*(stack-2)+i,vertex.size()-1,1+slice*(stack-2)+i+1,index+9*i);
    }
    AllocVec3WithNormal(vertices,vertex,1+slice*(stack-2)+slice-1,vertex.size()-1,1+slice*(stack-2)-1,index+9*slice-9);
    return vertices;
}

float* CreateSphere(int stack, int slice, float radius,int* vertexNum){
    *vertexNum = (stack-1)*slice*18;
    float* vertices = new float[(stack-1)*slice*18];
    double _z;
    double _r;
    double _x;
    double _y;
    std::vector<vec3>vertex = std::vector<vec3>();

    vertex.emplace_back(0,radius,0);
    for(int i = 1;i<stack;i++){
        _z = radius-(2*radius)/stack*i;
        _r = sqrt(radius*radius-_z*_z);
        float theta = M_PI*2/slice;
        for(int s = 0;s<slice;s++){
            _x = cos(theta*s)*_r;
            _y = sin(theta*s)*_r;
            vertex.emplace_back(_x,_z,_y);
        }
    }
    vertex.emplace_back(0,-radius,0);

    //맨 위 slice 개의 삼각형 할당
    for(int i = 0;i<slice-1;i++){
        AllocVec3(vertices,vertex,0,9*i);
        AllocVec3(vertices,vertex,i+1,9*i+3);
        AllocVec3(vertices,vertex,i+2,9*i+6);
    }
    AllocVec3(vertices,vertex,0,9*(slice-1));
    AllocVec3(vertices,vertex,slice,9*(slice-1)+3);
    AllocVec3(vertices,vertex,1,9*(slice-1)+6);
    int indexi;
    int indexj;
    //그 아래로 stack-1 층의 사각형을 삼각형으로 나누어 할당
    for(int i = 1;i<stack-1;i++){
        indexi = 9*slice + (i-1)*(slice*18);
        for(int j = 0;j<slice-1;j++){
            indexj = j*18;
            AllocVec3(vertices,vertex,1+slice*(i-1)+j,indexi+indexj);
            AllocVec3(vertices,vertex,1+slice*(i)+j,indexi+indexj+3);
            AllocVec3(vertices,vertex,1+slice*(i)+j+1,indexi+indexj+6);
            AllocVec3(vertices,vertex,1+slice*(i-1)+j,indexi+indexj+9);
            AllocVec3(vertices,vertex,1+slice*(i)+j+1,indexi+indexj+12);
            AllocVec3(vertices,vertex,1+slice*(i-1)+j+1,indexi+indexj+15);
        }
        int j = slice-1;
        indexj = j*18;
        AllocVec3(vertices,vertex,1+slice*(i-1)+j,indexi+indexj);
        AllocVec3(vertices,vertex,1+slice*(i)+j,indexi+indexj+3);
        AllocVec3(vertices,vertex,1+slice*(i),indexi+indexj+6);
        AllocVec3(vertices,vertex,1+slice*(i-1)+j,indexi+indexj+9);
        AllocVec3(vertices,vertex,1+slice*(i),indexi+indexj+12);
        AllocVec3(vertices,vertex,1+slice*(i-1),indexi+indexj+15);
    }
    int index = 9*(slice) + (stack-2)*slice*18;
    //맨 아래 slice 개의 삼각형 할당
    for(int i = 0;i<slice-1;i++){
        AllocVec3(vertices,vertex,1+slice*(stack-2)+i,index+9*i);
        AllocVec3(vertices,vertex,vertex.size()-1,index+9*i+3);
        AllocVec3(vertices,vertex,1+slice*(stack-2)+i+1,index+9*i+6);
    }
    AllocVec3(vertices,vertex,1+slice*(stack-2)+slice-1,index+9*slice-9);
    AllocVec3(vertices,vertex,vertex.size()-1,index+9*slice-6);
    AllocVec3(vertices,vertex,1+slice*(stack-2)-1,index+9*slice-3);
    return vertices;
}