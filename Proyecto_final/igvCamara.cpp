
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"

// Metodos constructores

igvCamara::igvCamara():movimientoActivado(ninguno),anguloRoll(90) {

}

igvCamara::~igvCamara() {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
    rotacionPan=-90;
    rotaciontilt = 0;
    rotacionOrbitalV=0;
    rotacionOrbitalH=0;
	tipo = _tipo;

}


// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
    radio = 1;
    rotacionPan=-90;
    rotaciontilt = 0;
    rotacionOrbitalV=0;
    rotacionOrbitalH=0;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _angulo, double _raspecto, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::aplicar(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		gluPerspective(angulo, raspecto, znear, zfar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
}


void igvCamara::zoom(double factor) {
    //modificacion atributos ventana proyección perspectiva.
    angulo = angulo * factor;

    //modificacion atributos ventana proyección paralela.
    xwmin = xwmin * factor;
    xwmax = xwmax * factor;
    ywmin = ywmin * factor;
    ywmax = ywmax * factor;
}

void igvCamara::roll(double angulo) {
    anguloRoll += angulo;
    float anguloRadianes = (anguloRoll *3.14)/180;
    float y = radio * sin(anguloRadianes);
    float x = radio * cos(anguloRadianes);
    V.set(x,y,0);
    aplicar();

}


void igvCamara::pan(double recorrido) {
    rotacionPan += recorrido;
    float anguloRadianes = (rotacionPan *3.14)/180;
    double dist = (new Utils())->normalized(P0[0] - r[0], P0[1] - r[1], P0[2] - r[2]);

    float x = dist * cos(anguloRadianes);

    r.set(x,r[1],r[2]);
    aplicar();
}

void igvCamara::tilt(double recorrido) {
    rotaciontilt+=recorrido;
    float anguloRadianes = (rotaciontilt *3.14)/180;
    double dist = (new Utils())->normalized(P0[0] - r[0], P0[1] - r[1], P0[2] - r[2]);

    float y = dist * sin(anguloRadianes);
    std::cout<<rotaciontilt<<std::endl;
    r.set(r[0],y,r[2]);
    aplicar();
}


void igvCamara::orbit(double recorridoH, double recorridoV) {
    rotacionOrbitalH += recorridoH;
    float anguloRadianes = (rotacionOrbitalH *3.14)/180;
    //double dist = (new Utils())->normalized(P0[0] - r[0], P0[1] - r[1], P0[2] - r[2]);
    float y = 1 * sin(anguloRadianes);
    float x = 1 * cos(anguloRadianes);
    P0.set(x,0,y);

   /* rotacionOrbitalV += recorridoV;
    float anguloRadianes2 = (rotacionOrbitalV *3.14)/180;
    double dist2 = (new Utils())->normalized(P0[0] - r[0], P0[1] - r[1], P0[2] - r[2]);
    float y2 = dist * sin(anguloRadianes);
    float x2 = dist * cos(anguloRadianes);
*/

    aplicar();
}
