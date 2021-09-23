#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores -----------------------------------

igvEscena3D::igvEscena3D() { 
	ejes = true;
	cajasY = 1;
	cajasX = 0;
	cajasZ = 0;
	separacionEjeX = 1.5;
	separacionEjeZ = 2.5;
}

igvEscena3D::~igvEscena3D() {}


// Metodos publicos ----------------------------------------

void igvEscena3D::creaCaja(GLfloat* color_pieza,float numCajasX, float numCajasY,float numCajasZ) {

	
	
	glMaterialfv(GL_FRONT, GL_EMISSION, color_pieza);

	//Tapa
	glPushMatrix();
	glTranslatef(numCajasX, 0.375f+numCajasY-1.0, numCajasZ);
	glScalef(1.2f, 0.25f, 2.2f);
	glutSolidCube(1);
	glPopMatrix();


	//Cuerpo
	glPushMatrix();
	
		glTranslatef(numCajasX, numCajasY - 1.0, numCajasZ);
	
	
	
	glScalef(1.0f, 1.0f, 2.0f);
	glutSolidCube(1);
	glPopMatrix();
}

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

void igvEscena3D::visualizar(int escena) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	//Luces
	GLfloat light0[] = { 10,8,9,1 }; // point light source
	glLightfv(GL_LIGHT0, GL_POSITION, light0);
	glEnable(GL_LIGHT0);

	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();

	// Escena seleccionada a través del menú (click botón derecho)
	if (escena == EscenaA) renderEscenaA();
	else if (escena == EscenaB) renderEscenaB();
	else if (escena == EscenaC) renderEscenaC();

	glPopMatrix(); // restaura la matriz de modelado
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvEscena3D::renderEscenaA() {
	// Practica 2a. Parte A.
	GLfloat color_pieza[] = { 0,0.25,0 };
	creaCaja(color_pieza,0,1,0);
	
}

void igvEscena3D::renderEscenaB() {
	GLfloat color_pieza[] = { 0,0,0.5 };

	// Practica 2a. Parte B.
	for (int i = 0; i < cajasY; i++){
		creaCaja(color_pieza,0,i+1,0);
	}
}


void igvEscena3D::renderEscenaC() {
	GLfloat color_pieza[] = { 0.5,0,0 };

	// Practica 2a. Parte C.
	
	//Siempre creamos una primera caja centrada en los ejes x,y,z
	for (int i = 0; i < cajasY; i++)
	{
		creaCaja(color_pieza, 0, i + 1, 0);
	}

	

	//Si pulsamos primero la tecla X este corresponde al segundo bucle,
	//asegurando que siempre que aumenten a la par 
	if (pulsaX) {
		for (int i = 0; i < cajasY; i++) {

			for (int j = 0; j < cajasX; j++) {

				for (int k = 0; k < cajasZ; k++) {
					creaCaja(color_pieza, 0, i + 1, (k * separacionEjeZ) + separacionEjeZ);
				}

				creaCaja(color_pieza, (j * separacionEjeX) + separacionEjeX, i + 1, 0);
			}
		}
	}


	//Si pulsamos primero la tecla 'Y' este corresponde al segundo bucle,
	//asegurando que siempre que aumenten a la par 
	if (pulsaZ) {
		for (int i = 0; i < cajasY; i++) {

			for (int k = 0; k < cajasZ; k++) {

				for (int j = 0; j < cajasX; j++) {
					creaCaja(color_pieza, (j * separacionEjeX) + separacionEjeX, i + 1, (k * separacionEjeZ) + separacionEjeZ);
				}

				creaCaja(color_pieza, 0, i + 1, (k * separacionEjeZ) + separacionEjeZ);
			}
		}
	}
	


	
	

}




