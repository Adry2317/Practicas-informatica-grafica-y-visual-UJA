#define GL_SILENCE_DEPRECATION
#ifndef __IGVTEXTURA
#define __IGVTEXTURA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <iostream>
#include <vector>
#include "lodepng.h"

class igvTextura {

	protected:
		// Atributos
        unsigned int idTextura; // identificador de la textura

	public:
		// Constructores por defecto y destructor
        igvTextura();
		igvTextura(std::string fichero); // Textura cargada desde un fichero
		~igvTextura();

		// Metodos
		void aplicar(void); //Establece la textura como la activa
		void setIdTextura(unsigned int id) { this->idTextura = id;}
		unsigned int getIdTextura() { return this->idTextura; }
    
};

#endif

