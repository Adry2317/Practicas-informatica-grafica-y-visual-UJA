#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>

class igvMallaTriangulos {
	protected:
		// Atributos

		long int num_vertices; // n�mero de v�rtices de la malla de tri�ngulos
		float *vertices; // array con las (num_vertices * 3) coordenadas de los v�rtices
		float *normales; // array con las (num_vertices * 3) coordenadas de la normal a cada v�rtice (s�lo para la generaci�n de la esfera)

		long int num_triangulos; // n�mero de tri�ngulos de la malla de tri�ngulos
		unsigned int *triangulos; // array con los (num_triangulos * 3) �ndices a los v�rtices de cada tri�ngulo

        bool normalActivada;
        bool sombreado;

	public:
		// Constructor y destructor
		
		igvMallaTriangulos();

		igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos);

		~igvMallaTriangulos();

		// M�todo con las llamadas OpenGL para visualizar la malla de tri�ngulos
		void visualizar();

		long int getNumVertices();
		float* getVertices();
		float* getNormal();
		long int getNumTriangulos();
		unsigned int* getTriangulos();
        bool get_normalActivada();
        void set_normalActivada(bool valor);
        bool get_sombreado();
        void set_sombreado(bool valor);
};

#endif
