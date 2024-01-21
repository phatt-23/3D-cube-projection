#include "projection.h"
#include <string.h>
#include <math.h>

bool debug = 0;
static const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

VEC2* draw_vec2(VEC2* v, char fill, CANVAS* c) {
    VEC3 index = {
        .x = (v->x + c->width  / 2)            ,
        .y = (v->y + c->height / 2) * c->width ,
        .z = index.x + index.y,
    };
    if(index.z >= c->width * c->height) {
        vec3_print(index, "");
        printf("    ^ this is out of bounds, here is the last frame:\n");
    }
    c->canvas[index.z] = fill;
    return v;
}

VEC2f* draw_vec2f(VEC2f* v, char fill, CANVAS* c) {
    const float width_half  = floorf(c->width/2),
                height_half = floorf(c->height/2);
    if(v->x >= -width_half  && v->x <= width_half && 
       v->y >= -height_half && v->y <= height_half) {
        int index = ((int)v->x + width_half) + ((int)v->y + height_half) * c->width;
        if(index < c->width * c->height && index > 0)
            c->canvas[index] = fill;
    }
    return v;
}

void create_canvas(CANVAS* c) {
    c->canvas = calloc(sizeof(int), c->width * c->height);
    for(int i = 0; i < c->width * c->height; i++) {
        c->canvas[i] = c->filling_char;
    }
}

void draw_axes(CANVAS* c, char fill) {
    VEC2 origin = {
        c->height/2 * c->width,
        c->width/2,
    };
    if(debug) printf("origin %d %d\n", origin.x, origin.y);
    for(int x=0; x <c->width; x++) {
        c->canvas[origin.x + x] = fill;
    }
    for(int y=0; y<c->height; y++) {
        c->canvas[origin.y + c->width*y] = fill;
    }
}

void print_canvas(CANVAS* c) {
    for(int i=c->height; i>=0; i--) {
        for(int j=0; j<c->width; j++) {
            printf("%c", c->canvas[i*c->width + j]);
        }
        printf("\n");
    }
}

void draw_line(VEC2* v1, VEC2* v2, char fill, CANVAS* c)  {
    int dx    = v2->x - v1->x,
            dy    = v2->y - v1->y,
            steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float x_increment = (float)dx / steps,
            y_increment = (float)dy / steps,
            x = v1->x,
            y = v1->y;

    for (int i = 0; i <= steps; i++) {
        VEC2 vec = { x , y };
        draw_vec2(&vec, fill, c);
        x += x_increment;
        y += y_increment;
    }
}



// return a pair of VEC2f that are clipped
void liang_barsky(VEC2f* v1, VEC2f* v2, char fill, CANVAS* c) {
    float xmin = -c->width/2, xmax = -xmin, ymin = -c->height, ymax = -ymin;
    float dx = v2->x - v1->x;
    float dy = v2->y - v1->y;
    float p[4] = { -dx, dx, -dy, dy };
    float q[4] = { v1->x - xmin, xmax - v1->x, v1->y - ymin, ymax - v1->y };
    float t1 = 0, t2 = 1;
    for (int i = 0; i < 4; ++i) {
        if (p[i] == 0) {
            if (q[i] < 0) {
                printf("Line is parallel to clipping edge and outside\n");
                return;
            }
        } else {
            float r = q[i] / p[i];
            if (p[i] < 0 && r > t1) {
                t1 = r;
            } else if (p[i] > 0 && r < t2) {
                t2 = r;
            }
        }
    }
    if (t1 > t2) {
        printf("Line is outside the clipping window\n");
        return;
    } else {
        VEC2f vecs[2] = { { v1->x + t1 * dx , v1->y + t1 * dy },
                          { v1->x + t2 * dx , v1->y + t2 * dy } };
        draw_linef(&vecs[0], &vecs[1], fill, c);
    }
}


void draw_linef(VEC2f* v1, VEC2f* v2, char fill, CANVAS* c) {
    VEC2f d = { v2->x - v1->x, v2->y - v1->y };
    float steps = (fabs(d.x) > fabs(d.y)) ? fabs(d.x) : fabs(d.y);
    VEC2f increment = { d.x / steps, d.y / steps };
    VEC2f pos = { v1->x, v1->y };
    for (int i = 0; i <= steps; i++) {
        draw_vec2f(&pos, fill, c);
        pos.x += increment.x;
        pos.y += increment.y;
    }
}

