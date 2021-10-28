#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "igvMallaTriangulos.h"

igvMallaTriangulos::igvMallaTriangulos() :num_vertices(0), vertices(nullptr), num_triangulos(0), triangulos(nullptr),normales(nullptr)
{
}

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float* _vertices, long int _num_triangulos, unsigned int* _triangulos) {
/*
	num_vertices = _num_vertices;
	vertices = new float[num_vertices * 3];
	for (long int i = 0; i < (num_vertices * 3); ++i) {
		vertices[i] = _vertices[i];
	}

	normales = nullptr;

	num_triangulos = _num_triangulos;
	triangulos = new unsigned int[num_triangulos * 3];
	for (long int i = 0; i < (num_triangulos * 3); ++i) {
		triangulos[i] = _triangulos[i];
	}
*/

}

igvMallaTriangulos::~igvMallaTriangulos() {
	if (vertices)
		delete []vertices;
	if (normales)
		delete []normales;
	if (triangulos)
		delete []triangulos;
}


void igvMallaTriangulos::visualizar(void) {



	/* Apartado B: TODO */
    //Sombreado
    if(sombreado){
        glShadeModel(GL_SMOOTH);
    }else{
        glShadeModel(GL_FLAT);
    }

    //Normales
    if(normalActivada){

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT,0,normales);
    }

    //Dibuja la malla
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT,0,vertices);
    glDrawElements(GL_TRIANGLES,(num_triangulos*3),GL_UNSIGNED_INT, triangulos);
    glDisableClientState(GL_VERTEX_ARRAY);


    if(normalActivada) {
        glDisableClientState(GL_NORMAL_ARRAY);
    }

}

int long igvMallaTriangulos::getNumVertices() {
	return num_vertices;
}

int long igvMallaTriangulos::getNumTriangulos() {
	return num_triangulos;
}

unsigned int* igvMallaTriangulos::getTriangulos() {
	return triangulos;
}

float* igvMallaTriangulos::getNormal() {
	return normales;
}

float* igvMallaTriangulos::getVertices() {
	return vertices;
}

bool igvMallaTriangulos::get_normalActivada() {
    return normalActivada;
}

void igvMallaTriangulos::set_normalActivada(bool valor) {
    this->normalActivada = valor;
}

bool igvMallaTriangulos::get_sombreado() {
    return sombreado;
}

void igvMallaTriangulos::set_sombreado(bool valor) {
    this->sombreado = valor;
}
