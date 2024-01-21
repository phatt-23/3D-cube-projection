#pragma once 

#include "keyboard.h"
#include "projection.h"
#include "shapes.h"

void tbreak(void);
void input_cube(char key, CUBE* cube);
void input_conf(char key, bool* run, int* sd);
void input_canv(char key, CANVAS* can);
