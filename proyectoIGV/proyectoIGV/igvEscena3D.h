
#define GL_SILENCE_DEPRECATION
#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvColor.h"
#include "igvPunto3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "Face.h"
#include "igvTextura.h"
enum {
	basex,
	cuerpoinferior,
	cuerposuperior,
	brazo
};

class igvEscena3D {
protected:

    //Angulos de libertad de las partes del grafo de escena
    float anguloCabeza;
    float anguloTorsoSuperior;
    float anguloBrazoIzquierdo;
    float anguloBrazoDerecho;
    float anguloAntebrazoIzquierdo;
    float anguloAntebrazoDerecho;
    float anguloPirnaIzquierda;
    float anguloPiernaDerecha;
    
    //Animacion activa
    bool animacion;

	//Ejes
	bool ejes;

    //Componentes de color de las luces
    igvColor ambiente;
    igvColor difuso;
    igvColor especular;
    
    //Exponente de phong
    float phong;
    //Posicion del foco de luz
    igvPunto3D posicion;
    //Texturas
    igvTextura* textura = nullptr;
    igvTextura* textura2 = nullptr;
    //Objetos de los planetas
    std::vector<Face*> objetos;
    
public:

	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// metodo con las llamadas OpenGL para visualizar la escena
	void visualizar(void);
    //Metodo para llamar a visualizar los planetas sin luces ni texturas
    void visualizarVB();
	//Metodos para visualizar cada parte del modelo
	void pintarTorsoInferior();
    void pintarTorsoSuperior();
    void pintarCabeza();
    void pintarBrazos();
    void pintarPiernas();

    //Setters y getters
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
    
    std::vector<Face*> getObjetos();
};

#endif
