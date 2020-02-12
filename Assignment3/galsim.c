#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
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

const float circleRadius=0.025, circleColor=0;
const int windowWidth=800;

void keep_within_box(double* xA, double* yA) {
  if(*xA > 1)
    *xA = 0;
  if(*yA > 1)
    *yA = 0;
}

int main(int argc, char* argv[]){
  //printf("%d", argc);
  if (argc != 6){
      printf("Wrong number of input arguments\n");
      return 1;
  }
  int N = atoi(argv[1]);
  char* filename = argv[2];
  int n_steps = atoi(argv[3]);
  int deltaT = atof(argv[4]);
  int graphics = atoi(argv[5]);

  printf("Command line arguments given: %d, %s, %d, %d, %d \n", N, filename, n_steps, deltaT, graphics);
  
//input_data/sun_and_planets_N_3.gal
    FILE *fp;
    //int N = 10;
    //char* filename = "input_data/ellipse_N_00010.gal";
    //char* filename = "test.gal";
    fp = fopen(filename, "rb");
    const float e0 = 0.001;
    const double G = 100 / N;
    double delta_t = pow(10, deltaT);
    //const int n_steps = 200;
  printf("\n %d",123);
    // graphics
    float L=1, W=1;
    InitializeGraphics(argv[0],windowWidth,windowWidth);
    SetCAxes(0,1);
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
        array[i].posX = arr[0];
        array[i].posY = arr[1];
        array[i].mass = arr[2];
        array[i].velX = arr[3];
        array[i].velY = arr[4];
        array[i].b = arr[5];
    }
    /*
    for(int i = 0; i<N; i++){
        printf("Read struct %f, %f, %f, %f, %f. %f \n", array[i].posX, array[i].posY, array[i].mass, array[i].velX, array[i].velY, array[i].b);
    }*/
    particle *new_array = malloc(N * sizeof(particle));
    printf("\n %d",123);
    for (int k = 0; k < n_steps; k++) {
      ClearScreen();
      for (int i = 0; i < N; i++) {
        keep_within_box(&array[i].posX, &array[i].posY);
        DrawCircle(array[i].posX, array[i].posY, L, W, circleRadius, circleColor);
        Refresh();
        printf("\n %d",i);
        usleep(3000);
        double Fix = 0;
        double Fiy = 0;
        double aix, aiy;
        double uix, uiy;
        double pix, piy;
        double massi = array[i].mass;
        for (int j = 0;  j < N; j++) {
          double Fjx = 0, Fjy = 0;
          if (j == i) {} /* skip iteration */
          else {
            double x_dist = array[i].posX - array[j].posX;
            double y_dist = array[i].posY - array[j].posY;
            double r2 = pow(x_dist, 2) + pow(y_dist, 2);
            double denom = pow((sqrt(r2)+e0), 3);
            double massj = array[j].mass;
            Fjx = massj * x_dist / denom; 
            Fjy = massj * y_dist / denom;
          }
          Fix += Fjx;
          Fiy += Fjy;
        }
        Fix = -G * massi * Fix;
        Fiy = -G * massi * Fiy;
        aix = Fix / massi;
        aiy = Fiy / massi;
        uix = array[i].velX + delta_t * aix;
        uiy = array[i].velY + delta_t * aiy;
        pix = array[i].posX + delta_t * uix;
        piy = array[i].posY + delta_t * uiy;
        // update for next time step
        new_array[i].velX = uix;
        new_array[i].velY = uiy;
        new_array[i].posX = pix;
        new_array[i].posY = piy;
        new_array[i].mass = array[i].mass;
        new_array[i].b = array[i].b;
      }
      array = new_array;
    }
    
  
    printf("\n");
    /*
    for(int i = 0; i<N; i++){
        printf("Read struct %f, %f, %f, %f, %f. %f \n", new_array[i].posX, new_array[i].posY, new_array[i].mass, new_array[i].velX, new_array[i].velY, new_array[i].b);
    }
    */

    FILE *fp2;
    fp2 = fopen("test.gal", "wb");
    for(int i = 0; i<N; i++){
      fwrite(&new_array[i].posX, sizeof(double), 1, fp2);
      fwrite(&new_array[i].posY, sizeof(double), 1, fp2);
      fwrite(&new_array[i].mass, sizeof(double), 1, fp2);
      fwrite(&new_array[i].velX, sizeof(double), 1, fp2);
      fwrite(&new_array[i].velY, sizeof(double), 1, fp2);
      fwrite(&new_array[i].b, sizeof(double), 1, fp2);
    }


  FlushDisplay();
  CloseDisplay();

  return 0;
}