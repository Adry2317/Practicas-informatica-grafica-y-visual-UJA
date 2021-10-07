#include <cstdlib>
#include <stdio.h>
#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	p0 = igvPunto3D(3.0, 2.0, 4);
	r = igvPunto3D(0, 0, 0);
	V = igvPunto3D(0, 1.0, 0);

	//Vista Normal
	p0Vistas.push_back(p0);
	rVistas.push_back(r);
	Vvistas.push_back(V);

	//Vista Planta
	p0Vistas.push_back(igvPunto3D(0,-5,0));
	rVistas.push_back(igvPunto3D(0,0,0));
	Vvistas.push_back(igvPunto3D(1.0,0,0));

	//Vista Perfil
	p0Vistas.push_back(igvPunto3D(5, 0, 0));
	rVistas.push_back(igvPunto3D(0, 0, 0));
	Vvistas.push_back(igvPunto3D(0, 1.0, 0));

	//Vista Alzado
	p0Vistas.push_back(igvPunto3D(0, 0, 5));
	rVistas.push_back(igvPunto3D(0, 0, 0));
	Vvistas.push_back(igvPunto3D(0, 1.0, 0));

	

	interfaz.camara.set(IGV_PARALELA, p0, r, V,
		-1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);

	//parámetros de la perspectiva
	interfaz.camara.angulo = 60.0;
	interfaz.camara.raspecto = 1.0;
}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {

	/* IMPORTANTE: en la implementación de este método hay que cambiar convenientemente el estado
	   de los objetos de la aplicación, pero no hacer llamadas directas a funciones de OpenGL */

	switch (key) {
	case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		
		if (interfaz.camara.tipo == IGV_PARALELA) {
			interfaz.camara.set(IGV_PERSPECTIVA, interfaz.p0Vistas[interfaz.camara.vista], interfaz.rVistas[interfaz.camara.vista], interfaz.Vvistas[interfaz.camara.vista],-1*3,1*3,-1*3,1*3,1,200);
		}
		else {
			interfaz.camara.set(IGV_PARALELA, interfaz.p0Vistas[interfaz.camara.vista], interfaz.rVistas[interfaz.camara.vista], interfaz.Vvistas[interfaz.camara.vista], -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);
		}

		interfaz.camara.aplicar();
		break;
	case 'P': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		if (interfaz.camara.tipo == IGV_PARALELA) {
			interfaz.camara.set(IGV_PERSPECTIVA, interfaz.p0Vistas[interfaz.camara.vista], interfaz.rVistas[interfaz.camara.vista], interfaz.Vvistas[interfaz.camara.vista], -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);
		}
		else {
			interfaz.camara.set(IGV_PARALELA, interfaz.p0Vistas[interfaz.camara.vista], interfaz.rVistas[interfaz.camara.vista], interfaz.Vvistas[interfaz.camara.vista], -1 * 3, 1 * 3, -1 * 3, 1 * 3, 1, 200);
		}

		interfaz.camara.aplicar();
		break;
	case 'v': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
		switch (interfaz.camara.vista)
		{
		case NORMAL:
			interfaz.camara.set(interfaz.p0Vistas[PLANTA], interfaz.rVistas[PLANTA], interfaz.Vvistas[PLANTA]);
			interfaz.camara.vista = PLANTA;
			break;
		case PLANTA:
			interfaz.camara.set(interfaz.p0Vistas[PERFIL], interfaz.rVistas[PERFIL], interfaz.Vvistas[PERFIL]);
			interfaz.camara.vista = PERFIL;
			break;
		case PERFIL:
			interfaz.camara.set(interfaz.p0Vistas[ALZADO], interfaz.rVistas[ALZADO], interfaz.Vvistas[ALZADO]);
			interfaz.camara.vista = ALZADO;
			break;
		case ALZADO:
			interfaz.camara.set(interfaz.p0Vistas[NORMAL], interfaz.rVistas[NORMAL], interfaz.Vvistas[NORMAL]);
			interfaz.camara.vista = NORMAL;
			break;
		}
		
		interfaz.camara.aplicar();
		break;
	case 'V': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
		switch (interfaz.camara.vista)
		{
		case NORMAL:
			interfaz.camara.set(interfaz.p0Vistas[PLANTA], interfaz.rVistas[PLANTA], interfaz.Vvistas[PLANTA]);
			interfaz.camara.vista = PLANTA;
			break;
		case PLANTA:
			interfaz.camara.set(interfaz.p0Vistas[PERFIL], interfaz.rVistas[PERFIL], interfaz.Vvistas[PERFIL]);
			interfaz.camara.vista = PERFIL;
			break;
		case PERFIL:
			interfaz.camara.set(interfaz.p0Vistas[ALZADO], interfaz.rVistas[ALZADO], interfaz.Vvistas[ALZADO]);
			interfaz.camara.vista = ALZADO;
			break;
		case ALZADO:
			interfaz.camara.set(interfaz.p0Vistas[NORMAL], interfaz.rVistas[NORMAL], interfaz.Vvistas[NORMAL]);
			interfaz.camara.vista = NORMAL;
			break;
		}

		interfaz.camara.aplicar();
		break;
	case '+': // zoom in

		break;
	case '-': // zoom out

		break;
	case 'n': // incrementar la distancia del plano cercano

		break;
	case 'N': // decrementar la distancia del plano cercano

		break;
	case '4': // dividir la ventana  en cuatro vistas

		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision y redibuja la escena
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

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
