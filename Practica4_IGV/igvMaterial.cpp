#include "igvMaterial.h"
#include "igvPunto3D.h"

// Metodos constructores 

igvMaterial::igvMaterial () {
	
}

igvMaterial::~igvMaterial () {

}

igvMaterial::igvMaterial (const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {

// APARTADO B
// Aplicar los valores de los atributos del objeto igvMaterial:
// - coeficiente de reflexi�n de la luz ambiental
// - coeficiente de reflexi�n difuso
// - coeficiente de reflesi�n especular
// - exponente de Phong

    glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());
    glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());
    glMaterialf(GL_FRONT,GL_SHININESS,Ns);
    glMaterialfv(GL_FRONT, GL_EMISSION, igvPunto3D(0,0,0).cloneToFloatArray() );
// establecer como color de emisi�n (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)



}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



