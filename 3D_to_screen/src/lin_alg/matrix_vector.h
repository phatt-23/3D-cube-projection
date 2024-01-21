#pragma once

#include "vector.h"
#include "matrix.h"

VEC2 mat22_vec2  (MAT22* mat, VEC2* vec);
VEC3 mat33_vec3  (MAT33* mat, VEC3* vec);
VEC3f mat33_vec3f  (MAT33f* mat, VEC3f* vec);
VEC2 mat23_vec3  (MAT23* mat, VEC3* vec);
VEC3 mat32_vec2  (MAT32* mat, VEC2* vec);

