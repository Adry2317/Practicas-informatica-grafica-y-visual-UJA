#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
    brazoArriba = false;
    limiteCabeza = false;
    limTorso = false;
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(6.0, 4.0, 8), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
		-1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3, 200);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
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
	switch (key) {
		////// Apartado C: incluir aqu� el cambio de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva 
		////// Apartado C: incluir aqu� la modificaci�n de los grados de libertad del modelo pulsando las teclas correspondientes

	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);

		break;

    case 't': //activa movimiento torso superior
        if(interfaz.escena.getAnguloTorsoSuperior() < 90) {
            interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() + 5);
        }
        break;
    case 'T': //activa movimiento torso superior
        if(interfaz.escena.getAnguloTorsoSuperior() > 5 ){
            interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() - 5);
        }
        break;
    case 'c'://activa movimiento cabeza
        if(interfaz.escena.getAnguloCabeza() < 33){
            interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()+5);
        }
        break;
    case 'C':
        if(interfaz.escena.getAnguloCabeza() > -12){
            interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()-5);
        }
    break;
    case 'p'://PIERNA DERECHA HACIA DELANTE
        if(interfaz.escena.getAnguloPiernaDerecha() > -45){
            interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha() - 5);
        }
        break;
    case 'P'://PIERNA DERECHA HACIA ATRAS
        if(interfaz.escena.getAnguloPiernaDerecha() < 45){
            interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()+5);
        }
    break;
    case 'o'://PIERNA IZQUIEDA HACIA DELANTE
        if(interfaz.escena.getAnguloPirnaIzquierda() > -45){
            interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda() - 5);
        }
        break;
    case 'O'://PIERNA IZQUIERDA HACIA ATRAS
        if(interfaz.escena.getAnguloPirnaIzquierda() < 45){
            interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()+5);
        }
        break;
    case 'b': //BRAZO SUPERIOR DERECHO HACIA DELANTE
        if(interfaz.escena.getAnguloBrazoDerecho() > -90){
            interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() - 5);
        }
        break;

    case 'B': //BRAZO SUPERIOR DERECHO HACIA ATRAS
        if(interfaz.escena.getAnguloBrazoDerecho()<80){
            interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho()+5);
        }
        break;

    case 'f': //BRAZO SUPERIOR IZQUIERDO HACIA DELANTE
        if(interfaz.escena.getAnguloBrazoIzquierdo() > -90){
            interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() - 5);
        }
        break;

    case 'F': //BRAZO SUPERIOR IZQUIERDO HACIA ATRAS
        if(interfaz.escena.getAnguloBrazoIzquierdo()<80){
            interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo()+5);
        }
        break;


    case 'd': //ANTEBRAZO IZQUIERDO HACIA DELANTE
        if(interfaz.escena.getAnguloAntebrazoIzquierdo() > -90){
            interfaz.escena.setAnguloAntebrazoIzquierdo(interfaz.escena.getAnguloAntebrazoIzquierdo() - 5);
        }
        break;

    case 'D': //ANTEBRAZO IZQUIERDO HACIA ATRAS
        if(interfaz.escena.getAnguloAntebrazoIzquierdo()<0){
            interfaz.escena.setAnguloAntebrazoIzquierdo(interfaz.escena.getAnguloAntebrazoIzquierdo()+5);
        }
        break;

    case 's': //ANTEBRAZO DERECHO HACIA DELANTE
        if(interfaz.escena.getAnguloAntebrazoDerecho() <90){
            interfaz.escena.setAnguloAntebrazoDerecho(interfaz.escena.getAnguloAntebrazoDerecho() + 5);
        }
        break;

    case 'S': //ANTEBRAZO DERECHO HACIA ATRAS
        if(interfaz.escena.getAnguloAntebrazoDerecho()>0){
            interfaz.escena.setAnguloAntebrazoDerecho(interfaz.escena.getAnguloAntebrazoDerecho()-5);
        }
        break;
    case 'a':
        if(interfaz.escena.isAnimacion()){
            interfaz.escena.setAnimacion(false);
        }else{
            interfaz.escena.setAnimacion(true);
        }
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


	// aplica las transformaciones en funci�n de los par�metros de la c�mara
	interfaz.camara.aplicar();
	// visualiza la escena
	interfaz.escena.visualizar();

	// refresca la ventana
	glutSwapBuffers();
}

void igvInterfaz::set_glutIdleFunc() {
	///// Apartado D: incluir el c�digo para animar el modelo de la manera m�s realista posible
    if(interfaz.escena.isAnimacion()) {
        if(!interfaz.brazoArriba) {
            if (interfaz.escena.getAnguloBrazoDerecho() > -90) {
                interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() - 0.25);

            }else{
                interfaz.brazoArriba = true;
            }
            if(interfaz.escena.getAnguloPiernaDerecha()>-45){
                interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()-0.125);
            }

            //Bajar
            if (interfaz.escena.getAnguloBrazoIzquierdo() < 80) {
                interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() + 0.25);

            }
            if(interfaz.escena.getAnguloPirnaIzquierda()<45){
                interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()+0.125);
            }
        }else{
            if (interfaz.escena.getAnguloBrazoDerecho() < 80) {
                interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() + 0.25);

            }else{
                interfaz.brazoArriba = false;
            }

            if(interfaz.escena.getAnguloPiernaDerecha()<45){
                interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()+0.125);
            }

            if (interfaz.escena.getAnguloBrazoIzquierdo() > -90) {
                interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() - 0.25);

            }

            if(interfaz.escena.getAnguloPirnaIzquierda()>-45){
                interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()-0.125);
            }
        }

        if(!interfaz.isLimiteCabeza()){
            if(interfaz.escena.getAnguloCabeza() < 33){
                interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()+0.1);
            }else{
                interfaz.setLimiteCabeza(true);
            }
        }else{
            if(interfaz.escena.getAnguloCabeza() > -12){
                interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()-0.1);
            }else{
                interfaz.setLimiteCabeza(false);
            }
        }

        if(!interfaz.isLimTorso()){
            if(interfaz.escena.getAnguloTorsoSuperior() < 70) {
                interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() + 0.07);
            }else{
                interfaz.setLimTorso(true);
            }
        }else{
            if(interfaz.escena.getAnguloTorsoSuperior() > 25 ){
                interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() - 0.07);
            }else{
                interfaz.setLimTorso(false);
            }
        }
        glutPostRedisplay();
    }

}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
}

bool igvInterfaz::isBrazoArriba() const {
    return brazoArriba;
}

void igvInterfaz::setBrazoArriba(bool brazoArriba) {
    igvInterfaz::brazoArriba = brazoArriba;
}

void igvInterfaz::setLimiteCabeza(bool limiteCabeza) {
    igvInterfaz::limiteCabeza = limiteCabeza;
}

bool igvInterfaz::isLimiteCabeza() const {
    return limiteCabeza;
}


void igvInterfaz::setLimTorso(bool limTorso) {
    igvInterfaz::limTorso = limTorso;
}

bool igvInterfaz::isLimTorso() const {
    return limTorso;
}
