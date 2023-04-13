//
// Created by hgallegos on 30/03/2023.
//

#include "vec3.h"

vec3 operator*(float f, vec3 v) { return vec3(v.x * f, v.y * f, v.z*f); }