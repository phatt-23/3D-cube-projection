#include "handle_input.h"

void tbreak(void) {
    puts(">> Press Enter To Continue <<");
    while(getchar() != '\n');
}

void input_cube(char key, CUBE* cube) {
    if(cube->index == 0) return;
    switch(key) { 
        case 'j':   // manipulation of rotation
            cube->ai.z += 0.1;
            break;
        case 'k':
            cube->ai.y += 0.1;
            break;
        case 'l':
            cube->ai.x += 0.1;
            break;
        case 'i':
            cube->ai.z -= 0.1;
            break;
        case 'o':
            cube->ai.y -= 0.1;
            break;
        case 'p':
            cube->ai.x -= 0.1;
            break;
        case 'u':   // stop rotation
            cube->ai.x = 0;
            cube->ai.y = 0;
            cube->ai.z = 0;
            break;
        case 'z':   // reset angles
            cube->a.x = 0;
            cube->a.y = 0;
            cube->a.z = 0;
            break;
        case 'm':   // set origin
            cube->o.x += 2;
            break;
        case 'b': 
            cube->o.y += 2;
            break;
        case 'g':
            cube->o.z += 2;
            break;
        case 'v':  
            cube->o.x -= 2;
            break;
        case 'n': 
            cube->o.y -= 2;
            break;
        case 'h':
            cube->o.z -= 2;
            break;
        default: break;
    }
}

void input_conf(char key, bool* run, int* sd) {
    switch(key) {
        case 'q':   // quiting loop
            *run = false;
            break;
        case 'w':   // slowing down
            *sd += 100;
            break;
        case 's':
            if(*sd > 0) *sd -= 100;
            break;
        default: break;
    }
}
void input_canv(char key, CANVAS* can) {
    switch(key) {
        case 'e':   // alter distance from camera
            if(can->distance < 5)
                can->distance += 0.5;
            else
                can->distance += 5;
            break;
        case 'd':
            if(can->distance > 5) 
                can->distance -= 5;
            else if(can->distance > 0.5)
                can->distance -= 0.5;

            break;
        case 'r':   // alter field of view
            if(can->fov < 5)
                can->fov += 0.5;
            else
                can->fov += 5;
            break;
        case 'f':
            if(can->fov > 5) 
                can->fov -= 5;
            else if(can->fov > 0)
                can->fov -= 0.5;
            break;
        default: break;
    }
}
