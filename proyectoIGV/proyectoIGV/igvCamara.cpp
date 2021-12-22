
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
	tipo = _tipo;

}


//Metodos para cambiar parametros de la camara
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

//Aplica el tipo de camara
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
    //Aumentamos el x en la posicion  y el punto al que mira
    P0.set(P0[0]+recorrido, P0[1],P0[2]);
    r.set(r[0]+recorrido, r[1], r[2]);

    aplicar();
}

void igvCamara::boomCrane(float recorridoV) {
    //Aumentamos en Y la posicion y el punto al que mira
    P0.set(P0[0], P0[1] + recorridoV,P0[2]);
    r.set(r[0], r[1]+recorridoV, r[2]);

    aplicar();
}

void igvCamara::truck(float recorrido) {
    //Calculamos la distancia entre el punto  que se mira y la posicion
    glm::vec3 posicion = glm::vec3(P0[0], P0[1], P0[2]);
    glm::vec3 puntoMira = glm::vec3(r[0],r[1],r[2]);

    glm::vec3 distancia = puntoMira - posicion;

    //Realizamos el calculo del punto por la ecuacion parametrica
    glm::vec3 nuevoPunto;
    nuevoPunto.x = P0[0] + recorrido * distancia.x;
    nuevoPunto.y = P0[1] + recorrido * distancia.y;
    nuevoPunto.z = P0[2] + recorrido * distancia.z;

    //Calculamos la diferencia de desplazamiento del punto
    glm::vec3 desplazamiento = nuevoPunto - posicion;
    P0.set(nuevoPunto.x, nuevoPunto.y, nuevoPunto.z);
    //Aplicamos el desplazamiento al punto que mira tambien el distancia
    r.set(r[0] + desplazamiento.x, r[1] + desplazamiento.y, r[2] + desplazamiento.z);
    aplicar();

}

//Setters y getters
const igvPunto3D &igvCamara::getP0() const {
    return P0;
}

void igvCamara::setP0(const igvPunto3D &p0) {
    P0 = p0;
}

const igvPunto3D &igvCamara::getR() const {
    return r;
}

void igvCamara::setR(const igvPunto3D &r) {
    igvCamara::r = r;
}

const igvPunto3D &igvCamara::getV() const {
    return V;
}

void igvCamara::setV(const igvPunto3D &v) {
    V = v;
}

GLdouble igvCamara::getXwmin() const {
    return xwmin;
}

void igvCamara::setXwmin(GLdouble xwmin) {
    igvCamara::xwmin = xwmin;
}

GLdouble igvCamara::getXwmax() const {
    return xwmax;
}

void igvCamara::setXwmax(GLdouble xwmax) {
    igvCamara::xwmax = xwmax;
}

GLdouble igvCamara::getYwmin() const {
    return ywmin;
}

void igvCamara::setYwmin(GLdouble ywmin) {
    igvCamara::ywmin = ywmin;
}

GLdouble igvCamara::getYwmax() const {
    return ywmax;
}

void igvCamara::setYwmax(GLdouble ywmax) {
    igvCamara::ywmax = ywmax;
}

GLdouble igvCamara::getAngulo() const {
    return angulo;
}

void igvCamara::setAngulo(GLdouble angulo) {
    igvCamara::angulo = angulo;
}

GLdouble igvCamara::getRaspecto() const {
    return raspecto;
}

void igvCamara::setRaspecto(GLdouble raspecto) {
    igvCamara::raspecto = raspecto;
}

GLdouble igvCamara::getZnear() const {
    return znear;
}

void igvCamara::setZnear(GLdouble znear) {
    igvCamara::znear = znear;
}

GLdouble igvCamara::getZfar() const {
    return zfar;
}

void igvCamara::setZfar(GLdouble zfar) {
    igvCamara::zfar = zfar;
}




