
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
    rotacionPan=0;
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
    rotacionPan=0;
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

    //aplicamos la transformcion con un punto y la matriz identidad
    glm::mat4 trasl = glm::translate(glm::mat4(1.0f),glm::vec3(P0[0], P0[1], P0[2]));

    //aplicamos rotacion
    trasl = glm::rotate(trasl,glm::radians((float)recorrido),glm::vec3(V[0],V[1],V[2]));
    //trasladamos al origen
    trasl = glm::translate(trasl,glm::vec3(-P0[0], -P0[1], -P0[2]));

    //creamos un nuevo punto ,ultiplicando r con la matriz de transformacion
    glm::vec4 pos = trasl * glm::vec4(r[0],r[1],r[2],1.0);

    r.set(pos.x, pos.y, pos.z);
    aplicar();

}

void igvCamara::tilt(double recorrido) {

    //calculamos el vector direccion a r y P0
    glm::vec3 direccion = glm::normalize(glm::vec3(r[0],r[1], r[2]) - glm::vec3(P0[0],P0[1],P0[2]));

    //vector cruzado para rptacion en eje z
    glm::vec3 camaraDerecha = glm::normalize(glm::cross(glm::vec3(V[0],V[1], V[2]), direccion));

    //aplicamos la transformcion con un punto y la matriz identidad
    glm::mat4 trasl = glm::translate(glm::mat4(1.0f),glm::vec3(P0[0], P0[1], P0[2]));

    //aplicamos rotacion
    trasl = glm::rotate(trasl,glm::radians((float)recorrido),camaraDerecha);
    //trasladamos al origen
    trasl = glm::translate(trasl,glm::vec3(-P0[0], -P0[1], -P0[2]));

    //creamos un nuevo punto ,ultiplicando r con la matriz de transformacion
    glm::vec4 pos = trasl * glm::vec4(r[0],r[1],r[2],1.0);

    r.set(pos.x, pos.y, pos.z);
    aplicar();

}


void igvCamara::orbit(double recorridoH, double recorridoV) {


    glm::vec3 direccion = glm::normalize(glm::vec3(r[0],r[1], r[2]) - glm::vec3(P0[0],P0[1],P0[2]));

    //vector cruzado para rptacion en eje z
    glm::vec3 camaraDerecha = glm::normalize(glm::cross(glm::vec3(V[0],V[1], V[2]), direccion));

    //Realizamos rotacion en X respecto al origen que es donde esta el objeto.
    //Se crea la matriz de rotacion respecto de la posiccion y aplica a la posicion
    glm::mat4 rotacion = glm::rotate(glm::mat4(1.f),glm::radians((float)recorridoH),glm::vec3(V[0],V[1],V[2]));
    rotacion = glm::rotate(rotacion,glm::radians((float)recorridoV),camaraDerecha);
    glm::vec4 pos = rotacion * glm::vec4 (P0[0], P0[1], P0[2], 1.0);


    P0.set(pos.x, pos.y, pos.z);


    aplicar();
}


void igvCamara::dolly(float recorrido) {
    P0.set(P0[0]+recorrido, P0[1],P0[2]);
    r.set(r[0]+recorrido, r[1], r[2]);

    aplicar();
}

void igvCamara::boomCrane(float recorridoV) {
    P0.set(P0[0], P0[1] + recorridoV,P0[2]);
    r.set(r[0], r[1]+recorridoV, r[2]);

    aplicar();
}




