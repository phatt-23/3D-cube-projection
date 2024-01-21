#pragma once

#include <stdio.h>

typedef struct vec3d_int {
    int x, y, z;
} VEC3;

typedef struct vec3d_float {
    float x, y, z;
} VEC3f;

typedef struct vec2d_int {
    int x, y;
} VEC2;

typedef struct vec2d_float {
    float x, y;
} VEC2f;

void vec2_print  (VEC2  vec , const char* expression);
void vec3_print  (VEC3  vec , const char* expression);
void vec2f_print (VEC2f vec , const char* expression);
void vec3f_print (VEC3f vec , const char* expression);
VEC2 vec2_add    (VEC2* vec1, VEC2* vec2);
VEC3 vec3_add    (VEC3* vec1, VEC3* vec2);
VEC2 vec2_sub    (VEC2* vec1, VEC2* vec2);
VEC3 vec3_sub    (VEC3* vec1, VEC3* vec2);
VEC2 vec2_scale  (VEC2* vec , int scale);
VEC3 vec3_scale  (VEC3* vec , int scale);
VEC3f vec3f_scale  (VEC3f* vec , float scale);

