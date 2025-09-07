#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include "simplification.h"


int main()
{
	Contour c,l,m,s;
    Bezier3 B1,B2,B3,B4;

    // n=1 avec 2 points
    int j1,j2;
    j1= 0;
    j2= 1;
	c= creer_liste_Point_vide();
	c = ajouter_element_liste_Point(c, set_point(1,2));
	c = ajouter_element_liste_Point(c, set_point(2,1));
    B1=approx_bezier3 ( c,  j1,  j2);
    printf("Courbe B1 = c0 :(%f,%f), c1:(%f, %f), c2 :(%f,%f ),c3 :(%f,%f )\n\n", B1.c0.x,B1.c0.y, B1.c1.x, B1.c1.y, B1.c2.x, B1.c2.y, B1.c3.x, B1.c3.y);
    
    //n=2 avec 3 points 
    m= creer_liste_Point_vide();
	m = ajouter_element_liste_Point(m, set_point(10,9));
	m = ajouter_element_liste_Point(m, set_point(9,5));
    m = ajouter_element_liste_Point(m, set_point(5,10));
    int n1=0;
    int n2=2;
    B3=approx_bezier3 ( m,  n1,  n2);
    printf("Courbe B3= c0 :(%f,%f), c1:(%f, %f), c2 :(%f,%f ),c3 :(%f,%f )\n\n", B3.c0.x,B3.c0.y, B3.c1.x, B3.c1.y, B3.c2.x, B3.c2.y, B3.c3.x, B3.c3.y);

    //n>=3 avec 4 points 
    l= creer_liste_Point_vide();
	l = ajouter_element_liste_Point(l, set_point(2,1));
	l = ajouter_element_liste_Point(l, set_point(6,1));
    l = ajouter_element_liste_Point(l, set_point(3,2));
    l = ajouter_element_liste_Point(l, set_point(5,5));
    int i1=0;
    int i2=8;
    B2=approx_bezier3 ( l,  i1,  i2);
    printf("Courbe B2 = c0 :(%f,%f), c1:(%f, %f), c2 :(%f,%f ),c3 :(%f,%f )\n\n", B2.c0.x,B2.c0.y, B2.c1.x, B2.c1.y, B2.c2.x, B2.c2.y, B2.c3.x, B2.c3.y);
    
    
    //n>=3 avec 9 points
    s= creer_liste_Point_vide();
	s = ajouter_element_liste_Point(s, set_point(0,0));
	s = ajouter_element_liste_Point(s, set_point(1,0));
    s = ajouter_element_liste_Point(s, set_point(1,1));
    s = ajouter_element_liste_Point(s, set_point(1,2));
    s = ajouter_element_liste_Point(s, set_point(2,2));
    s = ajouter_element_liste_Point(s, set_point(3,2));
    s = ajouter_element_liste_Point(s, set_point(3,3));
    s = ajouter_element_liste_Point(s, set_point(4,3));
    s = ajouter_element_liste_Point(s, set_point(5,3));
    int o1=0;
    int o2=8;
    B4=approx_bezier3 ( s,  o1,  o2);
    printf("Courbe B4 = c0 :(%f,%f), c1:(%f, %f), c2 :(%f,%f ), c3 :(%f,%f )\n\n", B4.c0.x,B4.c0.y, B4.c1.x, B4.c1.y, B4.c2.x, B4.c2.y, B4.c3.x, B4.c3.y);
    
    
    Tableau_Point tl;
    tl=sequence_points_liste_vers_tableau(s);
    int a=0;
    int b=tl.taille-1;
    //distance d(Pi,c(ti))
    for (int j=a+1;j<b;j++){
        int i =j-a;
        double ti = (double) (i)/ 8;
        double d =distance_point_bezier3(tl.tab[j],B4,ti);
        printf("\n%f\n", d);
    }
    return 0;
}