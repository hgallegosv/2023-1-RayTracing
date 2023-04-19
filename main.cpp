#include <iostream>
#include "Camara.h"
int main() {
    Camara cam;
    for (int x = 0, n=1; x < 20; x++, n++){
        cam.configurar(3,60,600,800,
                       vec3(x,5,50),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(n);
    }

    return 0;
}
