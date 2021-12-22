//
// Created by Jose Antonio on 18/12/21.
//
#define GL_SILENCE_DEPRECATION
#ifndef PRACTICA3B_IGV_FACE_H
#define PRACTICA3B_IGV_FACE_H

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <glm/glm.hpp>

class Face {
    private:
        float* color;
        bool seleccionada;
        float rotacion;
        glm::vec3 posicion;
    public:
        Face();
        Face(float r, float g, float b, glm::vec3 posicion);
        Face(const Face& orig);
        virtual ~Face();

        void visualizar();

        float *getColor() const;

        void setColor(float *color);

        bool isSeleccionada() const;

        void setSeleccionada(bool seleccionada);

        float getRotacion() const;

        void setRotacion(float rotacion);

        GLubyte* getColorByte();
};


#endif //PRACTICA3B_IGV_FACE_H
