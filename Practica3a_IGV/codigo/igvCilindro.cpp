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
	vertices = new float[num_vertices*3];

	float anguloAlfa = 360 / divU; //calculamos el angulo de apertura de los vertices.
	float sumatorioAnglo = 0;
	float salto = a / divV;
	int capas = divV + 1;
	int nCapa = 0;
	for (float j = -salto; j < a; j += salto) {
		for (int i = 0; i < divU; i++)
		{
			float anguloConvertido = (sumatorioAnglo * PI) / 180;
			float puntoX = cos(anguloConvertido) * r;
			float puntoZ = sin(anguloConvertido) * r;
			
			sumatorioAnglo += anguloAlfa;

			vertices[(3 * nCapa)] = puntoX;
			vertices[(3 * nCapa) + 1] = j;
			vertices[(3 * nCapa) + 2] = puntoZ;
			nCapa++;

		}
		std::cout << "Salto: " << j << std::endl;
		sumatorioAnglo = 0;
	}

	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
	delete[] vertices;
	vertices = nullptr;
	
}
