cmake_minimum_required(VERSION 3.20)
project(Practica3bIGV)


set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(Practica3bIGV pr3b.cpp igvCamara.h igvCamara.cpp igvEscena3D.h igvEscena3D.cpp igvInterfaz.h igvInterfaz.cpp igvPunto3D.h igvPunto3D.cpp)

link_directories( /usr/local/include/ )

target_link_libraries( Practica3bIGV OpenGL::GL GLUT::GLUT GLEW::glew glfw)

