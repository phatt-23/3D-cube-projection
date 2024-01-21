#include "matrix_vector.h"

VEC2 mat22_vec2  (MAT22* mat, VEC2* vec) {
    return (VEC2) {
        .x = (vec->x * mat->a11) + (vec->y * mat->a12),
        .y = (vec->x * mat->a21) + (vec->y * mat->a22),
    };  
}
VEC3 mat33_vec3  (MAT33* mat, VEC3* vec) {
    return (VEC3) {
        .x = (vec->x * mat->a11) + (vec->y * mat->a12) + (vec->z * mat->a13),
        .y = (vec->x * mat->a21) + (vec->y * mat->a22) + (vec->z * mat->a23),
        .z = (vec->x * mat->a31) + (vec->y * mat->a32) + (vec->z * mat->a33),
    };  
}
VEC3f mat33_vec3f  (MAT33f* mat, VEC3f* vec) {
    return (VEC3f) {
            .x = (vec->x * mat->a11) + (vec->y * mat->a12) + (vec->z * mat->a13),
            .y = (vec->x * mat->a21) + (vec->y * mat->a22) + (vec->z * mat->a23),
            .z = (vec->x * mat->a31) + (vec->y * mat->a32) + (vec->z * mat->a33),
    };
}
VEC2 mat23_vec3  (MAT23* mat, VEC3* vec) {
    return (VEC2) { 
        .x = (vec->x * mat->a11) + (vec->y * mat->a12) + (vec->z * mat->a13),
        .y = (vec->x * mat->a21) + (vec->y * mat->a22) + (vec->z * mat->a23),
    };
}
VEC3 mat32_vec2  (MAT32* mat, VEC2* vec) {
    return (VEC3) {
        .x = (vec->x * mat->a11) + (vec->y * mat->a12), 
        .y = (vec->x * mat->a21) + (vec->y * mat->a22), 
        .z = (vec->x * mat->a31) + (vec->y * mat->a32),
    };
}
