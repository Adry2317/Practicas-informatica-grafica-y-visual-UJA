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

	float anguloAlfa = 360 / divU; //calculamos el angulo de apertura de los vertices.
	int sumatorioAnglo = 0;


	for (int i = 0; i < divU; i++)
	{
		float puntoX = cos(sumatorioAnglo) * r;
		float puntoXGrados = (puntoX * PI) / 180;

		float puntoZ = sin(sumatorioAnglo) * r;
		float puntoYGrados = (puntoZ * PI) / 180;

		switch (sumatorioAnglo)
		{
		case (sumatorioAnglo<=90):
			break;
		}
	}


	/* Apartado C: Añadir el vector de normales */
}

igvCilindro::~igvCilindro()
{
}
