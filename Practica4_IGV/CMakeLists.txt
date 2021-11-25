cmake_minimum_required(VERSION 3.20)
project(Practica4_IGV)

set(CMAKE_CXX_STANDARD 11)

set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x86)

set(SDL2_image_INCLUDE_DIR C:/libs/SDL_image/include)
set(SDL2_image_LIB_DIR C:/libs/SDL_image/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_image_INCLUDE_DIR})
link_directories(${SDL2_image_LIB_DIR})

add_executable(Practica4_IGV pr4.cpp igvCamara.cpp igvColor.cpp igvColor.h igvFuenteLuz.cpp igvFuenteLuz.h igvMaterial.cpp igvMaterial.h igvTextura.cpp igvTextura.h igvCamara.h igvEscena3D.cpp igvEscena3D.h igvInterfaz.cpp igvInterfaz.h igvPunto3D.h igvPunto3D.cpp)

target_link_libraries(Practica4_IGV -lOpenGL32 -lfreeGLUT -lopengl32 -lglu32 SDL2main SDL2 SDL2_image)
