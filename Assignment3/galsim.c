#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "graphics.h"
#include <math.h>

typedef struct _particle
{
    double posX;
    double posY;
    double mass;
    double velX;
    double velY;
    double b;
}particle;

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
    int N = 2;
    char* filename = "input_data/ellipse_N_00020.gal";
    fp = fopen(filename, "rb");

    if (fp == NULL){
        printf("Error while opening the file.\n");
        return 1;
    }
    unsigned char buffer[8];
    double arr[6];
    particle *array = malloc(N * sizeof(particle));
    for(int i = 0; i<N; i++){

        for(int j = 0; j<6; j++){
            fread(buffer, sizeof(buffer), 1, fp);
            arr[j] = *((double*)buffer);
        }
        array[i]->posX = arr[0];
        array[i]->posY = arr[1];
        array[i]->mass = arr[2];
        array[i]->velX = arr[3];
        array[i]->velY = arr[4];
        array[i]->b = arr[5];
    }
    for(int i = 0; i<N; i++){
        printf("Read struct %f, %f, %f, %f, %f, %f \n", N, filename, nsteps, delta_t, graphics);
    }





        
    }





}