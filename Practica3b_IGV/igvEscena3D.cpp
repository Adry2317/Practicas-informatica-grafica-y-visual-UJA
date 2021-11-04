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




//metodos

void igvEscena3D::pintarTorsoInferior(){
    glPushMatrix();
    glTranslated(0, 0.5, 0);
    glRotated(90, 1 ,0,0);
    gluCylinder(gluNewQuadric(), 1 ,1, 1,16,16);

    glPopMatrix();

}

void igvEscena3D::pintarTorsoSuperior() {
    glPushMatrix();
        glTranslated(0,1.5,0);
        glRotated(90, 1 ,0,0);
        gluCylinder(gluNewQuadric(), 1 ,1.0, 1,16,16);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.5,0);
        glutSolidSphere(1, 16,16);
    glPopMatrix();
}

void igvEscena3D::pintarCabeza() {
    GLfloat rojo[] = { 1,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };
    GLfloat negro[] = { 0,0,0,1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glPushMatrix();
        glTranslated(0.7,2.5,1);
        glutSolidSphere(0.7,16,16);

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, negro);
        glTranslated(0.2,0.5,0.8);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, negro);
        glTranslated(0.9,0.5,0.8);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

    glPopMatrix();

}


void igvEscena3D::pintarBrazos() {
    GLfloat negro[] = { 0,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };;
    glMaterialfv(GL_FRONT, GL_EMISSION, negro);
    glPushMatrix();
        glTranslatef(3,0,0);
        glRotatef(80, 1,0,0);
        glRotatef(-30, 0,1,0);
        gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glutSolidSphere(0.14,16,16);
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glTranslatef(0,0,0.82);
            glutSolidSphere(0.14,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, negro);
                glTranslatef(0,0,0.08);
                glRotatef(-30,1,0,0);
                gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);
            glPopMatrix();
        glPopMatrix();





    glPopMatrix();


}

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
    GLfloat rojo[] = { 1,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };


	///// Apartado B: aqu� hay que a�adir la visualizaci�n del �rbol del modelo utilizando la pila de matrices de OpenGL
	/////             se recomienda crear una m�todo auxiliar que encapsule todo el c�digo para la visualizaci�n
	/////             del modelo, dejando aqu� s�lo la llamada a ese m�todo, as� como distintas funciones una para cada
	/////			  parte del modelo. 
    pintarTorsoInferior();
    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);


    pintarTorsoSuperior();
    glPushMatrix();
        glTranslatef(0.7,2.5,1);
        glRotatef(12,0,1,1);
        glTranslatef(-0.7,-2.5,-1);
        pintarCabeza();
    glPopMatrix();

    pintarBrazos();
    glPopMatrix(); // restaura la matriz de modelado
}




