#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

using namespace std;

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
    brazoArriba = false;
    limiteCabeza = false;
    limTorso = false;

}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {

    igvPunto3D p0,r,V;

    p0 = igvPunto3D(6.0, 4.0, 8);
    r = igvPunto3D(0, 0, 0);
    V = igvPunto3D(0, 1.0, 0);

    //Vista Normal
    p0Vistas.push_back(p0);
    rVistas.push_back(r);
    Vvistas.push_back(V);

    //Vista Planta
    p0Vistas.push_back(igvPunto3D(0,-5,0));
    rVistas.push_back(igvPunto3D(0,0,0));
    Vvistas.push_back(igvPunto3D(1.0,0,0));

    //Vista Perfil
    p0Vistas.push_back(igvPunto3D(5, 0, 0));
    rVistas.push_back(igvPunto3D(0, 0, 0));
    Vvistas.push_back(igvPunto3D(0, 1.0, 0));

    //Vista Alzado
    p0Vistas.push_back(igvPunto3D(0, 0, 5));
    rVistas.push_back(igvPunto3D(0, 0, 0));
    Vvistas.push_back(igvPunto3D(0, 1.0, 0));

    interfaz.camara.set(IGV_PARALELA, p0, r, V,
                        -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3, 200);

    camara.angulo = 60;
    camara.raspecto = 1.0;


    //Creacion de las 4 camaras
    for (int i = 0; i < interfaz.p0Vistas.size(); i++)
    {
        igvCamara nuevaCamara;
        nuevaCamara.set(IGV_PARALELA, p0Vistas[i], rVistas[i], Vvistas[i],
                        -1 * 5, 1 * 5, -1 * 5, 1 * 5, 1, 200);
        nuevaCamara.angulo = 60.0;
        nuevaCamara.raspecto = 1.0;
        nuevaCamara.vis = poscam (i);


        interfaz.vectorCamaras.push_back(nuevaCamara);
    }

}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y,
	string _titulo) {
	// inicializacion de las variables de la interfaz
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializacion de la ventana de visualizacion
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(1.0, 1.0, 1.0, 0.0); // establece el color de fondo de la ventana
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		////// Apartado C: incluir aqui el cambio de la camara para mostrar las vistas planta, perfil, alzado o perspectiva
		////// Apartado C: incluir aqui la modificacion de los grados de libertad del modelo pulsando las teclas correspondientes

	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);

		break;

    case 't': //activa movimiento torso superior
        if(interfaz.escena.getAnguloTorsoSuperior() < 90) {
            interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() + 5);
        }
        break;
    case 'T': //activa movimiento torso superior
        if(interfaz.escena.getAnguloTorsoSuperior() > 5 ){
            interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() - 5);
        }
        break;
    case 'c'://activa movimiento cabeza
        if(interfaz.escena.getAnguloCabeza() < 33){
            interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()+5);
        }
        break;
    case 'C':
        if(interfaz.escena.getAnguloCabeza() > -12){
            interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()-5);
        }
    break;
    case 'p'://PIERNA DERECHA HACIA DELANTE
        if(interfaz.escena.getAnguloPiernaDerecha() > -45){
            interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha() - 5);
        }
        break;
    case 'P'://PIERNA DERECHA HACIA ATRAS
        if(interfaz.escena.getAnguloPiernaDerecha() < 45){
            interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()+5);
        }
    break;
    case 'o'://PIERNA IZQUIEDA HACIA DELANTE
        if(interfaz.escena.getAnguloPirnaIzquierda() > -45){
            interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda() - 5);
        }
        break;
    case 'O'://PIERNA IZQUIERDA HACIA ATRAS
        if(interfaz.escena.getAnguloPirnaIzquierda() < 45){
            interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()+5);
        }
        break;
    case 'b': //BRAZO SUPERIOR DERECHO HACIA DELANTE
        if(interfaz.escena.getAnguloBrazoDerecho() > -90){
            interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() - 5);
        }
        break;

    case 'B': //BRAZO SUPERIOR DERECHO HACIA ATRAS
        if(interfaz.escena.getAnguloBrazoDerecho()<80){
            interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho()+5);
        }
        break;

    case 'f': //BRAZO SUPERIOR IZQUIERDO HACIA DELANTE
        if(interfaz.escena.getAnguloBrazoIzquierdo() > -90){
            interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() - 5);
        }
        break;

    case 'F': //BRAZO SUPERIOR IZQUIERDO HACIA ATRAS
        if(interfaz.escena.getAnguloBrazoIzquierdo()<80){
            interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo()+5);
        }
        break;


    case 'd': //ANTEBRAZO IZQUIERDO HACIA DELANTE
        if(interfaz.escena.getAnguloAntebrazoIzquierdo() > -90){
            interfaz.escena.setAnguloAntebrazoIzquierdo(interfaz.escena.getAnguloAntebrazoIzquierdo() - 5);
        }
        break;

    case 'D': //ANTEBRAZO IZQUIERDO HACIA ATRAS
        if(interfaz.escena.getAnguloAntebrazoIzquierdo()<0){
            interfaz.escena.setAnguloAntebrazoIzquierdo(interfaz.escena.getAnguloAntebrazoIzquierdo()+5);
        }
        break;

    case 's': //ANTEBRAZO DERECHO HACIA DELANTE
        if(interfaz.escena.getAnguloAntebrazoDerecho() <90){
            interfaz.escena.setAnguloAntebrazoDerecho(interfaz.escena.getAnguloAntebrazoDerecho() + 5);
        }
        break;

    case 'S': //ANTEBRAZO DERECHO HACIA ATRAS
        if(interfaz.escena.getAnguloAntebrazoDerecho()>0){
            interfaz.escena.setAnguloAntebrazoDerecho(interfaz.escena.getAnguloAntebrazoDerecho()-5);
        }
        break;
    case 'a':
        if(interfaz.escena.isAnimacion()){
            interfaz.escena.setAnimacion(false);
        }else{
            interfaz.escena.setAnimacion(true);
        }
        break;

    case 'V': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzadoo perspectiva
        if (!interfaz.cuatroCamaras) {
            switch (interfaz.camara.vis)
            {
                case alzado:
                    interfaz.camara.set(interfaz.p0Vistas[perfil], interfaz.rVistas[perfil], interfaz.Vvistas[perfil]);
                    interfaz.camara.vis = perfil;
                    break;
                case perfil:
                    interfaz.camara.set(interfaz.p0Vistas[planta], interfaz.rVistas[planta], interfaz.Vvistas[planta]);
                    interfaz.camara.vis = planta;
                    break;
                case planta:
                    interfaz.camara.set(interfaz.p0Vistas[panoramica], interfaz.rVistas[panoramica], interfaz.Vvistas[panoramica]);
                    interfaz.camara.vis = panoramica;
                    break;
                case panoramica:
                    interfaz.camara.set(interfaz.p0Vistas[alzado], interfaz.rVistas[alzado], interfaz.Vvistas[alzado]);
                    interfaz.camara.vis = alzado;
                    break;
            }

        }
        else {//Se muestran las cuatro camaras
            for (int i = 0; i < interfaz.vectorCamaras.size(); i++)
            {
                switch (interfaz.vectorCamaras[i].vis)
                {
                    case alzado:
                        interfaz.vectorCamaras[i].set(interfaz.p0Vistas[perfil], interfaz.rVistas[perfil], interfaz.Vvistas[perfil]);
                        interfaz.vectorCamaras[i].vis = perfil;
                        break;
                    case perfil:
                        interfaz.vectorCamaras[i].set(interfaz.p0Vistas[planta], interfaz.rVistas[planta], interfaz.Vvistas[planta]);
                        interfaz.vectorCamaras[i].vis = planta;
                        break;
                    case planta:
                        interfaz.vectorCamaras[i].set(interfaz.p0Vistas[panoramica], interfaz.rVistas[panoramica], interfaz.Vvistas[panoramica]);
                        interfaz.vectorCamaras[i].vis = panoramica;
                        break;
                    case panoramica:
                        interfaz.vectorCamaras[i].set(interfaz.p0Vistas[alzado], interfaz.rVistas[alzado], interfaz.Vvistas[alzado]);
                        interfaz.vectorCamaras[i].vis = alzado;
                        break;
                }
            }

        }

        interfaz.camara.aplicar();
        break;

        case '+': // zoom in
            if (!interfaz.cuatroCamaras) {

                if (interfaz.camara.angulo > 10) { //comprobamos que no se reduzca menos de un 5% el angulo de la camara.
                    interfaz.camara.zoom(0.95);
                }

                interfaz.camara.aplicar();
            }
            else {//Se muestran las cuatro camaras
                for (int i = 0; i < interfaz.vectorCamaras.size(); i++) {
                    if (interfaz.vectorCamaras[i].angulo > 10) { //comprobamos que no se reduzca menos de un 5% el angulo de la camara.
                        interfaz.vectorCamaras[i].zoom(0.95);
                    }

                    interfaz.vectorCamaras[i].aplicar();
                }
            }
            break;
        case '-': // zoom out
            if (!interfaz.cuatroCamaras) {
                if (interfaz.camara.angulo <= 175) { //Comprobamos que no se abra el ángulo de la camara más de 180 grados
                    interfaz.camara.zoom(1.05);
                }
                interfaz.camara.aplicar();
            }
            else {//Se muestran las cuatro camaras
                for (int i = 0; i < interfaz.vectorCamaras.size(); i++) {
                    if (interfaz.vectorCamaras[i].angulo <= 175) { //comprobamos que no se reduzca menos de un 5% el angulo de la camara.
                        interfaz.vectorCamaras[i].zoom(1.05);
                    }

                    interfaz.vectorCamaras[i].aplicar();
                }
            }
            break;

        case '4': // dividir la ventana  en cuatro vistas
            if (!interfaz.cuatroCamaras) {
                interfaz.cuatroCamaras = true;
            }
            else {
                interfaz.cuatroCamaras = false;
            }

            break;
        //Activa los disntintos movimiento de la camara y con los cursores se mueven
        case 'r':
            interfaz.camara.movimientoActivado = roll;
            break;
        case 'x':
            interfaz.camara.movimientoActivado = pan;
            break;

        case 'X':
            interfaz.camara.movimientoActivado = tilt;
            break;
        case 'm':
            interfaz.camara.movimientoActivado = orbit;
            break;
        case 'M':
            interfaz.camara.movimientoActivado = dolly;
            break;
        case 'w':
            interfaz.camara.movimientoActivado = boomCrane;
            break;
        case 'W':
            interfaz.camara.movimientoActivado = truck;
            break;
        case 'l'://Cambio de perspectiva a paralela
            if(interfaz.camara.tipo == IGV_PARALELA){
                interfaz.camara.set(IGV_PERSPECTIVA,interfaz.camara.getP0(), interfaz.camara.getR(),interfaz.camara.getV(),
                                    -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3, 200);
            }
            else if(interfaz.camara.tipo == IGV_PERSPECTIVA) {
                interfaz.camara.set(IGV_PARALELA,interfaz.camara.getP0(), interfaz.camara.getR(),interfaz.camara.getV(),
                                    -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 3, 200);
            }
            interfaz.camara.aplicar();
            break;

        case 27: // tecla de escape para SALIR
            exit(1);
            break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parametros de la camara y de la proyeccion
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

    // se establece el viewport

    if (interfaz.cuatroCamaras) { //Si se seleccionan el cuatro, dividimos la ventana en cuatro, donde mostraremos las cuatro camaras creadas anteriormente.
        glViewport(interfaz.get_ancho_ventana() / 2, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
        interfaz.vectorCamaras[3].aplicar();
        interfaz.escena.visualizar();

        glViewport(0, interfaz.get_alto_ventana() / 2, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
        interfaz.vectorCamaras[0].aplicar();
        interfaz.escena.visualizar();

        glViewport(interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
        interfaz.vectorCamaras[1].aplicar();
        interfaz.escena.visualizar();

        glViewport(0, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana() / 2);
        interfaz.vectorCamaras[2].aplicar();
        interfaz.escena.visualizar();

    }
    else {//Se muestra solo una ventan, por defecto.
        glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());
        //visualiza la escena
        interfaz.camara.aplicar();
        interfaz.escena.visualizar();

    }
    
    
    
    if (interfaz.modo == IGV_SELECCIONAR) {
            //Para que funcione habrá que dibujar la escena sin efectos, sin iluminación, sin texturas ...
            glDisable(GL_LIGHTING); // desactiva la iluminacion de la escena
            glDisable(GL_DITHER);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_CULL_FACE);

            //Reestablece los colores como no seleccionado
            if(interfaz.objeto_seleccionado != -1){
                interfaz.escena.getObjetos()[interfaz.objeto_seleccionado]->setSeleccionada(false);
                interfaz.objeto_seleccionado = -1;
            }
            
            //aplica la cámara
            interfaz.camara.aplicar();

            //visualiza los BV cada uno de un color
            interfaz.escena.visualizarVB();

            //Obtener el color del pixel seleccionado
            GLubyte pixel[3];
            glReadPixels(interfaz.cursorX, interfaz.alto_ventana-interfaz.cursorY,1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    
            int cont = 0;
            for(int i = 0; i < interfaz.escena.getObjetos().size(); i++){
                for(int j = 0; j < 3; j++){
                    if(interfaz.escena.getObjetos()[i]->getColorByte()[j] == pixel[j]){
                        cont++;
                    }
                }
                //Si las tres componentes de color del pixel coinciden se selecciona
                if(cont == 3){
                    cout<<"Objeto: "<<i<<endl;
                    interfaz.objeto_seleccionado = i;
                    interfaz.escena.getObjetos()[interfaz.objeto_seleccionado]->setSeleccionada(true);
                    break;
                }
                cont = 0;
            }

            //Cambiar a modo de visualización de la escena
            interfaz.modo = IGV_VISUALIZAR;

            //Habilitar de nuevo la iluminación
            glEnable(GL_LIGHTING);
            glEnable(GL_DITHER);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_CULL_FACE);
        
        }else{
           // aplica las transformaciones en función de los parámetros de la cámara
           interfaz.camara.aplicar();
           // visualiza la escena
           interfaz.escena.visualizar();

           // refresca la ventana
           glutSwapBuffers();
        }
    
}

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {

    //comprobar que se ha pulsado el botón izquierdo
    if(boton == GLUT_LEFT_BUTTON){
        interfaz.cursorX = x;
        interfaz.cursorY = y;
        if(estado == GLUT_DOWN){
            //Si se mantiene el boton cambia a seleccionar
            interfaz.boton_retenido = true;
            interfaz.modo = IGV_SELECCIONAR;
        }else{
            interfaz.boton_retenido = false;
        }
    }
    glutPostRedisplay();
}

