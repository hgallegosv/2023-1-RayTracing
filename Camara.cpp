//
// Created by hgallegos on 30/03/2023.
//

#include "Camara.h"
#include "Luz.h"
#include <vector>

using namespace std;
void Camara::configurar(float _near, float fov, int ancho, int alto,
                vec3 pos_eye, vec3 center, vec3 up) {
    f = _near;
    w = ancho;
    h = alto;
    a = 2 * f * tan(fov * M_PI/360);
    b = w / h * a;
    eye = pos_eye;
    ze = eye - center;
    ze.normalize();
    xe = up.cruz(ze);
    xe.normalize();
    ye = ze.cruz(xe);
}
void Camara::renderizar(int num) {
    Rayo rayo;
    rayo.ori = eye;
    vec3 dir;

    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");


    Esfera esf(vec3(2,0,0), 8, vec3(0,0,1));
    esf.kd = 0.8;

    vector<Objeto*> objetos;
    Objeto *p1;
    p1 = new Esfera(vec3(10,0,0), 8, vec3(0,0,1));
    p1->setConstantes(1, 0);
    objetos.emplace_back(p1);
    p1 = new Esfera(vec3(-10,0,0), 8, vec3(0,1,0));
    p1->setConstantes(0.8, 0.2);
    objetos.emplace_back(p1);
    p1 = new Esfera(vec3(0,10,0), 8, vec3(1,0,0));
    p1->setConstantes(0.6, 0.4, 32);
    objetos.emplace_back(p1);

    Luz luz(vec3(30,30,30), vec3(1,1,1));

    bool hay_interseccion;
    float t, t_tmp;
    vec3 color, normal, normal_tmp;
    Objeto *pObjeto = nullptr;
    for(int x=0;  x < w; x++) {
        for (int y = 0; y < h; y++) {
            dir = ze * (-f) + ye * a * (y / h - 0.5) + xe * b * (x / w - 0.5);
            dir.normalize();
            rayo.dir = dir;
            color.set(0,0,0);
            hay_interseccion = false;
            t = 1000000000;
            for(auto pObj : objetos) {
                if ( pObj->intersectar(rayo, t_tmp, normal_tmp)) {
                    hay_interseccion = true;
                    if (t_tmp < t) {
                        t = t_tmp;
                        normal = normal_tmp;
                        pObjeto = pObj;
                    }
                }
            }
            if ( hay_interseccion ) {
                vec3 pi = rayo.ori + rayo.dir * t;
                vec3 L = luz.pos - pi;
                L.normalize();
                vec3 luz_ambiente = vec3(1, 1, 1) * 0.2;
                // evaluar si hay sombra
                bool esta_sombra = false;
                Rayo rayo_sombra;
                rayo_sombra.ori = pi;
                rayo_sombra.dir = L;
                for(auto pObj : objetos) {
                    if ( pObj->intersectar(rayo_sombra, t_tmp, normal_tmp)) {
                        esta_sombra = true;
                    }
                }
                if (!esta_sombra) {
                    vec3 luz_difusa = vec3(0, 0, 0);
                    float factor_difuso = normal.punto(L);
                    if (factor_difuso > 0)
                        luz_difusa = luz.color * pObjeto->kd * factor_difuso;

                    vec3 luz_especular = vec3(0, 0, 0);
                    vec3 R = 2 * (L.punto(normal)) * normal - L;
                    vec3 V = -rayo.dir;
                    float factor_especular = R.punto(V);
                    if (factor_especular > 0)
                        luz_especular = luz.color * pObjeto->ks * pow(factor_especular, pObjeto->n);
                    color = pObjeto->color * (luz_ambiente + luz_difusa + luz_especular);
                    color.max_to_one();
                } else {
                    color = pObjeto->color * (luz_ambiente);
                }
            }
            (*pImg)(x,h-1-y,0) = (BYTE)(color.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color.z * 255);
        }
    }
    dis_img.render((*pImg));
    dis_img.paint();
    string nombre_archivo = "imagen" + to_string(num) + ".bmp";
    pImg->save(nombre_archivo.c_str());
    /*while (!dis_img.is_closed()) {
        dis_img.wait();
    }*/

}