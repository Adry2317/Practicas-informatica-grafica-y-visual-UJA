
#include "igvMallaTriangulos.h"

#include <cmath> 

class igvCilindro : public igvMallaTriangulos {

private:
	int num_vertices;
	float* vertices;
	int num_triangulos;
	int* triangulos;
	const double PI = 3.14;
public:

	//// Constructores por y destructor
	igvCilindro();
	igvCilindro(float r, float a, int divU, int divV);
	~igvCilindro();

};

