#ifndef __IGVCAJA
#define __IGVCAJA

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
    float* colorSeleccion;
    bool seleccionada;
public:
	//Constructores y destructores
	igvCaja();
	igvCaja(float r, float g, float b, float _r, float _g, float _b);
	igvCaja(const igvCaja& orig);
	~igvCaja();

	//M�todo para visualizar una caja
	void visualizar();

	//Devuelve el color
	float* getColor();

    float *getColorSeleccion() const;

    GLubyte* getColorByte();

    void setColor(float *color);

    void setColorSeleccion(float *colorSeleccion);
    //Para comparar con el pixel obtenido en la selecci�n

    GLubyte* getColorSeleccionByte();

    bool isSeleccionada() const;

    void setSeleccionada(bool seleccionada);
};

#endif
