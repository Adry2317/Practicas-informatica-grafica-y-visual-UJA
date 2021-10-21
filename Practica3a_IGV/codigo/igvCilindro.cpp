#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV)
{
	//r --> radio colindro
	//a --> Altura, divU --> divisiones latrales, divV --> divisiones en altura.

	/* Apartado B: Construir la malla de triángulos para representar el cilindro */
	num_vertices = divU * (divV + 1);
	vertices = new float[num_vertices];

	float anguloAlfa = 360 / divU; //calculamos el angulo de apertura de los vertices.
	float sumatorioAnglo = 0;
	float salto = a / divV;
	int capas = divV + 1;

	for (float j = -a/capas; j < a/capas; j += salto) {
		for (int i = 0; i < divU; i++)
		{
			float anguloConvertido = (sumatorioAnglo * PI) / 180;
			float puntoX = cos(anguloConvertido) * r;
			float puntoZ = sin(anguloConvertido) * r;
			
			sumatorioAnglo += anguloAlfa;

			vertices[(3 * i)] = puntoX;
			vertices[(3 * i) + 1] = j;
			vertices[(3 * i) + 2] = puntoZ;

		}

		sumatorioAnglo = 0;
	}

	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
	delete[] vertices;
	vertices = nullptr;
	
}
