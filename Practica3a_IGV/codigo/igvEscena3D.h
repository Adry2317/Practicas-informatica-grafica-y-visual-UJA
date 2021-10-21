#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvMallaTriangulos.h"
#include "igvCilindro.h"
#include <iostream>

class igvEscena3D {
protected:
	// Atributos
	bool ejes;

	// Apartado A: Añadir aquí los atributos con los ángulos de rotación en X, Y y Z.
	GLfloat rotacionX;
	GLfloat rotacionY;
	GLfloat rotacionZ;
public:
	// atributos públicos
	igvMallaTriangulos* malla; // malla de triángulos asociada a la escena

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar();

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

	// Apartado A: métodos para incrementar los ángulos
	// Apartado A: métodos para obtener los valores de los ángulos

	void setRotacionX(GLfloat _angulo);
	void setRotacionY(GLfloat _angulo);
	void setRotacionZ(GLfloat _angulo);

	GLfloat getRotacionX();
	GLfloat getRotacionY();
	GLfloat getRotacionZ();
	

};

#endif
