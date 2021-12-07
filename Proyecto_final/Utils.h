//
// Created by adry_ on 07/12/2021.
//

#ifndef PRACTICA3B_IGV_UTILS_H
#define PRACTICA3B_IGV_UTILS_H
#include "cmath"


class Utils {
public:
    virtual double normalizeI (int x, int y, int z){
        return sqrt((pow(x,2)+ pow(y,2)+ pow(z,2)));
    }

    virtual double normalizef (float x, float y, float z){
        return sqrt((pow(x,2)+ pow(y,2)+ pow(z,2)));
    }

    virtual double normalized (double x, double y, double z){
        return sqrt((pow(x,2)+ pow(y,2)+ pow(z,2)));
    }
};


#endif //PRACTICA3B_IGV_UTILS_H
