cmake_minimum_required(VERSION 3.17)
project(GLTexture)

include_directories(include)
link_directories(lib/x64)
link_directories(lib)

set(CMAKE_CXX_STANDARD 14)


add_executable(GLTexture main.cpp MoveFunc.cpp lodepng.cpp lodepng.h glad.c header/mainheader.h Initiation.cpp Shader.cpp header/Shader.h header/stb_image.h Texture.cpp Texture.h)
target_link_libraries(GLTexture libopengl32.a  libfreeglut.a glu32.dll glfw3)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(GLM_VERSION "0.9.9")
project(glm VERSION ${GLM_VERSION} LANGUAGES CXX)
enable_testing()

add_subdirectory(glm)
add_library(glm::glm ALIAS glm)