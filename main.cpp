#include <iostream>
#include "Camara.h"
void escena1();
void escena2();
int main() {
    escena2();

    return 0;
}
void escena1() {
    vector<Objeto*> objetos;
    Objeto *p1;
    p1 = new Esfera(vec3(10,0,0), 8, vec3(0,0,1));
    p1->setConstantes(1, 0);
    p1->ke = 1;
    objetos.emplace_back(p1);
    p1 = new Esfera(vec3(10,0,20), 8, vec3(0.1,0.1,0.1));
    p1->setConstantes(0.8, 0.2);
    p1->ke = 0.9;
    p1->es_transparente = true;
    p1->ior=1.5;
    objetos.emplace_back(p1);
    p1 = new Esfera(vec3(0,10,0), 8, vec3(1,0,0));
    p1->setConstantes(0.6, 0.4, 32);
    p1->ke = 0.8;
    p1->es_transparente = false;
    p1->ior = 1.2;
    objetos.emplace_back(p1);

    p1 = new Plano(vec3(0,1,0), 1, vec3(0.123, 0.456, 0.789));
    p1->setConstantes(0.9, 0.1);
    p1->ke = 0.1;
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(-20,0,0), vec3(-10,10,0),5, vec3(0,1,1));
    p1->setConstantes(0.7,0.3,8);
    objetos.emplace_back(p1);


    vector<Luz*> luces;
    Luz luz(vec3(30,30,30), vec3(1,1,1));
    luces.emplace_back(&luz);

    Camara cam;
    for (int x = 0, n=1; x < 5; x++, n++){
        cam.configurar(3,60,600,800,
                       vec3(x,5,50),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
    }
}
void escena2() {
    vector<Objeto*> objetos;
    Objeto *p1;
    p1 = new Plano(vec3(0,1,0), 1, vec3(0.123, 0.456, 0.789));
    p1->setConstantes(0.9, 0.1);
    p1->ke = 0.1;
    objetos.emplace_back(p1);

    p1 = new Cilindro(vec3(5,4,0), vec3(5,14,0),5, vec3(0,1,1));
    p1->setConstantes(0.7,0.3,8);
    p1->es_transparente = true;
    p1->ior = 1.3;
    objetos.emplace_back(p1);

    p1 = new Esfera(vec3(5,0,-20), 8, vec3(1,0.1,0.1));
    p1->setConstantes(0.8, 0.2);
    p1->ke = 0.9;
    p1->es_transparente = true;
    p1->ior=1.5;
    objetos.emplace_back(p1);

    vector<Luz*> luces;
    Luz luz(vec3(30,30,30), vec3(1,1,1));
    luces.emplace_back(&luz);

    Camara cam;
    for (int y = 1, n=1; y < 100; y+=4, n++){
        cam.configurar(3,60,600,800,
                       vec3(1,y,50),
                       vec3(0,0,0),
                       vec3(0,1,0));
        cam.renderizar(objetos, luces, n);
    }
}