#include <cstdlib>
#include <stdio.h>
#include<iostream>
#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;

    r=0;
    b=0;
    g=0;
    
	for (int pilasY = 0; pilasY < 3; pilasY++) {
		for (int pilasX = 0; pilasX < 3; pilasX++) {
			for (int pilasZ = 0; pilasZ < 3; pilasZ++) {

                if(r < 255){
                    r++;
                }else if (g<255){
                    g++;
                }else if(b < 255){
                    b++;
                }
				cajas.push_back(new igvCaja(r/255.0, g/255.0,b/255.0)); //Se crea una nueva caja con el color indicado
                
			}
		}
	}
}

igvEscena3D::~igvEscena3D() {
}

// Metodos publicos 
void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glBegin(GL_LINES);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}

//Método para la visualización del modelo
void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado
	if (ejes) pintar_ejes(); // se pintan los ejes
	glPopMatrix();

	glPushMatrix();
	visualizarVB();
	glPopMatrix();

}

//Método para la visualización del modelo sin luces (se utiliza durante la selección)
void igvEscena3D::visualizarVB() {
	GLfloat separacionX = 2.5;
	GLfloat separacionZ = 2.5;

	int cont = 0;
	// Practica 2a. Parte B y C.
	for (int pilasY = 0; pilasY < 3; pilasY++) {
		for (int pilasX = 0; pilasX < 3; pilasX++) {
			for (int pilasZ = 0; pilasZ < 3; pilasZ++) {
				glPushMatrix();
				glTranslatef(pilasX * separacionX, pilasY, pilasZ * separacionZ);
				cajas[cont++]->visualizar(); //Se visualiza la caja
				glPopMatrix();
			}
		}
	}
}

int igvEscena3D::getCajasX(){
    return nCajasX;
}

int igvEscena3D::getCajasY(){
    return nCajasY;
}

int igvEscena3D::getCajasZ(){
    return nCajasZ;
}

void igvEscena3D::setCajasX(int valor){
    nCajasX = valor;
}

void igvEscena3D::setCajasY(int valor){
    nCajasY = valor;
}

void igvEscena3D::setCajasZ(int valor){
    nCajasZ = valor;
}

void igvEscena3D::addCajas(){
    r += 1;
    g += 0;
    b += 1;
    cajas.push_back(new igvCaja(r/255.0, g/255.0,b/255.0)); //Se crea una nueva caja con el color indicado
}

