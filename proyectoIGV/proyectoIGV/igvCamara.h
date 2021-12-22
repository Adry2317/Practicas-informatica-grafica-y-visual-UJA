#define GL_SILENCE_DEPRECATION
#ifndef __IGVCAMARA
#define __IGVCAMARA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>

#endif
#include "iostream"
#include "igvPunto3D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef enum {
	panoramica,
	planta,
	perfil,
	alzado,
}poscam;

typedef enum {
	IGV_PARALELA,
	IGV_FRUSTUM,
	IGV_PERSPECTIVA
} tipoCamara;

typedef enum {
    ninguno,
    pan, //pamoramica horizontal
    tilt, //panoramica vertical
    dolly, //movimiento horizontal
    truck, //movimiento adelante/atras
    boomCrane, //movimiento hacia arriba y abajo
    orbit, //movimiento orbital longitud y latitud
    roll, //rotacion camara.

}movCamara;

class igvCamara {

public:
	// atributos
	poscam vis;		// Posici�n de la c�mara

	tipoCamara tipo;	// paralela o perspectiva

    movCamara movimientoActivado;

	// ventana de visi�n: parametros proyecci�n paralela y frustum
	GLdouble xwmin, xwmax, ywmin, ywmax;

	// ventana de visi�n: parametros proyecci�n perspectiva
	GLdouble 	angulo, raspecto;

	// distancias de planos cercano y lejano
	GLdouble znear, zfar;

	// punto de visi�n	
	igvPunto3D P0;

	// punto de referencia de visi�n	
	igvPunto3D r;

	// vector arriba	
	igvPunto3D V;

    int radio;
    float anguloRoll;



public:
	// Constructores por defecto y destructor
	igvCamara();
	~igvCamara();

	// Otros constructores
	igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

	// Metodos
	// define la posici�n de la c�mara
	void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V);

	// define una c�mara de tipo paralela o frustum
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar);

	// define una c�mara de tipo perspectiva
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _angulo, double _raspecto, double _znear, double _zfar);

	void aplicar();

	void zoom(double factor); // realiza un zoom sobre la c�mara

    void roll(double angulo); //Realiza un movimiento roll.

    void pan(double recorrido); //realiza movimiento panoramica horizontal

    void tilt(double recorrido); //realiza panoramica en vertica;

    void orbit(double recorridoH, double recorridoV); //Realiza orbitacion vertical y horizontal

    void dolly(float recorrido); //Realiza movimiento horizontal.

    void boomCrane(float recorridoV);

    void truck(float recorrido);

	void set_vista(tipoCamara t) { tipo = t; };
    
	tipoCamara get_vista() { return tipo; };
    
	void set_poscam(poscam x) { vis = x; };
    
	poscam get_poscam() { return vis; };

    const igvPunto3D &getP0() const;

    void setP0(const igvPunto3D &p0);

    const igvPunto3D &getR() const;

    void setR(const igvPunto3D &r);

    const igvPunto3D &getV() const;

    void setV(const igvPunto3D &v);

    GLdouble getXwmin() const;

    void setXwmin(GLdouble xwmin);

    GLdouble getXwmax() const;

    void setXwmax(GLdouble xwmax);

    GLdouble getYwmin() const;

    void setYwmin(GLdouble ywmin);

    GLdouble getYwmax() const;

    void setYwmax(GLdouble ywmax);

    GLdouble getAngulo() const;

    void setAngulo(GLdouble angulo);

    GLdouble getRaspecto() const;

    void setRaspecto(GLdouble raspecto);

    GLdouble getZnear() const;

    void setZnear(GLdouble znear);

    GLdouble getZfar() const;

    void setZfar(GLdouble zfar);
};

#endif

