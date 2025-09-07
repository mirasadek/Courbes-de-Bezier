#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include "simplification.h"

Bezier2 approx_bezier2 (Contour c, int j1, int j2){
    double n =j2-j1;
    //printf("\nn=%f\n", n );
    Tableau_Point TP = sequence_points_liste_vers_tableau(c);
    Bezier2 B;
    B.c0=TP.tab[j1];
    B.c2=TP.tab[j2];
    Point j3;
    j3= add_point(TP.tab[j1],TP.tab[j2]);
    if (n==1){
        B.c1.x=j3.x*(0.5);
        B.c1.y=j3.y*(0.5);
    }
    else{
        double alpha, beta;
        alpha= (3*n)/(n*n-1);
        beta = (1-(2*n))/(2*(n+1));
        //printf("alpha=%f\n", alpha);
        //printf("beta=%f\n", beta);
        Point a;
        a.x=0;
        a.y=0;
        for( int i=1; i <=n-1; i++){
            a=add_point(a,TP.tab[i+j1]);
        }
        B.c1.x=a.x*alpha+j3.x*beta;
        B.c1.y=a.y*alpha+j3.y*beta;
    }
    return B;
}

double delta(double k,double n){
    return (6*k*k*k*k)-(8*n*k*k*k)+(6*k*k)-(4*n*k)+(n*n*n*n)-(n*n);
    }

Bezier3 approx_bezier3 (Contour c, int j1, int j2){
    double n =j2-j1;
    Tableau_Point TP = sequence_points_liste_vers_tableau(c);
    Bezier3 B1;
    Point p0,p1,p2;
    p0=TP.tab[j1];
    p1=TP.tab[j2];
    p2=TP.tab[j1+1];
    B1.c0=p0;
    B1.c3=p1;

    if (n==1){
        B1.c1.x=(2*p0.x+p1.x)/3;
        B1.c1.y=(2*p0.y+p1.y)/3;
        B1.c2.x=(p0.x+2*p1.x)/3;
        B1.c2.y=(p0.y+2*p1.y)/3;
    }
    else if (n==2){
        B1.c1.x=(4*p2.x-p1.x)/3;
        B1.c1.y=(4*p2.y-p1.y)/3;
        B1.c2.x=(4*p2.x-p0.x)/3;
        B1.c2.y=(4*p2.y-p0.y)/3; 
    } 
    else{
        double alpha,beta,lambda;
        Point a,b;
        a.x=0;
        a.y=0;
        b.x=0;
        b.y=0;
        alpha=((-15*n*n*n)+(5*n*n)+(2*n)+4)/(3*(n+2)*((3*n*n)+1));
        beta=((10*n*n*n)-(15*n*n)+n+2)/(3*(n+2)*((3*n*n)+1));
        lambda=(70*n)/(3*(n*n-1)*(3*n*n+1)*(n*n-4));
        for (int i=1; i<=n-1;i++){
            a.x += delta(i,n)*(TP.tab[j1+i]).x;
            a.y += delta(i,n)*(TP.tab[j1+i]).y;
            b.x += delta(n-i,n)*(TP.tab[j1+i]).x;
            b.y += delta(n-i,n)*(TP.tab[j1+i]).y;
        }
        B1.c1.x=alpha*p0.x+lambda*a.x+beta*p1.x;
        B1.c1.y=alpha*p0.y+lambda*a.y+beta*p1.y;
        B1.c2.x=beta*p0.x+lambda*b.x+alpha*p1.x;
        B1.c2.y=beta*p0.y+lambda*b.y+alpha*p1.y;

    }
    return B1;
}

Contour douglas_peucker(Contour c, int j1, int j2, double d){

    Tableau_Point TP = sequence_points_liste_vers_tableau(c);
	Point  P1, P2, Pj;
    P1=TP.tab[j1];
    P2=TP.tab[j2]; // before pb here because i passed a j2 > c.taille

    Contour l, l1, l2;
    l=creer_liste_Point_vide();
    

    double dmax=0;
    double dj; 
    int k=j1;


    for (int j=j1+1; j<=j2; j++){
        Pj=TP.tab[j];
        dj=distance_seg(Pj, P1, P2);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }

    if (dmax<=d){
        l=ajouter_element_liste_Point(l,P1);
        l=ajouter_element_liste_Point(l,P2);
    }
    else{

        l1=douglas_peucker(c,j1,k,d);
        l2=douglas_peucker(c,k,j2,d);
        l=concatener_liste_Point(l1,l2);
    }
    //ecrire_contour(l);
    return l;
}



Liste_Bezier2 douglas_peucker_Bezier2(Contour c, int j1, int j2, double d){

    Tableau_Point TP = sequence_points_liste_vers_tableau(c);
    Point Pj;
	double n =j2-j1;
    Bezier2 B= approx_bezier2(c, j1,j2);
    Liste_Bezier2 l, l1, l2;
    double dmax=0;
    double ti,i,dj; 
    int k=j1;

    l=creer_liste_Bezier2_vide();

    for (int j=j1+1; j<=j2; j++){
        i=j-j1;
        ti=i/n;
        Pj=TP.tab[j];
        dj=distance_point_bezier2(Pj, B,ti);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }

    if (dmax<=d){
        l=ajouter_element_liste_Bezier2(l,B);
    }
    else{

        l1=douglas_peucker_Bezier2(c,j1,k,d);
        l2=douglas_peucker_Bezier2(c,k,j2,d);
        l=concatener_liste_Bezier2(l1,l2);
    }
    return l;
}



Liste_Bezier3 douglas_peucker_Bezier3(Contour c, int j1, int j2, double d){

    Tableau_Point TP = sequence_points_liste_vers_tableau(c);
    Point Pj;
	double n =j2-j1;
    Bezier3 B= approx_bezier3(c, j1,j2);
    Liste_Bezier3 l, l1, l2;
    double dmax=0;
    double ti,i,dj; 
    int k=j1;

    l=creer_liste_Bezier3_vide();

    for (int j=j1+1; j<=j2; j++){
        i=j-j1;
        ti=i/n;
        Pj=TP.tab[j];
        dj=distance_point_bezier3(Pj, B,ti);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }

    if (dmax<=d){
        l=ajouter_element_liste_Bezier3(l,B);
    }
    else{

        l1=douglas_peucker_Bezier3(c,j1,k,d);
        l2=douglas_peucker_Bezier3(c,k,j2,d);
        l=concatener_liste_Bezier3(l1,l2);
    }
    return l;
}