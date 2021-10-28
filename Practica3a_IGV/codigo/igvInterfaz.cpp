#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear c�maras
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(3.0,2.0,4),igvPunto3D(0,0,0),igvPunto3D(0,1.0,0),
		                                -1*1.5, 1*1.5, -1*1.5, 1*1.5, -1*3, 200);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_ancho_ventana,_alto_ventana);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
  glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
    case 'x': // Apartado A: rotar X positivo 
		if (interfaz.escena.getRotacionX() < 360) {
			interfaz.escena.setRotacionX(interfaz.escena.getRotacionX() + 10);
		}
		
		break;
    case 'X': // Apartado A: rotar X negativo 
		if (interfaz.escena.getRotacionX() > 0) {
			interfaz.escena.setRotacionX(interfaz.escena.getRotacionX() - 10);
		}
		
		break;
    case 'y': // Apartado A: rotar Y positivo 
		if (interfaz.escena.getRotacionY() < 360) {
			interfaz.escena.setRotacionY(interfaz.escena.getRotacionY() + 10);
		}
		
		break;
    case 'Y': // Apartado A: rotar y negativo 
		if (interfaz.escena.getRotacionY() > 0) {
			interfaz.escena.setRotacionY(interfaz.escena.getRotacionY() - 10);
		}
		
		break;
    case 'z': // Apartado A: rotar z positivo 
		if (interfaz.escena.getRotacionZ() < 360) {
			interfaz.escena.setRotacionZ(interfaz.escena.getRotacionZ() + 10);
		}
		break;
    case 'Z': // Apartado A: rotar Z negativo 
		if (interfaz.escena.getRotacionZ() > 0) {
			interfaz.escena.setRotacionZ(interfaz.escena.getRotacionZ() - 10);
		}
		
		break;
    case 'n': // Apartado A: rotar Z negativo
        if (interfaz.escena.malla->get_normalActivada()) {
            interfaz.escena.malla->set_normalActivada(false);
        }else{

            interfaz.escena.malla->set_normalActivada(true);
        }

        break;

    case 'N': // Apartado A: rotar Z negativo
        if (interfaz.escena.malla->get_normalActivada()) {
            interfaz.escena.malla->set_normalActivada(false);
        }else{

            interfaz.escena.malla->set_normalActivada(true);
        }

        break;
    case 'g': // Apartado A: rotar Z negativo
        if (interfaz.escena.malla->get_sombreado()) {
            interfaz.escena.malla->set_sombreado(false);
        }else{

            interfaz.escena.malla->set_sombreado(true);
        }

        break;
    case 'G': // Apartado A: rotar Z negativo
        if (interfaz.escena.malla->get_sombreado()) {
            interfaz.escena.malla->set_sombreado(false);
        }else{

            interfaz.escena.malla->set_sombreado(true);
        }

        break;
    case 'e': // activa/desactiva la visualizacion de los ejes
			interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	  break;
    case 27: // tecla de escape para SALIR
      exit(1);
    break;
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar();

	//visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
