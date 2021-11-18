#include "igvCaja.h"
#include <iostream>
igvCaja::igvCaja() {
	color = new float[3];
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
};

igvCaja::igvCaja(float r, float g, float b, float _r, float _g, float _b) {
    colorSeleccion = new float [3];
	color = new float[3];
	color[0] = r;
	color[1] = g;
	color[2] = b;
    colorSeleccion[0] = _r;
    colorSeleccion[1] = _g;
    colorSeleccion[2] = _b;
    seleccionada = false;
};

igvCaja::igvCaja(const igvCaja& orig) :color(orig.color){
};

igvCaja::~igvCaja() {
	delete color;
    delete colorSeleccion;
};

//M�todo para visualizar una caja
void igvCaja::visualizar() {

    if(seleccionada){
        float colorSeleccion[3] = {0.5, 0.5, 0.0};
        std::cout<<"seleccionada";
        glMaterialfv(GL_FRONT,GL_EMISSION,colorSeleccion);
    }else {
        glMaterialfv(GL_FRONT, GL_EMISSION, color);
    }
	glColor3fv(colorSeleccion);//Importante, es necesario para que lo reconozca el buffer de color a la hora de la selecci�n.
	
	glPushMatrix();
	glScalef(1, 1, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.4, 0);
	glScalef(1.1, 0.2, 2.1);
	glutSolidCube(1);
	glPopMatrix();
};

float* igvCaja::getColor() {
	return color;
}

GLubyte* igvCaja::getColorByte() {
	GLubyte colorubyte[3];
	colorubyte[0] = (GLubyte)(color[0] * 255);
	colorubyte[1] = (GLubyte)(color[1] * 255);
	colorubyte[2] = (GLubyte)(color[2] * 255);

	return colorubyte;
}

float *igvCaja::getColorSeleccion() const {
    return colorSeleccion;
}

void igvCaja::setColor(float *color) {
    igvCaja::color = color;
}

void igvCaja::setColorSeleccion(float *colorSeleccion) {
    igvCaja::colorSeleccion = colorSeleccion;
}

GLubyte *igvCaja::getColorSeleccionByte() {
    GLubyte colorubyte[3];
    std::cout<<colorSeleccion[0]<<std::endl;
    std::cout<<colorSeleccion[1]<<std::endl;
    std::cout<<colorSeleccion[2]<<std::endl;
    colorubyte[0] = (GLubyte)(colorSeleccion[0] * 255);
    colorubyte[1] = (GLubyte)(colorSeleccion[1] * 255);
    colorubyte[2] = (GLubyte)(colorSeleccion[2] * 255);

    return colorubyte;
}

bool igvCaja::isSeleccionada() const {
    return seleccionada;
}

void igvCaja::setSeleccionada(bool seleccionada) {
    igvCaja::seleccionada = seleccionada;
}
