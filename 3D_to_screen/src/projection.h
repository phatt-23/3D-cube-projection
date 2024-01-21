#ifndef INC_3D_TO_SCREEN_PROJECTION_H
#define INC_3D_TO_SCREEN_PROJECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "lin_alg/matrix_vector.h"

typedef struct canvas {
    int   width, height;
    char  filling_char;
    char* canvas;
    float distance, fov;
    int ccurrent;
    bool running;
    int slowdown;
    char fin[50];
} CANVAS;

void clear_canvas(CANVAS* c);
void clear_screen();

VEC2*  draw_vec2     (VEC2*   v, char fill, CANVAS* c);
VEC2f* draw_vec2f    (VEC2f*  v, char fill, CANVAS* c);
void   create_canvas (CANVAS* c);
void   draw_axes     (CANVAS* c, char fill);
void   print_canvas  (CANVAS* c);

void liang_barsky    (VEC2f*  v1, VEC2f*  v2, char   fill, CANVAS* c);
void draw_line       (VEC2*   v1, VEC2*   v2, char   fill, CANVAS* c);
void draw_linef      (VEC2f*  v1, VEC2f*  v2, char   fill, CANVAS* c);
void draw_plane_real (VEC2f*  v1, VEC2f*  v2, VEC2f* v3  , VEC2f*  v4, char fill, CANVAS* c);
void draw_plane      (VEC2*   v1, VEC2*   v2, VEC2*  v3  , VEC2*   v4, char fill, CANVAS* c);
void draw_planef     (VEC2f*  v1, VEC2f*  v2, VEC2f* v3  , VEC2f*  v4, char fill, CANVAS* c);

MAT33f set_mat_rot   (float al , float be , float ga);
VEC2f  vec3_project  (VEC3f vec, CANVAS* can);
float  get_rad       (float angle);

float prime(float x, VEC2f* p1, VEC2f* p2);
VEC2f intersection_xy(VEC3f* point1, VEC3f* point2);

#endif //INC_3D_TO_SCREEN_PROJECTION_H
