#include "igvCilindro.h"

igvCilindro::igvCilindro() :igvMallaTriangulos()
{
}

igvCilindro::igvCilindro(float r, float a, int divU, int divV):igvMallaTriangulos()
{
    normalActivada = false;
    sombreado = false;
	//r --> radio colindro
	//a --> Altura, divU --> divisiones latrales, divV --> divisiones en altura.

	/* Apartado B: Construir la malla de tri�ngulos para representar el cilindro */
	this->num_vertices = divU * (divV + 1);

	this->vertices = new float[num_vertices * 3];
	float anguloAlfa = 360 / divU; //calculamos el angulo de apertura de los vertices.
	float sumatorioAnglo = 0;
	float salto = a / divV;

    //Calculo de los vertices
	int nCapa = 0;
	for (float j = -salto; j < a; j += salto) {
		for (int i = 0; i < divU; i++)
		{
			float anguloConvertido = (sumatorioAnglo * PI) / 180;
			float puntoX = cos(anguloConvertido) * r;
			float puntoZ = sin(anguloConvertido) * r;
			
			sumatorioAnglo += anguloAlfa;

			this->vertices[(3 * nCapa)] = puntoX;
			this->vertices[(3 * nCapa) + 1] = j;
			this->vertices[(3 * nCapa) + 2] = puntoZ;
			nCapa++;

		}

		sumatorioAnglo = 0;
	}

    //Calculo de triangulos
    num_triangulos = 2 * divU * divV;
    triangulos = new unsigned int[num_triangulos*3];
    int contT = 0;
    int nivel=1;

    for(int k = 0; k < (num_vertices - divU) ; k++){

        if(k<(divU*nivel)-1){
            //triangulo inferior
            this->triangulos[contT] = k;
            contT++;
            this->triangulos[contT] = (k+1);
            contT++;
            this->triangulos[contT] = (k+divU)+1;
            contT++;

            //triangulo superior
            this->triangulos[contT] = (k);
            contT++;
            this->triangulos[contT] =(k+divU+1);
            contT++;
            this->triangulos[contT] = (k+divU);
            contT++;
        }else{ //Union de los ultimos triangulos

            //Triangulo inferior
            this->triangulos[contT] = k;
            contT++;
            this->triangulos[contT] = (k-divU) +1;
            contT++;
            this->triangulos[contT] = k+1;
            contT++;

            //Triangulo superior
            this->triangulos[contT] = k;
            contT++;
            this->triangulos[contT] =k+1;
            contT++;
            this->triangulos[contT] = k+divU ;
            contT++;
            nivel++;

        }
    }


	/* Apartado C: Añadir el vector de normales */
    normales = new float[num_vertices*3];
    for (int i = 0; i < num_vertices*3; i= i+3){
        float x = vertices[i];
        float y = vertices[i+1];
        float z = vertices[i+2];


        float modulo = sqrtf(powf(x,2)+ powf(y,2)+ powf(z,2));
        normales[i] = x/modulo;
        normales[i+1] = y/modulo;
        normales[i+2] = z/modulo;

    }
}




igvCilindro::~igvCilindro()
{

	
}
