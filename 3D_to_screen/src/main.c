#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lin_alg/matrix_vector.h"
#include "projection.h"
#include "shapes.h"
#include "handle_input.h"

#define MAX_CUBES 10
#define MAX_STRING_LENGTH 255

CANVAS* handle_args(int argc, char** argv, CANVAS* can);
void input_cnum(char key, CANVAS* c);
void handle_input(CUBE* cubes, CANVAS* window);
void info_print(CUBE* cube, CANVAS* window);

void set_input_cubes(char* line, CUBE* cubes) {
    CUBE c;
    printf("> STRING: %s", line);
    if(!strcmp(strtok(line, " "), "CUBE")) {                              // it is a CUBE
        strcpy(c.name, strtok(NULL, " ;"));                           // name
        c.index = atoi(strtok(NULL, " ;"));                        // ID
        c.o.x   = atof(strtok(NULL, " ;"));                        // origin vector
        c.o.y   = atof(strtok(NULL, " ,"));
        c.o.z   = atof(strtok(NULL, " ,"));
        c.a.x   = atof(strtok(NULL, " ;"));                        // initial angles
        c.a.y   = atof(strtok(NULL, " ,"));
        c.a.z   = atof(strtok(NULL, " ,"));
        c.ai.x  = atof(strtok(NULL, " ;"));                        // rotation speed
        c.ai.y  = atof(strtok(NULL, " ,"));
        c.ai.z  = atof(strtok(NULL, " ,"));
        c.s     = atof(strtok(NULL, " ;"));                          // side length
        c.fill  = strtok(NULL, " ;")[0];                             // filler char
        printf(" >> Extract: %s ; %d ; %.2f, %.2f, %.2f ; %.2f, %.2f, %.2f ; %.2f, %.2f, %.2f ; %.2f ; %c\n",
               c.name,c.index,c.o.x,c.o.y,c.o.z,c.a.x,c.a.y,c.a.z,c.ai.x,c.ai.y,c.ai.z,c.s,c.fill);
        puts("> Initialising a cube");
        cubes[c.index] = set_cube(c.name,c.index,c.o.x,c.o.y,c.o.z,c.a.x,
                                  c.a.y,c.a.z,c.ai.x,c.ai.y,c.ai.z,c.s,c.fill);
    }
}

void read_in(CANVAS* c, CUBE* cubes) {
    char text_line[MAX_STRING_LENGTH] = {};
    printf("> OPENING FILE << %s\n", c->fin);
    FILE* file_in = fopen(c->fin, "r");
    tbreak();
    while(strncmp(text_line, "end", 3) != 0) {
        fgets(text_line, sizeof(text_line), file_in);
        set_input_cubes(text_line, cubes);
        tbreak();
    }
    printf("> CLOSING FILE %s\n", c->fin);
    fclose(file_in);
    tbreak();
}

void clean_up(CANVAS* c) {
    printf("> EXITING\n");
    clear_screen();
    free(c->canvas);
}

int main(int argc, char** argv) {
    // Initialise Everything
    CANVAS window;
    CUBE cubes[MAX_CUBES];
    for(int i=0; i<MAX_CUBES; i++) {
        cubes[i] = set_cube("no name", 12345 + i, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '*');
    }
    handle_args(argc, argv, &window);
    read_in(&window, cubes);
    create_canvas(&window);
    // Main Loop
    while(window.running) {
        // Handle Input
        handle_input(cubes, &window);
        // Update
        clear_canvas(&window);
        for(int i=0; i<MAX_CUBES; i++) {
            draw_cube(&cubes[i], &window);
        }
        // Render
        clear_screen();
        print_canvas(&window);
        info_print(&cubes[window.ccurrent], &window);


        usleep(100*window.slowdown);
    }
    // Clean Up
    clean_up(&window);
    return 0;
}

void input_cnum(char key, CANVAS* c) {
    for(int i=0; i<MAX_CUBES; i++) {
        if(key == '0' + i) {
            c->ccurrent = i;
        }
    }
}

void handle_input(CUBE* cubes, CANVAS* window) {
    if(kbhit()) {
        char key = getchar();
        input_conf(key, &window->running, &window->slowdown);
        input_canv(key, window);
        input_cube(key, &cubes[window->ccurrent]);
        input_cnum(key, window);
    }
}

void info_print(CUBE* cube, CANVAS* window) {
    printf("> window.current_cube = %d\n", window->ccurrent);
    printf("> SELECTED CUBE NAME = %s INDEX = %d                          \n", cube->name, cube->index);
    printf("> CUBE IS ROTATED BY ---- x(%.2f) y(%.2f) z(%.2f) degs        \n", cube->a.z, cube->a.y, cube->a.x);
    printf(">   CUBE COORDINATES ---- x(%.2f) y(%.2f) z(%.2f) units       \n", cube->o.x, cube->o.y, cube->o.z);
    printf("> [U][I][O] rotate ------ x(%.2f) y(%.2f) z(%.2f) degs/frame  \n", cube->ai.z, cube->ai.y, cube->ai.x);
    printf("> [J][K][L]                                                   \n");
    printf(">    [W][S] slow down --- %d times                            \n", window->slowdown);
    printf(">    [E][D] distance ---- %.2f units                          \n", window->distance);
    printf(">    [R][F] fov --------- %.2f degs                           \n", window->fov);
    printf(">       [Q] to exit the loop                                  \n");
    for (int i = 0; i < 8; i++) {
        VEC3f v = mat33_vec3f(&cube->mat_rot, &cube->v[i]);
        v.x += cube->o.x;
        v.y += cube->o.y;
        v.z += cube->o.z + window->distance;
        printf("> VERTEX %c\tX: %f\tY: %f\tZ: %f\n", 'A' + i, v.x, v.y, v.z);
    }
}

CANVAS* handle_args(int argc, char** argv, CANVAS* can) {
    for(int i=0; i < argc; i++) {
        if (!strcmp(argv[i], "-wh")) {
            can->width = atoi(argv[i + 1]);
            can->height = atoi(argv[i + 2]);
        } else if (!strcmp(argv[i], "-fill")) {
            can->filling_char = argv[i + 1][0];
        } else if (!strcmp(argv[i], "-dist")) {
            can->distance = atof(argv[i + 1]);
        } else if (!strcmp(argv[i], "-fov")) {
            can->fov = atof(argv[i + 1]);
        } else if (!strcmp(argv[i], "-fin")) {
            strcpy(can->fin, argv[i + 1]);
        }
    }
    can->running = true;
    can->slowdown = 100;
    return can;
}



