#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D():ambiente(1,1,1),difuso(1,1,1),especular(1,1,1),phong(120.0),posicion(3,3,3) {
    
    //Inicializacion de variables
	ejes = true;

    anguloTorsoSuperior = 30.0;
    anguloCabeza = 12.0;
    anguloPirnaIzquierda = 0;
    anguloPiernaDerecha = 0;
    anguloBrazoDerecho = 0;
    anguloBrazoIzquierdo = 0;
    anguloAntebrazoIzquierdo = -30.0;
    anguloAntebrazoDerecho = 30.0;
    animacion = false;
               
    //Creacion del modelo de los planetas
   glm::vec3 posicionTierra = glm::vec3(6.5,6.5,5);
   glm::vec3 posicionLuna = glm::vec3(-6.5,0.5,-5);
   
   Face* tierra = new Face(10 / 255, 10 / 255, 10 / 255,posicionTierra);
   Face* luna = new Face(255 / 255, 255 / 255, 10 / 255,posicionLuna);
   
   //Añadimos al vector de objetos
   objetos.push_back(tierra);
   objetos.push_back(luna);
    
    
}

//Destructor, se borran los elememntos
igvEscena3D::~igvEscena3D() {
    delete textura;
    if(objetos.size() > 0){
        delete objetos[0];
        
        delete objetos[1];
    }
    objetos.clear();
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



/**
 * Pinta la zona del torso inferior
 * */
void igvEscena3D::pintarTorsoInferior(){
    glPushMatrix();
    glTranslated(0, 0.5, 0);
    glRotated(90, 1 ,0,0);
    gluCylinder(gluNewQuadric(), 1 ,1, 1,16,16);

    glPopMatrix();

}

/**
 *Pinta el torso superior
 * */
void igvEscena3D::pintarTorsoSuperior() {
    glPushMatrix();
        glTranslated(0,1.5,0);
        glRotated(90, 1 ,0,0);

        gluCylinder(gluNewQuadric(), 1 ,1.0, 1,16,16);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.5,0);
        glutSolidSphere(1, 16,16);
    glPopMatrix();
}
/**
 * Pinta la cabeza
 * */
void igvEscena3D::pintarCabeza() {
    GLfloat verde[] = { 0,1,0,1.0 };
    GLfloat ojos[] = { 0,0,0,1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION,verde);
    glPushMatrix();
        glTranslated(0.7,2.5,1);//Cabeza
        glutSolidSphere(0.7,16,16);

        //Pintar ojos
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, ojos);
        glTranslated(-0.2,0.5,0.4);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, ojos);
        glTranslated(0.4,0.4,0.4);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

    glPopMatrix();

}

/**
 *Pinta los brazos
 */
void igvEscena3D::pintarBrazos() {
    GLfloat negro[] = { 0,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };;
    //brazo izquierdo
    glMaterialfv(GL_FRONT, GL_EMISSION, negro);
    glPushMatrix();

        glTranslatef(-1,1.5,0.3);
        glRotatef(80, 1,0,0);
        glRotatef(-30, 0,1,0);
        glRotatef(anguloBrazoIzquierdo,1,0,0);//
        gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glutSolidSphere(0.14,16,16);
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glTranslatef(0,0,0.82);
            glutSolidSphere(0.14,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, negro);
                glTranslatef(0,0,0.08);
                glRotatef(anguloAntebrazoIzquierdo,1,0,0);
                gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

                glPushMatrix();
                    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                    glTranslatef(0,0,0.93);
                    glScalef(0.3,0.2,0.3);
                    glutSolidCube(1);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Brazo derecho.

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, negro);
        glTranslatef(1,1.5,0.3);
        glRotatef(80, 1,0,0);
        glRotatef(30, 0,1,0);
        glRotatef(anguloBrazoDerecho,1,0,0);
        gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glutSolidSphere(0.14,16,16);
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, verde);
            glTranslatef(0,0,0.82);
            glutSolidSphere(0.14,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, negro);
                glTranslatef(0,0,0.08);
                glRotatef(anguloAntebrazoDerecho,-1,0,0);
                gluCylinder(gluNewQuadric(), 0.14 ,0.14, 0.8,16,16);

                glPushMatrix();
                    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                    glTranslatef(0,0,0.93);
                    glScalef(0.3,0.2,0.3);
                    glutSolidCube(1);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


}

/**
 * Función encargada de pintar las piernas
 */
void igvEscena3D::pintarPiernas() {
    GLfloat negro[] = { 0,0,0,1.0 };
    GLfloat verde[] = { 0,1,0,1.0 };;
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, verde);
        glTranslatef(-0.6,-0.5,0);
        glRotatef(anguloPirnaIzquierda,1,0,0);
        glutSolidSphere(0.14,16,16);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, negro);
            glRotatef(90,1,0,0);
            gluCylinder(gluNewQuadric(), 0.14 ,0.14, 1.6,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                glTranslatef(0,0,1.8);
                glRotatef(90,1,0,0);
                glRotatef(-5,0,1,0);
                glScalef(0.7,0.2,1);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    //pierna derecha
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, verde);
        glTranslatef(0.6,-0.5,0);
        glRotatef(anguloPiernaDerecha,1,0,0);
        glutSolidSphere(0.14,16,16);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_EMISSION, negro);
            glRotatef(90,1,0,0);
            gluCylinder(gluNewQuadric(), 0.14 ,0.14, 1.6,16,16);
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_EMISSION, verde);
                glTranslatef(0,0,1.8);
                glRotatef(90,1,0,0);
                glRotatef(-5,0,1,0);
                glScalef(0.7,0.2,1);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}





