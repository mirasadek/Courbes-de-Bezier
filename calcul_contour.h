#include<stdio.h> 
#include<stdlib.h> 
#include "image.h"
#include "simplification.h"

typedef enum {Nord, Est, Sud, West} Orientation;
typedef struct {
  UINT x, y;
  Orientation o;
} Robot;

int image_vide(Image I);

void image_masque(Image I, Image m);

void trouver_pixel_depart(Image I,UINT *a, UINT *b);

Contour memoriser_position (UINT x,UINT y, Contour c);

void avancer(Robot *r);

void nv_orientation(Robot *r,Image I);

Contour trouver_contour(Image I, Image m, int* n, Contour c );

void elevation_degree_3(Point *p1, Point *p2,Bezier2 b);

void creat_eps(FILE* f, Liste_Bezier3 b, UINT h, UINT l);
