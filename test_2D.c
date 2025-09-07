#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include"geometrie_2D.h"

int main(int argc, char** argv){
    double x,y;
    double z,n;
    double l,m;
    Point p,b,a;

    printf("entrer les coordonnee d'un point p : x et y\n");
    scanf("%lf%lf", &x, &y);
    p=set_point( x , y );

    printf("entrer les coordonnee d'un autre point a : z et n \n");
    scanf("%lf%lf", &z, &n);
    a=set_point( z , n );

    printf("entrer les coordonnee d'un autre point b : l et m \n");
    scanf("%lf%lf", &l, &m);
    b=set_point( l , m );

    printf("la distance est %lf : \n", distance_seg(p, a,b));
    return 0;
}
  