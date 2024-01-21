#pragma once

#include <stdio.h>

typedef struct matrix_rows3_cols3_int {
    int a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33;
} MAT33;

typedef struct matrix_rows3_cols3_float {
    float a11, a12, a13,
            a21, a22, a23,
            a31, a32, a33;
} MAT33f;

typedef struct matrix_rows2_cols2 {
    int a11, a12,
        a21, a22;
} MAT22; 

typedef struct matrix_rows3_cols2 {
    int a11, a12, 
        a21, a22, 
        a31, a32;
} MAT32; 

typedef struct matrix_rows2_cols3 {
    int a11, a12, a13,
        a21, a22, a23;
} MAT23; 

void mat22_print (MAT22 mat, const char* expression);
void mat33_print (MAT33 mat, const char* expression);
void mat33f_print (MAT33f mat, const char* expression);
void mat23_print (MAT23 mat, const char* expression);
void mat32_print (MAT32 mat, const char* expression);

MAT22 mat22_scale(MAT22* mat  , int    scale); 
MAT33 mat33_scale(MAT33* mat  , int    scale);
MAT33 mat33_add  (MAT33* mat1 , MAT33* mat2 );
MAT22 mat22_add  (MAT22* mat1 , MAT22* mat2 );
MAT33 mat33_sub  (MAT33* mat1 , MAT33* mat2 );
MAT22 mat22_sub  (MAT22* mat1 , MAT22* mat2 );
MAT33 mat33_mat33(MAT33* mat1 , MAT33* mat2 );
MAT22 mat22_mat22(MAT22* mat1 , MAT22* mat2 );
MAT22 mat23_mat32(MAT23* mat1 , MAT32* mat2 );
MAT33 mat32_mat23(MAT32* mat1 , MAT23* mat2 );



