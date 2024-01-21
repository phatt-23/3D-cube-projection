#include "matrix.h"

void mat22_print (MAT22 mat, const char* expression) {
    char* spaces = "   ";
    printf("> matrix 2x2 print: %s\n", expression);
    printf("%s[ %d ; %d ]\n", spaces, mat.a11, mat.a12);
    printf("%s[ %d ; %d ]\n", spaces, mat.a21, mat.a22);
}

void mat33_print (MAT33 mat, const char* expression) {
    char* spaces = "   ";
    printf("> matrix 3x3 print: %s\n", expression);
    printf("%s[ %d ; %d ; %d ]\n", spaces, mat.a11, mat.a12, mat.a13);
    printf("%s[ %d ; %d ; %d ]\n", spaces, mat.a21, mat.a22, mat.a23);
    printf("%s[ %d ; %d ; %d ]\n", spaces, mat.a31, mat.a32, mat.a33);
}

void mat33f_print (MAT33f mat, const char* expression) {
    char* spaces = "   ";
    printf("> matrix 3x3 print: %s\n", expression);
    printf("%s[ %.2f ; %.2f ; %.2f ]\n", spaces, mat.a11, mat.a12, mat.a13);
    printf("%s[ %.2f ; %.2f ; %.2f ]\n", spaces, mat.a21, mat.a22, mat.a23);
    printf("%s[ %.2f ; %.2f ; %.2f ]\n", spaces, mat.a31, mat.a32, mat.a33);
}

void mat23_print (MAT23 mat, const char* expression) {
    char* spaces = "   ";
    printf("> matrix 2x3 print: %s\n", expression);
    printf("%s[ %d ; %d ; %d ]\n", spaces, mat.a11, mat.a12, mat.a13);
    printf("%s[ %d ; %d ; %d ]\n", spaces, mat.a21, mat.a22, mat.a23);
}

void mat32_print (MAT32 mat, const char* expression) {
    char* spaces = "   ";
    printf("> matrix 3x2 print: %s\n", expression);
    printf("%s[ %d ; %d ]\n", spaces, mat.a11, mat.a12);
    printf("%s[ %d ; %d ]\n", spaces, mat.a21, mat.a22);
    printf("%s[ %d ; %d ]\n", spaces, mat.a31, mat.a32);
}

MAT22 mat22_scale(MAT22* mat, int scale) {
    return (MAT22) {
        .a11 = mat->a11 * scale,
        .a12 = mat->a12 * scale,
        .a21 = mat->a21 * scale,
        .a22 = mat->a22 * scale,
    };
} 
MAT33 mat33_scale(MAT33* mat, int scale) {
    return (MAT33) {
        .a11 = mat->a11 * scale, 
        .a12 = mat->a12 * scale, 
        .a13 = mat->a13 * scale, 
        .a21 = mat->a21 * scale, 
        .a22 = mat->a22 * scale, 
        .a23 = mat->a23 * scale, 
        .a31 = mat->a31 * scale, 
        .a32 = mat->a32 * scale, 
        .a33 = mat->a33 * scale, 
    };
}

