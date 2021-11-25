#include "igvCaja.h"
#include <iostream>
igvCaja::igvCaja() {
	color = new float[3];
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
    seleccionada = false;
};

igvCaja::igvCaja(float r, float g, float b) {
	color = new float[3];
	color[0] = r;
	color[1] = g;
	color[2] = b;
    seleccionada = false;
};

igvCaja::igvCaja(const igvCaja& orig) :color(orig.color){
};

igvCaja::~igvCaja() {
	delete color;
    
};

//Método para visualizar una caja
void igvCaja::visualizar() {
    if(seleccionada){
        float colorUsado[3];
        colorUsado[0] = 0.5;
        colorUsado[1] = 0.5;
        colorUsado[2] = 0.0;
        
        glMaterialfv(GL_FRONT, GL_EMISSION, colorUsado);
    }else{
        
        float colorUsado[3];
        colorUsado[0] = 0.0;
        colorUsado[1] = 0.5;
        colorUsado[2] = 0.0;
        glMaterialfv(GL_FRONT, GL_EMISSION, colorUsado);
    }
    
    glColor3fv(color);//Importante, es necesario para que lo reconozca el buffer de color a la hora de la selección.
	
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

void igvCaja::setSeleccionada(bool valor){
    seleccionada = valor;
}



