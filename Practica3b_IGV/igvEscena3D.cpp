#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

	// Apartado C: inicializar los atributos para el control de los grados de libertad del modelo 

}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

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

///// Apartado B: M�todos para visualizar cada parte del modelo

////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).



	///// Apartado B: aqu� hay que a�adir la visualizaci�n del �rbol del modelo utilizando la pila de matrices de OpenGL
	/////             se recomienda crear una m�todo auxiliar que encapsule todo el c�digo para la visualizaci�n
	/////             del modelo, dejando aqu� s�lo la llamada a ese m�todo, as� como distintas funciones una para cada
	/////			  parte del modelo. 



	glPopMatrix(); // restaura la matriz de modelado
}




