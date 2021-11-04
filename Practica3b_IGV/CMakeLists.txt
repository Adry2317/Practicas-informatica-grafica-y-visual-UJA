cmake_minimum_required(VERSION 3.20)
project(Practica3b_IGV)

set(CMAKE_CXX_STANDARD 11)

add_executable(Practica3b_IGV pr3b.cpp igvCamara.cpp igvCamara.h igvEscena3D.cpp igvEscena3D.h igvInterfaz.cpp igvInterfaz.h igvPunto3D.h igvPunto3D.cpp)

target_link_libraries(Practica3b_IGV -lOpenGL32 -lfreeGLUT -lopengl32 -lglu32)
