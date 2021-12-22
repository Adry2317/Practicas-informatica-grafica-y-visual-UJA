#include <cstdlib>

#include "igvInterfaz.h"

// Objetos globales
// objeto que contiene la configuracion y la interaccion con la ventana de visualizacion
igvInterfaz interfaz;

int main(int argc, char** argv) {
	// inicializa la ventana de visualizacion
	interfaz.configura_entorno(argc, argv,
		800, 800, // tamaño de la ventana
		100, 100, // posicion de la ventana
		"Informatica Grafica y Visualizacion. Proyecto final." // titulo de la ventana
	);

	// establece las funciones callbacks para la gestion de los eventos
	interfaz.inicializa_callbacks();

	// inicia el bucle de visualizacion de OpenGL
	interfaz.inicia_bucle_visualizacion();

	return(0);
}
