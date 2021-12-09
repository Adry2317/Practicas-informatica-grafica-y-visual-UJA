#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif


enum {
	basex,
	cuerpoinferior,
	cuerposuperior,
	brazo
};

class igvEscena3D {
protected:
	////// Apartado C: a�adir qu� los atributos para el control de los grados de libertad del modelo
    float anguloCabeza;
    float anguloTorsoSuperior;
    float anguloBrazoIzquierdo;
    float anguloBrazoDerecho;
    float anguloAntebrazoIzquierdo;
    float anguloAntebrazoDerecho;
    float anguloPirnaIzquierda;
    float anguloPiernaDerecha;
    bool animacion;

	// Otros atributos		
	bool ejes;

public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// m�todo con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	///// Apartado B: M�todos para visualizar cada parte del modelo
	void pintarTorsoInferior();
    void pintarTorsoSuperior();
    void pintarCabeza();
    void pintarBrazos();
    void pintarPiernas();

	////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo


	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

    void setAnguloCabeza(float anguloCabeza);

    void setAnguloTorsoSuperior(float anguloTorsoSuperior);

    void setAnguloBrazoIzquierdo(float anguloBrazoIzquierdo);

    void setAnguloBrazoDerecho(float anguloBrazoDerecho);

    void setAnguloAntebrazoIzquierdo(float anguloAntebrazoIzquierdo);

    void setAnguloAntebrazoDerecho(float anguloAntebrazoDerecho);

    void setAnguloPirnaIzquierda(float anguloPirnaIzquierda);

    void setAnguloPiernaDerecha(float anguloPiernaDerecha);

    float getAnguloPirnaIzquierda() const;

    float getAnguloPiernaDerecha() const;

    float getAnguloCabeza() const;

    float getAnguloTorsoSuperior() const;

    float getAnguloBrazoIzquierdo() const;

    float getAnguloBrazoDerecho() const;

    float getAnguloAntebrazoIzquierdo() const;

    float getAnguloAntebrazoDerecho() const;


    void setAnimacion(bool animacion);

    bool isAnimacion() const;
};

#endif