void igvInterfaz::set_glutMotionFunc(GLint x, GLint y) {

    // si el botón está retenido y hay algún objeto seleccionado,
    // comprobar el objeto seleccionado y la posición del ratón y rotar
    // el objeto seleccionado utilziando el desplazamiento entre la posición
    //inicial y final del ratón
    if(interfaz.boton_retenido && interfaz.objeto_seleccionado != -1){
        float distX = x - interfaz.cursorX;
        //float distY = y - interfaz.cursorY;
        interfaz.escena.getObjetos()[interfaz.objeto_seleccionado]->setRotacion(distX);
        interfaz.cursorX = x;
        interfaz.cursorY = y;
        
    }
    
    glutPostRedisplay();


}

void igvInterfaz::set_glutIdleFunc() {
	//codigo para animar el modelo de la manera mas realista posible
    
    if(interfaz.escena.isAnimacion()) {
        if(!interfaz.brazoArriba) {
            if (interfaz.escena.getAnguloBrazoDerecho() > -90) {
                interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() - 0.25);

            }else{
                interfaz.brazoArriba = true;
            }
            if(interfaz.escena.getAnguloPiernaDerecha()>-45){
                interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()-0.125);
            }

            //Bajar
            if (interfaz.escena.getAnguloBrazoIzquierdo() < 80) {
                interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() + 0.25);

            }
            if(interfaz.escena.getAnguloPirnaIzquierda()<45){
                interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()+0.125);
            }
        }else{
            if (interfaz.escena.getAnguloBrazoDerecho() < 80) {
                interfaz.escena.setAnguloBrazoDerecho(interfaz.escena.getAnguloBrazoDerecho() + 0.25);

            }else{
                interfaz.brazoArriba = false;
            }

            if(interfaz.escena.getAnguloPiernaDerecha()<45){
                interfaz.escena.setAnguloPiernaDerecha(interfaz.escena.getAnguloPiernaDerecha()+0.125);
            }

            if (interfaz.escena.getAnguloBrazoIzquierdo() > -90) {
                interfaz.escena.setAnguloBrazoIzquierdo(interfaz.escena.getAnguloBrazoIzquierdo() - 0.25);

            }

            if(interfaz.escena.getAnguloPirnaIzquierda()>-45){
                interfaz.escena.setAnguloPirnaIzquierda(interfaz.escena.getAnguloPirnaIzquierda()-0.125);
            }
        }

        if(!interfaz.isLimiteCabeza()){
            if(interfaz.escena.getAnguloCabeza() < 33){
                interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()+0.1);
            }else{
                interfaz.setLimiteCabeza(true);
            }
        }else{
            if(interfaz.escena.getAnguloCabeza() > -12){
                interfaz.escena.setAnguloCabeza(interfaz.escena.getAnguloCabeza()-0.1);
            }else{
                interfaz.setLimiteCabeza(false);
            }
        }

        if(!interfaz.isLimTorso()){
            if(interfaz.escena.getAnguloTorsoSuperior() < 70) {
                interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() + 0.07);
            }else{
                interfaz.setLimTorso(true);
            }
        }else{
            if(interfaz.escena.getAnguloTorsoSuperior() > 25 ){
                interfaz.escena.setAnguloTorsoSuperior(interfaz.escena.getAnguloTorsoSuperior() - 0.07);
            }else{
                interfaz.setLimTorso(false);
            }
        }
        glutPostRedisplay();
    }

}

