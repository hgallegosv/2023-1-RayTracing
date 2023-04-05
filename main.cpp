#include <iostream>
#include "Camara.h"
int main() {
    Camara cam;
    cam.configurar(3,60,600,800,
                   vec3(3,5,50),
                   vec3(0,0,0),
                   vec3(0,1,0));
    cam.renderizar();
    return 0;
}
