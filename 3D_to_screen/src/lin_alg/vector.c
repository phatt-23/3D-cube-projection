#include "vector.h"

void vec2_print(VEC2 vec, const char* expression) {
    char* spaces = "   ";
    printf("> vec2 print: %s\n", expression);
    printf("%s[ %d ]\n", spaces, vec.x);
    printf("%s[ %d ]\n", spaces, vec.y);
}
void vec2f_print(VEC2f vec, const char* expression) {
    char* spaces = "   ";
    printf("> vec2f print: %s\n", expression);
    printf("%s[ %.2f ]\n", spaces, vec.x);
    printf("%s[ %.2f ]\n", spaces, vec.y);
}

void vec3_print(VEC3 vec, const char* expression) {
    char* spaces = "   ";
    printf("> vec2 print: %s\n", expression);
    printf("%s[ %d ]\n", spaces, vec.x);
    printf("%s[ %d ]\n", spaces, vec.y);
    printf("%s[ %d ]\n", spaces, vec.z);
}
void vec3f_print(VEC3f vec, const char* expression) {
    char* spaces = "   ";
    printf("> vec3f print: %s\n", expression);
    printf("%s[ %.2f ]\n", spaces, vec.x);
    printf("%s[ %.2f ]\n", spaces, vec.y);
    printf("%s[ %.2f ]\n", spaces, vec.z);
}

VEC2 vec2_scale  (VEC2* vec, int scale) {
    return (VEC2) {
        .x = vec->x * scale,
        .y = vec->y * scale
    };
}
VEC3 vec3_scale  (VEC3* vec, int scale) {
    return (VEC3) {
        .x = vec->x * scale,
        .y = vec->y * scale,
        .z = vec->z * scale,
    };
}
VEC3f vec3f_scale  (VEC3f* vec, float scale) {
    return (VEC3f) {
            .x = vec->x * scale,
            .y = vec->y * scale,
            .z = vec->z * scale,
    };
}

VEC2 vec2_add(VEC2* vec1, VEC2* vec2) {
    return (VEC2) {
        .x = vec1->x + vec2->x,
        .y = vec1->y + vec2->y
    };
}
VEC3 vec3_add(VEC3* vec1, VEC3* vec2) {
    return (VEC3) {
        .x = vec1->x + vec2->x,
        .y = vec1->y + vec2->y,
        .z = vec1->z + vec2->z
    };
}

VEC2 vec2_sub  (VEC2* vec1, VEC2* vec2) {
    return (VEC2) {
        .x = vec1->x - vec2->x,
        .y = vec1->y - vec2->y
    };
} 
VEC3 vec3_sub  (VEC3* vec1, VEC3* vec2) {
    return (VEC3) {
        .x = vec1->x - vec2->x,
        .y = vec1->y - vec2->y,
        .z = vec1->z - vec2->z
    };
}
