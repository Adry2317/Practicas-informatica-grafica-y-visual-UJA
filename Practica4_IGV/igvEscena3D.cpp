#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

// Metodos constructores 

igvEscena3D::igvEscena3D ():ambiente(0.15,0,0),difuso(0.5,0,0),especular(0.5,0,0),phong(120.0),
                            posicion(3,1,1)
{
	ejes = true;

}

igvEscena3D::~igvEscena3D() {
}


// Metodos publicos 

void pintar_ejes(void) {
  GLfloat rojo[]={1,0,0,1.0};
  GLfloat verde[]={0,1,0,1.0};
  GLfloat azul[]={0,0,1,1.0};

  glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
	glBegin(GL_LINES);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,verde);
	glBegin(GL_LINES);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,azul);
	glBegin(GL_LINES);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}


void pintar_quad(float div_x, float div_z) {

	float ini_x = 0.0;
	float ini_z = 0.0;
	float tam_x = 5.0;
	float tam_z = 5.0;


    float distanciaX = tam_x/div_x;

    float distanciaZ = tam_z/div_z;






    for(float i = ini_x; i < tam_x; i = i + distanciaX ){
        for(float j = ini_z; j < tam_z; j = j + distanciaZ ){
            glNormal3f(0,1,0);
            glBegin(GL_QUADS);

            glTexCoord2f(i/tam_x,j/tam_z);
            glVertex3f(i , 0.0, j);

            glTexCoord2f(i/tam_x,(j+ distanciaZ)/tam_z);
            glVertex3f(i/tam_x , 0.0, (j + distanciaZ)/tam_z);

            glTexCoord2f((i+distanciaX)/tam_x,(j+distanciaZ)/tam_z);
            glVertex3f(i + distanciaX, 0.0, j + distanciaZ);

            glTexCoord2f((i+distanciaX)/tam_x,j/tam_z);
            glVertex3f(i + distanciaX, 0.0, j);

            glEnd();
        }
    }


}


void igvEscena3D::visualizar(void) {
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

		// se pintan los ejes
	  if (ejes) pintar_ejes();

		// luces se aplican antes de las transformaciones a la escena para que permanezcan fijas

		// APARTADO A: Define y aplica la luz puntual especificada en el gui�n de pr�cticas
        double a0 = 1.0;
        double a1 = 0.0;
        double a2 = 0.0;
        igvFuenteLuz puntual(GL_LIGHT0,igvPunto3D(1.0,1.0,1.0),igvColor(0.0,0.0,0.0,1.0),igvColor(1.0,1.0,1.0,1.0),igvColor(1.0,1.0,1.0,1.0),a0,a1,a2);
        puntual.encender();
        puntual.aplicar();
		// APARTADO E: Define y aplica la luz tipo foco especificada en el gui�n de pr�cticas
	    igvFuenteLuz foco(GL_LIGHT1,posicion,igvColor(0.0,0.0,0.0,1.0),igvColor(1.0,1.0,1.0,1.0),igvColor(1.0,1.0,1.0,1.0),a0,a1,a2,igvPunto3D(0.0,-1.0,0.0),40,1);
        foco.encender();
        foco.aplicar();
		/* Apartado B: definir y aplicar las propiedades de material indicadas en el gui�n de pr�cticas */
        igvMaterial material(ambiente,difuso ,especular,phong);
        material.aplicar();

		/* Apartado D: sustituir los valores correspondientes a la componente R del coeficiende difuso,
		               la componente R del coeficiente especular y el exponente de Phong, por el valor
									 del atributo correspondiente de la clase igvEscena */


		/* Apartado F: A�ade aqu� la creaci�n del objeto textura y su aplicaci�n */

        igvTextura textura ("mapa.png");

        textura.aplicar();
		pintar_quad(50, 50);



	glPopMatrix (); // restaura la matriz de modelado
}

const igvColor &igvEscena3D::getAmbiente() const {
    return ambiente;
}

void igvEscena3D::setAmbiente(const igvColor &ambiente) {
    igvEscena3D::ambiente = ambiente;
}

const igvColor &igvEscena3D::getDifuso() const {
    return difuso;
}

void igvEscena3D::setDifuso(const igvColor &difuso) {
    igvEscena3D::difuso = difuso;
}

const igvColor &igvEscena3D::getEspecular() const {
    return especular;
}

void igvEscena3D::setEspecular(const igvColor &especular) {
    igvEscena3D::especular = especular;
}

float igvEscena3D::getPhong() const {
    return phong;
}

void igvEscena3D::setPhong(float phong) {
    igvEscena3D::phong = phong;
}

const igvPunto3D &igvEscena3D::getPosicion() const {
    return posicion;
}

void igvEscena3D::setPosicion(const igvPunto3D &posicion) {
    igvEscena3D::posicion = posicion;
}
