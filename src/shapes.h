#ifndef INC_3D_TO_SCREEN_SHAPES_H
#define INC_3D_TO_SCREEN_SHAPES_H

#include "projection.h"

typedef struct cube {
    char name[20];
    VEC3f v[8];     // vertexes
    VEC2f proj[8];  // projected vertexes
    VEC3f o,        // origin coord
          a,        // rot angles
          ai;       // rot speed
    float s;        // size length
    char fill;      // filler
    MAT33f mat_rot; // rotation matrix
    int index;      // unique identifier
} CUBE;

CUBE set_cube(const char* name, int index,
              float ox , float oy , float oz,
              float ax , float ay , float az,
              float aix, float aiy, float aiz,
              float size_length, char fill);

void draw_cube(CUBE* cube, CANVAS* can);


#endif //INC_3D_TO_SCREEN_SHAPES_H
