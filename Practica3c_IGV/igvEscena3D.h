#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "igvCaja.h"

class igvEscena3D {
protected:
	// Otros atributos
    int r,g,b;
	bool ejes;
	std::vector<igvCaja*> cajas; //Array con todas los objetos de la escena

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// m�todo con las llamadas OpenGL para visualizar la escena
	void visualizar(void);
	void visualizarVB(void);

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };
	std::vector<igvCaja*>& getCajas() { return cajas; };
};

#endif
