#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "graphics.h"
#include <math.h>

struct particle
{
    double posX;
    double posY;
    double mass;
    double velX;
    double velY;
    double b;
};

int main(int argc, char* argv[]){
    /*
    printf("%d", argc);
    if (argc != 6){
        printf("Wrong number of input arguments\n");
        return 1;
    }
    int N = atoi(argv[1]);
    char* filename = argv[2];
    int nsteps = atoi(argv[3]);
    double delta_t = atof(argv[4]);
    int graphics = atoi(argv[5]);

    printf("Command line arguments given: %d, %s, %d, %f, %d \n", N, filename, nsteps, delta_t, graphics);
    */

    FILE *fp;

    char* filename = "input_data/ellipse_N_00020.gal";
    fp = fopen(filename, "rb");

    if (fp == NULL){
        printf("Error while opening the file.\n");
        return 1;
    }
    double a;
    unsigned char buffer[8];
    double arr[6];
    for(int i = 0; i<6; i++){
        fread(buffer, sizeof(buffer), 1, fp);
        arr[i] = *((double*)buffer);
    }
    for(int i = 0; i<6; i++){
        printf("%f\n", arr[i]);
    }





}