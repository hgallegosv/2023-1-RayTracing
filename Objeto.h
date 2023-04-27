//
// Created by hgallegos on 30/03/2023.
//

#ifndef CG2023_OBJETO_H
#define CG2023_OBJETO_H
#include "vec3.h"
#include "Rayo.h"

class Objeto {
public:
    vec3 color;
    float kd, ks, n;
    float ke;  // constante de espejo
    bool es_transparente;
    float ior; // index of refraction
    bool es_luz;
    Objeto(vec3 col, float kd=1):color{col}, kd{kd}{
        ke = 0; es_transparente=false; ior=1;
        es_luz = 0;
    }

    void setConstantes(float kd=1, float ks=1, float n=8) {
        this->kd=kd; this->ks=ks; this->n = n;
    }
    //virtual bool intersectar(Rayo ray, float &t)=0;
    virtual bool intersectar(Rayo ray, float &t, vec3 &normal)=0;
};

class Esfera : public Objeto {
public:
    vec3 centro;
    float radio;

    Esfera(vec3 cen, float r, vec3 col, float kd=1): centro{cen}, radio{r}, Objeto(col, kd) {}
    bool intersectar(Rayo ray, float &t, vec3 &normal) {
        auto _a = ray.dir.punto(ray.dir);
        auto _b = 2*ray.dir.punto(ray.ori-centro);
        auto _c = (ray.ori-centro).punto(ray.ori-centro)-radio*radio;
        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}
        float t1 = (-_b + sqrt(D))/2*_a;
        float t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1, t2);
        if(t <= 0) {return false;}
        vec3 pi = ray.ori + ray.dir * t;
        normal = pi - centro;
        normal.normalize();
        return true;

    }
};
class Plano : public Objeto {
public:
    vec3 normal_plano;
    float d;
    Plano(vec3 normal, float dist, vec3 col): normal_plano(normal), Objeto(col) {
        normal_plano.normalize();
    }
    bool intersectar(Rayo ray, float &t, vec3 &normal) {
        float denominador = normal_plano.punto(ray.dir);
        if (denominador != 0) {
            t = (normal_plano*d - ray.ori).punto(normal_plano) / denominador;
            if (t < 0) {
                return false;
            }
            normal = normal_plano;
            return true;
        }
        return false;
    }
};

class Cilindro: public Objeto{
public:
    vec3 pa, pb;
    float ra;
    Cilindro(vec3 _pa, vec3 _pb, float _ra, vec3 _color):
    pa{_pa}, pb{_pb}, ra{_ra}, Objeto(_color){}
    bool intersectar(Rayo rayo, float &t, vec3 &normal);
};
#endif //CG2023_OBJETO_H
