#include <cstdlib>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() { 
	ejes = true; 
}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana,_alto_ventana);
    glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
    glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // tecla de escape para SALIR
      exit(1);
    break;

	case 'e':
		if (interfaz.get_ejes() == false) {
			
			interfaz.set_ejes(true);
		}
		else {
			interfaz.set_ejes(false);
		}
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  glViewport(0,0,(GLsizei) w,(GLsizei) h);

  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

  // establece el tipo de proyeccion a utilizar
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-1,1,-1,1,-1,200);

  // se define la camara de vision
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void igvInterfaz::set_glutDisplayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
  glPushMatrix(); // guarda la matriz de modelado

	// Apartado A: pintar los ejes
  if (interfaz.get_ejes()) {
	  glBegin(GL_LINES);
		  glColor3f(1.0f, 0.0f, 0.0f);
		  glVertex3f(-100.0f, 0.0f, 0.0f);
		  glVertex3f(100.0f, 0.0f, 0.0f);

		  glColor3f(0.0f, 1.0f, 0.0f);
		  glVertex3f(0.0f, -100.0f, 0.0f);
		  glVertex3f(0.0f, 100.0f, 0.0f);

		  glColor3f(0.0f, 0.0f, 1.0f);
		  glVertex3f(0.0f, 0.0f, -100.0f);
		  glVertex3f(0.0f, 0.0f, 100.0f);

	  glEnd();
  }




 


	// Apartado B: visualizar primitiva cubo en modo alambre
  glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(1.0);

	// Apartado D: cara superior con triángulos
	glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();



  glPopMatrix (); // restaura la matriz de modelado
  glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
