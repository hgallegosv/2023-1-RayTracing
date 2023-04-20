//
// Created by hgallegos on 30/03/2023.
//

#include "Objeto.h"
bool Cilindro::intersectar(Rayo rayo, float &t, vec3 &normal) {
    vec3 ro = rayo.ori;
    vec3 rd = rayo.dir;
    vec3 ca = pb-pa;
    vec3 oc = ro-pa;
    float caca = ca.punto(ca);
    float card = ca.punto(rd);
    float caoc = ca.punto(oc);
    float a = caca - card*card;
    float b = caca * oc.punto(rd) - caoc*card;
    float c = caca * oc.punto(oc) - caoc*caoc - ra*ra*caca;
    float h = b*b - a*c;
    if( h < 0.0 ) return false; //no intersection
    h = sqrt(h);
    t = (-b-h)/a;
    //if (t <= 0) return false;
    // body
    float y = caoc + t*card;
    if ( y > 0.0 && y < caca && t > 0) {
        normal = (oc + t*rd - ca*y/caca)/ra;
        normal.normalize();
        return true;
    }
    // caps
    t = (((y<0.0)?0.0:caca) - caoc)/card;
    if (t <= 0) return false;
    if( abs(b+a*t)<h ) {
        normal =  ca * sgn(y) / caca;
        normal.normalize();
        return true;
    }
    return false; //no intersection
}
