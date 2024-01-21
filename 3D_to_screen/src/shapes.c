#include "shapes.h"

//       E                (F)
//
//           (A)       B
//
//
//            D       (C)
//
//       (H)               G

typedef enum { A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7 } VERTECES;
typedef enum { OUTSIDE = 0, P1_OUT = 1, P2_OUT = 2, INSIDE = 3 } LOCATION_2VECS;

CUBE set_cube(const char* name, int index, float ox , float oy , float oz, float ax , float ay , float az, float aix, float aiy, float aiz, float size_length, char fill)
{
    float half_size = size_length/2;
    CUBE n_cube = {
            .v = {
                    {-(half_size), (half_size), (half_size)},
                    { (half_size), (half_size), (half_size)},
                    { (half_size),-(half_size), (half_size)},
                    {-(half_size),-(half_size), (half_size)},
                    {-(half_size), (half_size),-(half_size)},
                    { (half_size), (half_size),-(half_size)},
                    { (half_size),-(half_size),-(half_size)},
                    {-(half_size),-(half_size),-(half_size)},
            },
            .o    = { ox, oy, oz },
            .a    = { ax, ay, az },
            .ai   = { aix, aiy, aiz },
            .s    = size_length,
            .fill = fill,
            .index = index,
    };
    sprintf(n_cube.name, "%s", name);
    return n_cube;
}

// 0 -- if both are behind camera
// 1 -- if p1 is behind the camera but p2 isn't
// 2 -- if p2 is behind the camera but p1 isn't
// 3 -- if non are behind the camera
int check_loc(VERTECES p1, VERTECES p2, VEC3f* vertexes) {
    if(vertexes[p1].z < 0 && vertexes[p2].z < 0) return OUTSIDE;
    if(vertexes[p1].z < 0 && vertexes[p2].z >= 0) return P1_OUT;
    if(vertexes[p1].z >= 0 && vertexes[p2].z < 0) return P2_OUT;
    return INSIDE;
}
int check_z_clip(VEC3f p1, VEC3f p2) {
    if(p1.z < 0 && p2.z < 0) return OUTSIDE;
    if(p1.z < 0 && p2.z >= 0) return P1_OUT;
    if(p1.z >= 0 && p2.z < 0) return P2_OUT;
    return INSIDE;
}
void connect_z_clip(VEC3f* a, VEC3f* b, char fill, CANVAS* can) {
    // PROBABLY UNSAFE
    VEC2f tt = {0,0};
    VEC3f ttt = {0,0,0};
    VEC3f v[2] = { *a, *b };
    VEC2f p[2];
    p[0] = vec3_project(*a, can);
    p[1] = vec3_project(*b, can);
    switch(check_z_clip(*a,*b)) {
        case INSIDE:
            liang_barsky(&p[0], &p[1], fill, can);
            break;
        case P1_OUT:
            tt = intersection_xy(&v[0], &v[1]);
            ttt.x = tt.x;
            ttt.y = tt.y;
            tt = vec3_project(ttt, can);
            liang_barsky(&tt, &p[1], fill, can);
            break;
        case P2_OUT:
            tt = intersection_xy(&v[0], &v[1]);
            ttt.x = tt.x;
            ttt.y = tt.y;
            tt = vec3_project(ttt, can);
            liang_barsky(&tt, &p[0], fill, can);
            break;
        default: break;
    }
}

void connect_points(VERTECES a, VERTECES b, CUBE* cube, VEC3f* v, CANVAS* can) {
    VEC2f tt = {0,0};
    VEC3f ttt = {0,0,0};
    switch(check_loc(a, b, v)) {
        case INSIDE:
            liang_barsky(&cube->proj[a], &cube->proj[b],cube->fill,can);
            break;
        case P1_OUT:
            tt = intersection_xy(&v[a], &v[b]);
            ttt.x = tt.x;
            ttt.y = tt.y;
            tt = vec3_project(ttt, can);
            liang_barsky(&tt, &cube->proj[b],cube->fill,can);
            break;
        case P2_OUT:
            tt = intersection_xy(&v[a], &v[b]);
            ttt.x = tt.x;
            ttt.y = tt.y;
            tt = vec3_project(ttt, can);
            liang_barsky(&tt, &cube->proj[a],cube->fill,can);
            break;
        default: break;
    }
}

void cube_update(CUBE* cube) {
    cube->a.x += cube->ai.x;
    cube->a.y += cube->ai.y;
    cube->a.z += cube->ai.z;
    while(cube->a.x >= 360) cube->a.x -= 360;
    while(cube->a.y >= 360) cube->a.y -= 360;
    while(cube->a.z >= 360) cube->a.z -= 360;
    while(cube->a.x <= -360) cube->a.x += 360;
    while(cube->a.y <= -360) cube->a.y += 360;
    while(cube->a.z <= -360) cube->a.z += 360;
}

void cube_setup(CUBE* cube, VEC3f* v, CANVAS* can) {
    cube->mat_rot = set_mat_rot(get_rad(cube->a.x), get_rad(cube->a.y), get_rad(cube->a.z));
    for (int i = 0; i < 8; i++) {
        v[i] = mat33_vec3f(&cube->mat_rot, &cube->v[i]);
        v[i].x += cube->o.x;
        v[i].y += cube->o.y;
        v[i].z += cube->o.z + can->distance;
        cube->proj[i] = vec3_project(v[i], can);
    }
}

void cube_connect(CUBE* cube, VEC3f* v, CANVAS* can) {
    static VEC3f origin;
    static VEC2f vv;
    for(int i=0; i<4; i++) {
        connect_points(A+i, E+i, cube, v, can);
    }
    for(int i=0; i<2; i++) {
        connect_points(A+i*2, B+i*2, cube, v, can);
        connect_points(E+i*2, F+i*2, cube, v, can);
        connect_points(B+i*4, C+i*4, cube, v, can);
        connect_points(A+i*4, D+i*4, cube, v, can);
    }
    // DRAW CORNER LETTERS AND CENTER
    origin = cube->o;
    origin.z += can->distance;
    VEC3f nul = {0,0,can->distance};
    char filling = 'o';
    if(cube->o.z <= 0) filling = '%';
    connect_z_clip(&origin, &nul, filling, can);
    if(origin.z > 0) {
        vv = vec3_project(origin, can);
        draw_vec2f(&vv, '0' + cube->index, can);
    }
    for(int i=0; i<8; i++) {
        if(v[i].z > 0) {
            draw_vec2f(&cube->proj[i], 'A' + i, can);
        }
    }
}

void draw_cube(CUBE* cube, CANVAS* can) {
    if(cube->index < 0 || cube->index > 9) return;
    static VEC3f v[8];
    cube_setup(cube, v, can);
    cube_connect(cube, v, can);
    cube_update(cube);

}

