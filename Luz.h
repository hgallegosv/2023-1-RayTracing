//
// Created by hgallegos on 5/04/2023.
//

#ifndef CG2023_LUZ_H
#define CG2023_LUZ_H
#include "vec3.h"

class Luz {
public:
    vec3 pos, color;
    Luz(vec3 _pos, vec3 _color): pos(_pos), color(_color){};
};


#endif //CG2023_LUZ_H