void draw_plane_real(VEC2f* v1, VEC2f* v2, VEC2f* v3, VEC2f* v4, char fill, CANVAS* c) {
    float   dx1     = v2->x - v1->x,
            dy1     = v2->y - v1->y,
            dx2     = v4->x - v3->x,
            dy2     = v4->y - v3->y,
            steps1  = (fabs(dx1) > fabs(dy1)) ? fabs(dx1) : fabs(dy1),
            steps2  = (fabs(dx2) > fabs(dy2)) ? fabs(dx2) : fabs(dy2);

    float x_incre1 = (float)dx1 / steps1,
            y_incre1 = (float)dy1 / steps1,
            x_incre2 = (float)dx2 / steps2,
            y_incre2 = (float)dy2 / steps2;

    VEC2f vec1 = { v1->x , v1->y },
          vec2 = { v3->x , v3->y };

    for (float i = 0; i < steps1; i++) {
        draw_vec2f(&vec1, fill, c);
        vec1.x += x_incre1;
        vec1.y += y_incre1;
        for (float j = 0; j < steps2; j++) {
            draw_vec2f(&vec2, fill, c);
            draw_linef(&vec1, &vec2, fill, c);
            vec2.x += x_incre2;
            vec2.y += y_incre2;
        }
        vec2.x = v3->x;
        vec2.y = v3->y;
    }
}

void draw_plane_real_int(VEC2* v1, VEC2* v2, VEC2* v3, VEC2* v4, char fill, CANVAS* c) {
    float   dx1     = v2->x - v1->x,
            dy1     = v2->y - v1->y,
            dx2     = v4->x - v3->x,
            dy2     = v4->y - v3->y,
            steps1  = (fabs(dx1) > fabs(dy1)) ? fabs(dx1) : fabs(dy1),
            steps2  = (fabs(dx2) > fabs(dy2)) ? fabs(dx2) : fabs(dy2);

    float x_incre1 = (float)dx1 / steps1,
            y_incre1 = (float)dy1 / steps1,
            x_incre2 = (float)dx2 / steps2,
            y_incre2 = (float)dy2 / steps2;

    VEC2f vec1 = { v1->x , v1->y },
            vec2 = { v3->x , v3->y };

    for (float i = 0; i < steps1; i++) {
        draw_vec2f(&vec1, fill, c);
        vec1.x += x_incre1;
        vec1.y += y_incre1;
        for (float j = 0; j < steps2; j++) {
            draw_vec2f(&vec2, fill, c);
            draw_linef(&vec1, &vec2, fill, c);
            vec2.x += x_incre2;
            vec2.y += y_incre2;
        }
        vec2.x = v3->x;
        vec2.y = v3->y;
    }
}

void draw_plane(VEC2* v1, VEC2* v2, VEC2* v3, VEC2* v4, char fill, CANVAS* c) {
    draw_line(v1, v2, fill, c);
    draw_line(v1, v3, fill, c);
    draw_line(v1, v4, fill, c);
    draw_line(v2, v3, fill, c);
    draw_line(v2, v4, fill, c);
    draw_line(v3, v4, fill, c);
    VEC2 vecs[4] = { *v1, *v2, *v3, *v4 };
    VEC2 vecs_sort[4] = {
            {  c->width / 2 ,  0             },
            { -c->width / 2 ,  0             },
            {  0            , -c->height /2  },
            {  0            ,  c->height  /2 },
    };
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[0].x > vecs[i].x)
            vecs_sort[0] = vecs[i];
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[1].x < vecs[i].x) {
            vecs_sort[1] = vecs[i];
        }
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[2].y < vecs[i].y) {
            vecs_sort[2] = vecs[i];
        }
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[3].y > vecs[i].y) {
            vecs_sort[3] = vecs[i];
        }
    }
    for(int i = 0; i < 24; i++) {
        draw_plane_real_int(
                &vecs_sort[ (i)   % 3 ],
                &vecs_sort[ (i+1) % 3 ],
                &vecs_sort[ (i+2) % 3 ],
                &vecs_sort[ (i+3) % 3 ],
                fill, c
        );
    }
}

