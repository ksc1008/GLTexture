cmake_minimum_required(VERSION 3.17)
project(GL)

file(GLOB ROOT_CPP *.cpp)
file(GLOB ROOT_C *.c)
file(GLOB ROOT_HEADER *.h)
file(GLOB HEADER_FILES header/*.h)

include_directories(include)
link_directories(lib/x64)
link_directories(lib)

set(CMAKE_CXX_STANDARD 14)


#add_executable(GLTexture main.cpp glad.c header/mainheader.h Initiation.cpp Shader.cpp header/Shader.h header/stb_image.h _Texture.cpp header/_Texture.h MVP.cpp header/MVP.h Input.cpp Camera.cpp Camera.h CreateSphere.cpp VertexData.cpp Light.cpp header/Light.h Material.cpp header/Material.h header/OBJ_Loader.h Mesh.cpp header/Mesh.h Model.cpp header/Model.h)
add_executable(GL ${ROOT_CPP} ${ROOT_HEADER} ${HEADER_FILES} ${ROOT_C})
target_link_libraries(GL glfw3)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(GLM_VERSION "0.9.9")
project(glm VERSION ${GLM_VERSION} LANGUAGES CXX)
enable_testing()

add_subdirectory(glm)
add_library(glm::glm ALIAS glm)