//Llamadas a los callbacks
void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
    glutSpecialFunc(set_glutSpecialKeys);
    
    glutMouseFunc(set_glutMouseFunc);
    glutMotionFunc(set_glutMotionFunc);
}

//Movimiento flechas de direccion para cada tipo de movimiento de camara
void igvInterfaz::set_glutSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            switch (interfaz.camara.movimientoActivado) {
                case roll:
                    interfaz.camara.roll(-5);
                    break;

                case pan:
                    interfaz.camara.pan(5);
                    break;
                case dolly:
                    interfaz.camara.dolly(-1);
                    break;

                case orbit:
                    interfaz.camara.orbit(-5,0);
                    break;
            }
        break;

        case GLUT_KEY_RIGHT:
            switch (interfaz.camara.movimientoActivado) {
                case roll:
                    interfaz.camara.roll(5);
                    break;

                case pan:
                    interfaz.camara.pan(-5);
                    break;

                case orbit:
                    interfaz.camara.orbit(5,0);
                    break;
                case boomCrane:
                    interfaz.camara.boomCrane(1);
                    break;
                case dolly:
                        interfaz.camara.dolly(1);
                    break;
            }
            break;
        case GLUT_KEY_UP:
            switch (interfaz.camara.movimientoActivado) {
                case tilt:
                    interfaz.camara.tilt(-5);
                    break;
                case orbit:
                    interfaz.camara.orbit(0,5);
                    break;
                case boomCrane:
                    interfaz.camara.boomCrane(1);
                    break;
                case truck:
                    interfaz.camara.truck(0.3);
                    break;
            }
            break;
        case GLUT_KEY_DOWN:
            switch (interfaz.camara.movimientoActivado) {
                case tilt:
                    interfaz.camara.tilt(5);
                    break;
                case orbit:
                    interfaz.camara.orbit(0,-5);
                    break;
                case boomCrane:
                    interfaz.camara.boomCrane(-1);
                    break;
                case truck:
                    interfaz.camara.truck(-0.3);
                    break;
            }
            break;

    }
    glutPostRedisplay();
}


//Setters y getters
bool igvInterfaz::isBrazoArriba() const {
    return brazoArriba;
}

void igvInterfaz::setBrazoArriba(bool brazoArriba) {
    igvInterfaz::brazoArriba = brazoArriba;
}

void igvInterfaz::setLimiteCabeza(bool limiteCabeza) {
    igvInterfaz::limiteCabeza = limiteCabeza;
}

bool igvInterfaz::isLimiteCabeza() const {
    return limiteCabeza;
}


void igvInterfaz::setLimTorso(bool limTorso) {
    igvInterfaz::limTorso = limTorso;
}

bool igvInterfaz::isLimTorso() const {
    return limTorso;
}