/**
 Visualizacion del modelo
 */
void igvEscena3D::visualizar() {
	// crear luces

    glShadeModel(GL_SMOOTH);
    
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

        // se pintan los ejes
        if (ejes) pintar_ejes();

        double a0 = 1.0;
        double a1 = 0.0;
        double a2 = 0.0;

        //Fuentes de luz puntual y foco
        igvFuenteLuz puntual(GL_LIGHT0,igvPunto3D(-1,0,-1),igvColor(0.0,0.0,0.0,1.0),igvColor(0.5,0.5,0.5,1.0),igvColor(1.0,1.0,1.0,1.0),a0,a1,a2);
        puntual.encender();
        puntual.aplicar();

        igvFuenteLuz foco(GL_LIGHT1,posicion,igvColor(0.0,0.0,0.0,1.0),igvColor(0.5,0.5,0.5,0.2),igvColor(0.5,0.5,0.5,0.2),a0,a1,a2,igvPunto3D(0.0,0.0,0.0),40,256);
        foco.encender();
        foco.aplicar();
        
        //Material de la luz
        igvMaterial material(ambiente,difuso ,especular,phong);
        material.aplicar();


        GLfloat rojo[] = { 1,0,0,1.0 };
        GLfloat verde[] = { 0,1,0,1.0 };
        GLfloat azul[] = { 0,0,1,1.0 };


        //Pinta parte inferior del muñeco
        glPushMatrix();
            glRotatef(30,0,1,0);
            glMaterialfv(GL_FRONT, GL_EMISSION, azul);
            pintarTorsoInferior();
            pintarPiernas();
        glPopMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, rojo);

        //Parte superior del muñeco
        glPushMatrix();
            glRotated(anguloTorsoSuperior, 0 ,1,0);
            pintarTorsoSuperior();
            pintarBrazos();
            glPushMatrix();
                glTranslatef(0,2.5,0.5);
                glRotatef(anguloCabeza,0,1,1);
                glTranslatef(-0.7,-2.5,-1);
                pintarCabeza();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    
    //Se inicializa la textura si no se ha hecho y se cargan
    if(textura == nullptr){
        textura = new igvTextura("tierra.png");
        
    }
    
    if(textura2 == nullptr){
        textura2 = new igvTextura("luna.png");
        
    }
    
    //Visualizacion de los planetas con texturas asignadas
    glPushMatrix();
        textura->aplicar();
        objetos[0]->visualizar();
    
        textura2->aplicar();
        objetos[1]->visualizar();
    glPopMatrix();


}

//Visualizacion sin luces ni texturas
void igvEscena3D::visualizarVB(){
    glPushMatrix();
    objetos[0]->visualizar();
    objetos[1]->visualizar();
    glPopMatrix();
}

//Getters y setters
std::vector<Face*> igvEscena3D::getObjetos(){
    return objetos;
}

void igvEscena3D::setAnguloCabeza(float anguloCabeza) {
    igvEscena3D::anguloCabeza = anguloCabeza;
}

void igvEscena3D::setAnguloTorsoSuperior(float anguloTorsoSuperior) {
    igvEscena3D::anguloTorsoSuperior = anguloTorsoSuperior;
}

void igvEscena3D::setAnguloBrazoIzquierdo(float anguloBrazoIzquierdo) {
    igvEscena3D::anguloBrazoIzquierdo = anguloBrazoIzquierdo;
}

void igvEscena3D::setAnguloBrazoDerecho(float anguloBrazoDerecho) {
    igvEscena3D::anguloBrazoDerecho = anguloBrazoDerecho;
}

void igvEscena3D::setAnguloAntebrazoIzquierdo(float anguloAntebrazoIzquierdo) {
    igvEscena3D::anguloAntebrazoIzquierdo = anguloAntebrazoIzquierdo;
}

void igvEscena3D::setAnguloAntebrazoDerecho(float anguloAntebrazoDerecho) {
    igvEscena3D::anguloAntebrazoDerecho = anguloAntebrazoDerecho;
}

float igvEscena3D::getAnguloCabeza() const {
    return anguloCabeza;
}

float igvEscena3D::getAnguloTorsoSuperior() const {
    return anguloTorsoSuperior;
}

float igvEscena3D::getAnguloBrazoIzquierdo() const {
    return anguloBrazoIzquierdo;
}

float igvEscena3D::getAnguloBrazoDerecho() const {
    return anguloBrazoDerecho;
}

float igvEscena3D::getAnguloAntebrazoIzquierdo() const {
    return anguloAntebrazoIzquierdo;
}

float igvEscena3D::getAnguloAntebrazoDerecho() const {
    return anguloAntebrazoDerecho;
}

void igvEscena3D::setAnguloPirnaIzquierda(float anguloPirnaIzquierda) {
    igvEscena3D::anguloPirnaIzquierda = anguloPirnaIzquierda;
}

void igvEscena3D::setAnguloPiernaDerecha(float anguloPiernaDerecha) {
    igvEscena3D::anguloPiernaDerecha = anguloPiernaDerecha;
}

float igvEscena3D::getAnguloPirnaIzquierda() const {
    return anguloPirnaIzquierda;
}

float igvEscena3D::getAnguloPiernaDerecha() const {
    return anguloPiernaDerecha;
}

void igvEscena3D::setAnimacion(bool animacion) {
    igvEscena3D::animacion = animacion;
}

bool igvEscena3D::isAnimacion() const {
    return animacion;
}






