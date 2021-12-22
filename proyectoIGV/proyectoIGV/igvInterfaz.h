#define GL_SILENCE_DEPRECATION
#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include <vector>
#include "igvEscena3D.h"
#include "igvCamara.h"

using namespace std;

typedef enum {
    IGV_VISUALIZAR,
    IGV_SELECCIONAR,
} modoInterfaz;

class igvInterfaz {
protected:
	// Atributos
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion

	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	igvCamara camara; // camara que se utiliza para visualizar la escena
    vector<igvCamara> vectorCamaras;//vector que almacena las camaras a mostrar al pulsar 4
    bool cuatroCamaras; //variable de control para saber si están activas las 4 camaras
    vector<igvPunto3D> p0Vistas, rVistas, Vvistas; //Vector con las coordenadas de las distintas camaras
    
    //Limites de movimiento de las partes
    bool brazoArriba; 
    bool limiteCabeza;
    bool limTorso;
    
    modoInterfaz modo; // IGV_VISUALIZAR: en la ventana se va a visualizar de manera normal la escena,
                           // IGV_SELECCIONAR: se ha pulsado sobre la ventana de visualización, la escena se debe
                           // visualizar en modo selección
    int cursorX, cursorY; // pixel de la pantalla sobre el que está situado el ratón, por pulsar o arrastrar

    int objeto_seleccionado; // código del objeto seleccionado, -1 si no hay ninguno

    bool boton_retenido; // indica si el botón está pulsado (true) o se ha soltado (false)
  

public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();


	// callbacks de eventos
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // metodo que define la camara de vision y el viewport
												   // se llama automaticamente cuano se camba el tamaño de la ventana
	static void set_glutDisplayFunc(); // metodo para visualizar la escena
	static void set_glutIdleFunc(); // metodo para animar la escena
    static void set_glutSpecialKeys(int key, int x, int y); //Método teclas de dirección.

	// Metodos
	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los parametros para crear una ventana de visualizacion
	void configura_entorno(int argc, char** argv, // parametros del main
		int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizacion
		int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizacion
		string _titulo // titulo de la ventan de visualizacion
	);
	void inicializa_callbacks(); // inicializa todas los callbacks
	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// metodos get_ y set_ de acceso a los atributos
	int get_ancho_ventana() { return ancho_ventana; };
	int get_alto_ventana() { return alto_ventana; };
	static void  set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y); // control de pulsacion del raton
    static void  set_glutMotionFunc(GLint x, GLint y); // control del desplazamiento del raton con boton pulsado
	void set_ancho_ventana(int _ancho_ventana) { ancho_ventana = _ancho_ventana; };
	void set_alto_ventana(int _alto_ventana) { alto_ventana = _alto_ventana; };

    bool isBrazoArriba() const;

    void setBrazoArriba(bool brazoArriba);

    void setLimiteCabeza(bool limiteCabeza);

    bool isLimiteCabeza() const;

    void setLimTorso(bool limTorso);

    bool isLimTorso() const;
};

#endif
