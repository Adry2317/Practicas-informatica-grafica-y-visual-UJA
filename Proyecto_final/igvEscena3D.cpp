#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;


	// Apartado C: inicializar los atributos para el control de los grados de libertad del modelo 
    anguloTorsoSuperior = 30.0;
    anguloCabeza = 12.0;
    anguloPirnaIzquierda = 0;
    anguloPiernaDerecha = 0;
    anguloBrazoDerecho = 0;
    anguloBrazoIzquierdo = 0;
    anguloAntebrazoIzquierdo = -30.0;
    anguloAntebrazoDerecho = 30.0;
    animacion = false;

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





/**
 * Pinta la zona del torso inferior
 * */
void igvEscena3D::pintarTorsoInferior(){
    glPushMatrix();
    glTranslated(0, 0.5, 0);
    glRotated(90, 1 ,0,0);
    gluCylinder(gluNewQuadric(), 1 ,1, 1,16,16);

    glPopMatrix();

}

/**
 *Pinta el torso superior
 * */
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
/**
 * Pinta la cabeza
 * */
void igvEscena3D::pintarCabeza() {
    GLfloat verde[] = { 0,1,0,1.0 };
    GLfloat ojos[] = { 0,0,0,1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION,verde);
    glPushMatrix();
        glTranslated(0.7,2.5,1);//Cabeza
        glutSolidSphere(0.7,16,16);

        //Pintar ojos
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, ojos);
        glTranslated(-0.2,0.5,0.4);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, ojos);
        glTranslated(0.4,0.4,0.4);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

    glPopMatrix();

}

/**
 *
 */
void igvEscena3D::pintarBrazos() {
    GLfloat negro[] = { 0,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };;
    //brazo izquierdo
    glMaterialfv(GL_FRONT, GL_EMISSION, negro);
    glPushMatrix();

        glTranslatef(-1,1.5,0.3);
        glRotatef(80, 1,0,0);
        glRotatef(-30, 0,1,0);
        glRotatef(anguloBrazoIzquierdo,1,0,0);//
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
                glRotatef(anguloAntebrazoIzquierdo,1,0,0);
                gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

                glPushMatrix();
                    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                    glTranslatef(0,0,0.93);
                    glScalef(0.3,0.2,0.3);
                    glutSolidCube(1);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Brazo derecho.

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, negro);
        glTranslatef(1,1.5,0.3);
        glRotatef(80, 1,0,0);
        glRotatef(30, 0,1,0);
        glRotatef(anguloBrazoDerecho,1,0,0);
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
                glRotatef(anguloAntebrazoDerecho,-1,0,0);
                gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

                glPushMatrix();
                    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                    glTranslatef(0,0,0.93);
                    glScalef(0.3,0.2,0.3);
                    glutSolidCube(1);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


}

/**
 * Función encargada de pintar las piernas
 */
void igvEscena3D::pintarPiernas() {
    GLfloat negro[] = { 0,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };;
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, verde);
        glTranslatef(-0.6,-0.5,0);
        glRotatef(anguloPirnaIzquierda,1,0,0);
        glutSolidSphere(0.14,16,16);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, negro);
            glRotatef(90,1,0,0);
            gluCylinder(gluNewQuadric(), 0.14 ,0.14, 1.6,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                glTranslatef(0,0,1.8);
                glRotatef(90,1,0,0);
                glRotatef(-5,0,1,0);
                glScalef(0.7,0.2,1);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    //pierna derecha
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, verde);
        glTranslatef(0.6,-0.5,0);
        glRotatef(anguloPiernaDerecha,1,0,0);
        glutSolidSphere(0.14,16,16);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, negro);
            glRotatef(90,1,0,0);
            gluCylinder(gluNewQuadric(), 0.14 ,0.14, 1.6,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                glTranslatef(0,0,1.8);
                glRotatef(90,1,0,0);
                glRotatef(-5,0,1,0);
                glScalef(0.7,0.2,1);
                glutSolidCube(1);
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

    glPushMatrix();
    glRotatef(30,0,1,0);
    pintarTorsoInferior();
    pintarPiernas();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);


    glPushMatrix();
    glRotated(anguloTorsoSuperior, 0 ,1,0);
    pintarTorsoSuperior();
    pintarBrazos();
        glPushMatrix();
            glTranslatef(0,2.5,0.5);
            glRotatef(anguloCabeza,0,1,1);
            glTranslatef(-0.7,-2.5,-1);
            pintarCabeza();
        glPopMatrix();
    glPopMatrix();




    glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::setAnguloCabeza(float anguloCabeza) {
    igvEscena3D::anguloCabeza = anguloCabeza;
}

void igvEscena3D::setAnguloTorsoSuperior(float anguloTorsoSuperior) {
    igvEscena3D::anguloTorsoSuperior = anguloTorsoSuperior;
}

void igvEscena3D::setAnguloBrazoIzquierdo(float anguloBrazoIzquierdo) {
    igvEscena3D::anguloBrazoIzquierdo = anguloBrazoIzquierdo;
}

void igvEscena3D::setAnguloBrazoDerecho(float anguloBrazoDerecho) {
    igvEscena3D::anguloBrazoDerecho = anguloBrazoDerecho;
}

void igvEscena3D::setAnguloAntebrazoIzquierdo(float anguloAntebrazoIzquierdo) {
    igvEscena3D::anguloAntebrazoIzquierdo = anguloAntebrazoIzquierdo;
}

void igvEscena3D::setAnguloAntebrazoDerecho(float anguloAntebrazoDerecho) {
    igvEscena3D::anguloAntebrazoDerecho = anguloAntebrazoDerecho;
}

float igvEscena3D::getAnguloCabeza() const {
    return anguloCabeza;
}

float igvEscena3D::getAnguloTorsoSuperior() const {
    return anguloTorsoSuperior;
}

float igvEscena3D::getAnguloBrazoIzquierdo() const {
    return anguloBrazoIzquierdo;
}

float igvEscena3D::getAnguloBrazoDerecho() const {
    return anguloBrazoDerecho;
}

float igvEscena3D::getAnguloAntebrazoIzquierdo() const {
    return anguloAntebrazoIzquierdo;
}

float igvEscena3D::getAnguloAntebrazoDerecho() const {
    return anguloAntebrazoDerecho;
}

void igvEscena3D::setAnguloPirnaIzquierda(float anguloPirnaIzquierda) {
    igvEscena3D::anguloPirnaIzquierda = anguloPirnaIzquierda;
}

void igvEscena3D::setAnguloPiernaDerecha(float anguloPiernaDerecha) {
    igvEscena3D::anguloPiernaDerecha = anguloPiernaDerecha;
}

float igvEscena3D::getAnguloPirnaIzquierda() const {
    return anguloPirnaIzquierda;
}

float igvEscena3D::getAnguloPiernaDerecha() const {
    return anguloPiernaDerecha;
}

void igvEscena3D::setAnimacion(bool animacion) {
    igvEscena3D::animacion = animacion;
}

bool igvEscena3D::isAnimacion() const {
    return animacion;
}