void draw_planef(VEC2f* v1, VEC2f* v2, VEC2f* v3, VEC2f* v4, char fill, CANVAS* c) {
    draw_linef(v1, v2, fill, c);
    draw_linef(v1, v3, fill, c);
    draw_linef(v1, v4, fill, c);
    draw_linef(v2, v3, fill, c);
    draw_linef(v2, v4, fill, c);
    draw_linef(v3, v4, fill, c);
    VEC2f vecs[4] = { *v1, *v2, *v3, *v4 };
    VEC2f vecs_sort[4] = {
            {  c->width / 2 ,  0             },
            { -c->width / 2 ,  0             },
            {  0            , -c->height /2  },
            {  0            ,  c->height  /2 },
    };
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[0].x > vecs[i].x)
            vecs_sort[0] = vecs[i];
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[1].x < vecs[i].x) {
            vecs_sort[1] = vecs[i];
        }
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[2].y < vecs[i].y) {
            vecs_sort[2] = vecs[i];
        }
    }
    for(int i = 0 ; i < 4 ; i++) {
        if(vecs_sort[3].y > vecs[i].y) {
            vecs_sort[3] = vecs[i];
        }
    }
    draw_plane_real(
            &vecs_sort[0],
            &vecs_sort[3],
            &vecs_sort[2],
            &vecs_sort[1],
            fill, c
    );
}

void clear_canvas(CANVAS* c) {
    memset(c->canvas, '.' , c->width * c->height);
}

void clear_screen() {
    printf("%s", CLEAR_SCREEN_ANSI);
}

MAT33f set_mat_rot (float al, float be, float ga) {
    const float sin_al = sin(al),
                sin_be = sin(be),
                sin_ga = sin(ga),
                cos_al = cos(al),
                cos_be = cos(be),
                cos_ga = cos(ga),
         cos_al_sin_be = cos_al*sin_be,
         sin_al_sin_be = sin_al*sin_be;

    return (MAT33f) {
            cos_al*cos_be , cos_al_sin_be*sin_ga - sin_al*cos_ga , cos_al_sin_be*cos_ga + sin_al*sin_ga ,
            sin_al*cos_be , sin_al_sin_be*sin_ga + cos_al*cos_ga , sin_al_sin_be*cos_ga - cos_al*sin_ga ,
            -sin_be       , cos_be*sin_ga                        , cos_be*cos_ga                        ,
    };
}

VEC2f vec3_project(VEC3f vec, CANVAS* can) {
    float d_half = can->distance/2;
    float f = 1.0 / tan(get_rad(can->fov) / 2);
    if(vec.z == 0) {
        vec.z = 0.00001;
    }
    return (VEC2f) {
        (f * vec.x) / vec.z * d_half,
        (f * vec.y) / vec.z * d_half,
    };
}

float get_rad(float angle) {
    static const float degs = 360.0;
    while(angle >= degs) angle -= degs;
    return angle * M_PI / 180.0;
}

float prime(float x, VEC2f* p1, VEC2f* p2) {
    float dx = (p1->x - p2->x);
    float dy = (p1->y - p2->y);
    printf("dx: %f\tdy: %f\tslope: %f", dx, dy, dy/dx);
    return x * ( dy / dx ) + p1->y;
}

VEC2f intersection_xy(VEC3f* point1, VEC3f* point2) {
    VEC3f p1, p2;
    if(point1->z < 0) {
        p1 = *point1;
        p2 = *point2;
    } else {
        p2 = *point1;
        p1 = *point2;
    }
    VEC2f x_vec1 = { p1.z, p1.x };
    VEC2f x_vec2 = { p2.z, p2.x };
    VEC2f y_vec1 = { p1.z, p1.y };
    VEC2f y_vec2 = { p2.z, p2.y };
    float input = fabs(p1.z);
    return (VEC2f) {
            prime(input, &x_vec1, &x_vec2),
            prime(input, &y_vec1, &y_vec2),
    };
}
