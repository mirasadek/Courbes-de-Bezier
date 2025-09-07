#include<stdio.h> 
#include<stdlib.h> 
#include "exemple_sequence_point.h"

Bezier2 approx_bezier2 (Contour c, int j1, int j2);

Bezier3 approx_bezier3 (Contour c, int j1, int j2);

double delta(double k,double n);

Contour douglas_peucker(Contour c, int i, int j, double d);

Liste_Bezier2 douglas_peucker_Bezier2(Contour c, int j1, int j2, double d);

Liste_Bezier3 douglas_peucker_Bezier3(Contour c, int j1, int j2, double d);