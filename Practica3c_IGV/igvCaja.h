#ifndef __IGVCAJA
#define __IGVCAJA
#define GL_SILENCE_DEPRECATION

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

class igvCaja
{
private:
	float* color;
    bool seleccionada;
public:
	//Constructores y destructores
	igvCaja();
	igvCaja(float r, float g, float b);
	igvCaja(const igvCaja& orig);
	~igvCaja();

	//M�todo para visualizar una caja
	void visualizar();

	//Devuelve el color
	float* getColor();
	GLubyte* getColorByte(); //Para comparar con el pixel obtenido en la selecci�n

    
    void setSeleccionada(bool valor);
};

#endif
