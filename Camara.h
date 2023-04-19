//
// Created by hgallegos on 30/03/2023.
//

#ifndef CG2023_CAMARA_H
#define CG2023_CAMARA_H

#include "Rayo.h"
#include "vec3.h"
#include "CImg.h"
#include "Objeto.h"
#include "Luz.h"
#include <vector>
using namespace std;
using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
    vec3 eye, xe, ye, ze;
    float f, a, b, w, h;
    CImg<BYTE> *pImg;
    int prof_max;
public:
    Camara() { prof_max = 7; }
    void configurar(float _near, float fov, int ancho, int alto,
                    vec3 pos_eye, vec3 center, vec3 up);
    void renderizar(int num=1);

    vec3 calcular_color(Rayo rayo, vector<Objeto*> objetos, vector<Luz*> luces, int prof);

};


#endif //CG2023_CAMARA_H
