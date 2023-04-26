//
// Created by hgallegos on 30/03/2023.
//

#ifndef CG2023_RAYO_H
#define CG2023_RAYO_H

#include "vec3.h"
class Rayo {
public:
    vec3 ori, dir;
    Rayo(){}
    Rayo(vec3 _ori) { ori = _ori; }
    Rayo(vec3 _ori, vec3 _dir) {
        ori = _ori;
        dir = _dir;
    }
};


#endif //CG2023_RAYO_H
