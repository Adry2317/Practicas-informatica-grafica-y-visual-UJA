#include "igvTextura.h"

// Metodos constructores y destructor
igvTextura::igvTextura(){
    
}


igvTextura::igvTextura(std::string fichero) {

    idTextura = 1;
    
    //Se carga la textura con la libreria de lodepng.
    std::vector<unsigned char> imagen;
    unsigned ancho, alto;
    unsigned error = lodepng::decode(imagen,ancho,alto,fichero);

    if(error){
        std::string mensaje = "no se puede cargar";
        throw std::runtime_error(mensaje);
    }

    unsigned char* imgPtr = &imagen[0];
    int numeroComponentesColor = 4;
    int incrementoAncho = ancho * numeroComponentesColor;
    unsigned char* top = nullptr;
    unsigned char* bottom = nullptr;
    unsigned char temp = 0;

    //Como los carga al reves hay que darle la vuelta
    for(int i = 0; i < alto/2; i++){
        top = imgPtr + i * incrementoAncho;
        bottom = imgPtr + (alto -i -1) * incrementoAncho;
        for(int j = 0; j < incrementoAncho; j++){
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            ++top;
            ++bottom;
        }
    }

    
    //Parametros de la textura
    glGenTextures(1,&idTextura);
    glBindTexture(GL_TEXTURE_2D,idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,ancho,alto,0,GL_RGBA,GL_UNSIGNED_BYTE, imagen.data());


}


//Aplica la textura correspondiente
void igvTextura::aplicar(void) {
    glActiveTexture(GL_TEXTURE + idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);
    
}

//Destructor
igvTextura::~igvTextura() {
  glDeleteTextures(1, &idTextura);
}
