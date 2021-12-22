//
// Created by Jose Antonio on 18/12/21.
//

#include "Face.h"

Face::Face() {
    color = new float[3];
    color[0] = 0.0;
    color[1] = 0.0;
    color[2] = 0.0;
    seleccionada = false;
    rotacion = 0;
    posicion = glm::vec3(0,0,0);
}

Face::Face(float r, float g, float b, glm::vec3 posicion) {
    color = new float[3];
    color[0] = r;
    color[1] = g;
    color[2] = b;
    seleccionada = false;
    rotacion = 0;
    this->posicion = posicion;
}

Face::Face(const Face &orig) {

}

Face::~Face() {
    delete color;
}

void Face::visualizar() {
    glColor3fv(color); //Importante, es necesario para que lo reconozca el buffer de color a la hora de la selección.
    GLfloat blanco[] = { 1,1,1,1.0 };
    glPushMatrix();
    glTranslatef(posicion.x,posicion.y,posicion.z);
    glRotatef(-90, 1, 0, 0);
    glRotatef(rotacion, 0, 0, 1);
    GLUquadric *obj = gluNewQuadric();
    gluQuadricTexture(obj, GL_TRUE);
    glMaterialfv(GL_FRONT, GL_EMISSION, blanco);
    gluSphere(obj, 1, 150, 150);
    gluDeleteQuadric(obj);
    glPopMatrix();
}

GLubyte* Face::getColorByte() {
    GLubyte colorubyte[3];
    colorubyte[0] = (GLubyte)(color[0] * 255);
    colorubyte[1] = (GLubyte)(color[1] * 255);
    colorubyte[2] = (GLubyte)(color[2] * 255);

    return colorubyte;
}

float *Face::getColor() const {
    return color;
}

void Face::setColor(float *color) {
    Face::color = color;
}

bool Face::isSeleccionada() const {
    return seleccionada;
}

void Face::setSeleccionada(bool seleccionada) {
    Face::seleccionada = seleccionada;
}

float Face::getRotacion() const {
    return rotacion;
}

void Face::setRotacion(float rotacion) {
    Face::rotacion += rotacion;
}
