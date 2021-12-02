#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

class igvEscena3D {
	protected:
		// Atributos
        igvColor ambiente;
        igvColor difuso;
        igvColor especular;
        float phong;
		bool ejes;
        igvPunto3D posicion;

	public:

		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar();

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};


    const igvColor &getAmbiente() const;

    void setAmbiente(const igvColor &ambiente);

    const igvColor &getDifuso() const;

    void setDifuso(const igvColor &difuso);

    const igvColor &getEspecular() const;

    void setEspecular(const igvColor &especular);

    float getPhong() const;

    void setPhong(float phong);

    const igvPunto3D &getPosicion() const;

    void setPosicion(const igvPunto3D &posicion);
};



#endif
