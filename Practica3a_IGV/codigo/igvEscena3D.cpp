#include <cstdlib>
#include <stdio.h>
#include <cmath>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"


// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;
	rotacionX = 0;
	rotacionY = 0;
	rotacionZ = 0;
	// Apartado B: Inserta el código para crear un cilindro
	malla = new igvCilindro(1,1,40,2);
}

igvEscena3D::~igvEscena3D() {
	delete malla;
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

void igvEscena3D::visualizar(void) {
	GLfloat color_malla[] = { 0,0.25,0 };
	// crear luces
	GLfloat luz0[4] = { 2.0,2.5,3.0,1 }; // luz puntual para visualizar el cubo

	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();


	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena
	glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
	glRotatef(getRotacionX(), 1, 0, 0);
	glRotatef(getRotacionY(), 0, 1, 0);
	glRotatef(getRotacionZ(), 0, 0, 1);

	// Apartado B: la siguiente llamada hay que sustituirla por la llamada al método visualizar de la malla
	//GLUquadric* cyl = gluNewQuadric();
	//gluCylinder(cyl, 1, 1, 1, 20, 5);
	//gluDeleteQuadric(cyl);
	//cyl=nullptr;
	
	
	for (int i = 0; i < malla->getNumVertices()*3; i=i+3) {

		//std::cout << "x: " << pru.vertices[i] << " y: " << pru.vertices[i + 1] << " z: " << pru.vertices[i + 2] << std::endl;
		glPushMatrix();
		glTranslatef(malla->getVertices()[i], malla->getVertices()[i + 1], malla->getVertices()[i + 2]);
		glutSolidCube(0.1);
		glPopMatrix();
	}
	
	glPopMatrix(); // restaura la matriz de modelado
}

void igvEscena3D::setRotacionX(GLfloat _angulo) {
	this->rotacionX = _angulo;
}

void igvEscena3D::setRotacionY(GLfloat _angulo) {
	this->rotacionY = _angulo;
}

void igvEscena3D::setRotacionZ(GLfloat _angulo) {
	this->rotacionZ = _angulo;
}

GLfloat igvEscena3D::getRotacionX(){
	return this->rotacionX;
}

GLfloat igvEscena3D::getRotacionY() {
	return this->rotacionY;
}

GLfloat igvEscena3D::getRotacionZ() {
	return this->rotacionZ;
}
