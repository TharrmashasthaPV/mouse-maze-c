#include <stdio.h>

#include "API.h"

void log(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

void logint(int* text) {
    fprintf(stderr, "%d\n", text);
    fflush(stderr);
}

void frontwallcheck(unsigned int xpos, unsigned int ypos, char ori){
    if (API_wallFront()) {
            API_setWall(xpos, ypos, ori);
        }
}

void leftwallcheck(unsigned int xpos, unsigned int ypos, char ori){
    if (API_wallLeft()) {
            API_setWall(xpos, ypos, ori);
        }
}

void rightwallcheck(unsigned int xpos, unsigned int ypos, char ori){
    if (API_wallRight()) {
            API_setWall(xpos, ypos, ori);
        }
}

int main(int argc, char* argv[]) {
    log("Running...");
    unsigned xpos = 0;
    unsigned ypos = 0;
    unsigned orient = 0;
    API_setColor(0, 0, 'G');
    API_setText(0, 0, "abc");
    char ori_to_let[4] = {'n','e','s','w'};
    while (1) {
        frontwallcheck(xpos, ypos, ori_to_let[orient]);
        leftwallcheck(xpos, ypos, ori_to_let[(orient-1)%4]);
        rightwallcheck(xpos, ypos, ori_to_let[(orient+1)%4]);
        if (!API_wallLeft()) {
            API_turnLeft();
            frontwallcheck(xpos, ypos, ori_to_let[orient]);
            leftwallcheck(xpos, ypos, ori_to_let[(orient-1)%4]);
            rightwallcheck(xpos, ypos, ori_to_let[(orient+1)%4]);
            orient = (orient-1)%4;
        }
        while (API_wallFront()) {
            API_setWall(xpos, ypos, ori_to_let[orient]);
            API_turnRight();
            orient = (orient+1)%4;
        }
        API_moveForward();
        if (orient == 0){
            ypos += 1;
        }
        if (orient == 2){
            ypos -= 1;
        }
        if (orient == 1){
            xpos += 1;
        }
        if (orient == 3){
            xpos -= 1;
        }
    }
}