MAT33 mat33_add(MAT33* mat1, MAT33* mat2) {
    return (MAT33) {
        .a11 = mat1->a11 + mat2->a11, 
        .a12 = mat1->a12 + mat2->a12, 
        .a13 = mat1->a13 + mat2->a13, 
        .a21 = mat1->a21 + mat2->a21, 
        .a22 = mat1->a22 + mat2->a22, 
        .a23 = mat1->a23 + mat2->a23, 
        .a31 = mat1->a31 + mat2->a31, 
        .a32 = mat1->a32 + mat2->a32, 
        .a33 = mat1->a33 + mat2->a33, 
    };
}
MAT22 mat22_add(MAT22* mat1, MAT22* mat2) {
    return (MAT22) {
        .a11 = mat1->a11 + mat2->a11, 
        .a12 = mat1->a12 + mat2->a12, 
        .a21 = mat1->a21 + mat2->a21, 
        .a22 = mat1->a22 + mat2->a22, 
    };
}
MAT33 mat33_sub(MAT33* mat1, MAT33* mat2) {
    return (MAT33) {
        .a11 = mat1->a11 - mat2->a11, 
        .a12 = mat1->a12 - mat2->a12, 
        .a13 = mat1->a13 - mat2->a13, 
        .a21 = mat1->a21 - mat2->a21, 
        .a22 = mat1->a22 - mat2->a22, 
        .a23 = mat1->a23 - mat2->a23, 
        .a31 = mat1->a31 - mat2->a31, 
        .a32 = mat1->a32 - mat2->a32, 
        .a33 = mat1->a33 - mat2->a33, 
    };
}
MAT22 mat22_sub(MAT22* mat1, MAT22* mat2) {
        return (MAT22) {
        .a11 = mat1->a11 - mat2->a11, 
        .a12 = mat1->a12 - mat2->a12, 
        .a21 = mat1->a21 - mat2->a21, 
        .a22 = mat1->a22 - mat2->a22, 
    };
}
MAT33 mat33_mat33(MAT33* mat1 , MAT33* mat2) {
    return (MAT33) {
        .a11 = (mat1->a11 * mat2->a11) + (mat1->a12 * mat2->a21) + (mat1->a13 * mat2->a31), 
        .a12 = (mat1->a11 * mat2->a12) + (mat1->a12 * mat2->a22) + (mat1->a13 * mat2->a32), 
        .a13 = (mat1->a11 * mat2->a13) + (mat1->a12 * mat2->a23) + (mat1->a13 * mat2->a33),
        .a21 = (mat1->a21 * mat2->a11) + (mat1->a22 * mat2->a21) + (mat1->a23 * mat2->a31), 
        .a22 = (mat1->a21 * mat2->a12) + (mat1->a22 * mat2->a22) + (mat1->a23 * mat2->a32), 
        .a23 = (mat1->a21 * mat2->a13) + (mat1->a22 * mat2->a23) + (mat1->a23 * mat2->a33),
        .a31 = (mat1->a31 * mat2->a11) + (mat1->a32 * mat2->a21) + (mat1->a33 * mat2->a31), 
        .a32 = (mat1->a31 * mat2->a12) + (mat1->a32 * mat2->a22) + (mat1->a33 * mat2->a32), 
        .a33 = (mat1->a31 * mat2->a13) + (mat1->a32 * mat2->a23) + (mat1->a33 * mat2->a33),
    };
}
MAT22 mat22_mat22(MAT22* mat1 , MAT22* mat2) {
    return (MAT22) {
        .a11 = (mat1->a11 * mat2->a11) + (mat1->a12 * mat2->a21), 
        .a12 = (mat1->a11 * mat2->a12) + (mat1->a12 * mat2->a22), 
        .a21 = (mat1->a21 * mat2->a11) + (mat1->a22 * mat2->a21), 
        .a22 = (mat1->a21 * mat2->a12) + (mat1->a22 * mat2->a22), 
    };
}
MAT22 mat23_mat32(MAT23* mat1 , MAT32* mat2) {
    return (MAT22) {
        .a11 = (mat1->a11 * mat2->a11) + (mat1->a12 * mat2->a21) + (mat1->a13 * mat2->a31), 
        .a21 = (mat1->a21 * mat2->a11) + (mat1->a22 * mat2->a21) + (mat1->a23 * mat2->a31), 
        .a12 = (mat1->a11 * mat2->a12) + (mat1->a12 * mat2->a22) + (mat1->a13 * mat2->a32), 
        .a22 = (mat1->a21 * mat2->a12) + (mat1->a22 * mat2->a22) + (mat1->a23 * mat2->a32), 
    };
}
MAT33 mat32_mat23(MAT32* mat1 , MAT23* mat2) {
    return (MAT33) {
        .a11 = (mat1->a11 * mat2->a11) + (mat1->a12 * mat2->a21), 
        .a12 = (mat1->a11 * mat2->a12) + (mat1->a12 * mat2->a22), 
        .a13 = (mat1->a11 * mat2->a13) + (mat1->a12 * mat2->a23),
        .a21 = (mat1->a21 * mat2->a11) + (mat1->a22 * mat2->a21), 
        .a22 = (mat1->a21 * mat2->a12) + (mat1->a22 * mat2->a22), 
        .a23 = (mat1->a21 * mat2->a13) + (mat1->a22 * mat2->a23),
        .a31 = (mat1->a31 * mat2->a11) + (mat1->a32 * mat2->a21), 
        .a32 = (mat1->a31 * mat2->a12) + (mat1->a32 * mat2->a22), 
        .a33 = (mat1->a31 * mat2->a13) + (mat1->a32 * mat2->a23),
    };
}