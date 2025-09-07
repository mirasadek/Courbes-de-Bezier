#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include "calcul_contour.h"

int image_vide(Image I){
    UINT x,y;
    for (y=1;y<=hauteur_image(I);y++){
		for (x=1;x<=largeur_image(I);x++){
			if (get_pixel_image(I, x, y)== NOIR){
				return 0; // retourn faux (0) si image non vide
            }
		}
	}
    return 1;
}

void image_masque(Image I, Image m){
    UINT x,y;
    for (y=1;y<=hauteur_image(m);y++){
		for (x=1;x<=largeur_image(m);x++){
			if ((get_pixel_image(I, x, y)== NOIR) && get_pixel_image(I, x, y-1)== BLANC){
				set_pixel_image( m,  x,  y,  NOIR);
			}
		}
	}
}

void trouver_pixel_depart(Image I,UINT *a, UINT *b){
    UINT x, y;
	for (y=1;y<=hauteur_image(I);y++){
		for (x=1;x<=largeur_image(I);x++){
			if ((get_pixel_image(I, x, y) == NOIR) && (get_pixel_image(I, x, y-1) == BLANC)){
				(*a)=x;
                (*b)=y;
                return;
            }
        }
	}
}

Contour memoriser_position (UINT x,UINT y, Contour c){
    c=ajouter_element_liste_Point(c, set_point(x,y));
    return c;
}

void avancer(Robot *r){
    switch(r->o){
        case Nord :
            r->y--;
            break;

        case Sud :
            r->y++;
            break;

        case Est :
            r->x++;
            break;

        case West :
            r->x--;
            break;
    }
}

void nv_orientation (Robot *r,Image I){
    UINT x,y;
    Pixel pg,pd;
    x=r->x;
    y=r->y;
    switch(r->o){
        case Nord :
            pg = get_pixel_image(I, x, y);
            pd=get_pixel_image(I, x+1, y);
            if (pg==NOIR){
                r->o=West;
                }
            else if (pd==BLANC) {
                r->o=Est;
            }
            break;

        case Sud :
            pg = get_pixel_image(I, x+1, y+1);
            pd=get_pixel_image(I, x, y+1);
            if (pg==NOIR){
                r->o=Est;
                }
            else if (pd==BLANC){
                r->o=West;
            }
            break;

        case Est :
            pg = get_pixel_image(I, x+1, y);
            pd=get_pixel_image(I, x+1, y+1);
            if (pg==NOIR){
                r->o=Nord;
                }
            else if (pd==BLANC){
                r->o=Sud;
            }
            break;

        case West :
            pg = get_pixel_image(I, x, y+1);
            pd=get_pixel_image(I, x, y);
            if (pg==NOIR){
                r->o=Sud;
                }
            else if (pd==BLANC){
                r->o=Nord;
            }
            break;
    }
}

Contour trouver_contour(Image I, Image m, int* n, Contour c){
    UINT a,b;
    trouver_pixel_depart(m,&a,&b);
    UINT a0,b0;
    Robot r;
    a0=a-1;
    b0=b-1;
    r.x = a0;// premiere position du notre robot
    r.y=b0; // premiere position du notre robot 
    r.o = Est;
    int flag=1;
    while (flag == 1){
        c=memoriser_position(r.x,r.y,c);
        (*n)++;
        if (r.o == Est){
            set_pixel_image(m, r.x+1,r.y+1, BLANC); // supprimer pixel SE NOIR dans m
        }
        avancer(&r);
        nv_orientation(&r,I);
        if ((r.x == a0) && (r.y== b0) && (r.o==Est)){
            flag=0;
        }
    }
    c=memoriser_position(r.x,r.y,c);
    (*n)++;
    return c;
}

/*
void elevation_degree_3(Point *p1, Point *p2,Bezier2 b){ // formule elevation de degree dans le cours 
    p1->x=(b.c0.x+2*b.c1.x)/3;
    (p1->y)=(b.c0.y+2*b.c1.y)/3;

    (p2->x)=(b.c2.x+2*b.c1.x)/3;
    (p2->y)=(b.c2.y+2*b.c1.y)/3;
}
*/

void creat_eps(FILE* f, Liste_Bezier3 b, UINT h, UINT l){
    Tableau_Bezier3 TP = sequence_Bezier3_liste_vers_tableau(b);
	int k;
	int nP = TP.taille;
    Point p1,p2;
    Bezier3 B = TP.tab[0]; // recuperer le courbe d'indice 0 
	fprintf( f,"%f %f moveto ",B.c0.x, h-B.c0.y);
    //elevation_degree_3(&p1, &p2,B);
    fprintf(f, "%f %f %f %f %f %f curveto\n", p1.x, h - p1.y, p2.x, h - p2.y, B.c3.x, h - B.c3.y);
	for (k = 1; k < nP; k++) {	
        B = TP.tab[k]; // recuperer le point d'indice k 
        //elevation_degree_3(&p1, &p2,B);
        fprintf(f, "%f %f %f %f %f %f  curveto\n", B.c1.x, h-B.c1.y,B.c2.x, h-B.c2.y, B.c3.x, h-B.c3.y);
        } 
    fprintf(f,"\n");
}


int main(int argc, char** argv){
    if (argc < 2) {
    printf("Usage: %s <fichier d'entree>\n", argv[0]);
    return 1;
    }
    int i,n,t;
    UINT l,h;
    i=0; // nombre de contour
    n=0; //n = nombre de points avant simplification 
    Image I, m;
    //Tableau_Point T;
    Contour c;
    Liste_Bezier3 b;
    I=lire_fichier_image(argv[1]);
    m = creer_image(largeur_image(I), hauteur_image(I));

    image_masque(I, m);

    l= largeur_image( I);
    h= hauteur_image( I);
    FILE* f;
    char fichier[256];
    strcpy(fichier,argv[1]);
    strcpy(fichier +(strlen(fichier)-3),"eps");
    f=fopen(fichier,"w");
    fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f,"%%%%BoundingBox 0 0 %u %u \n", l, h);

    int d;
    printf("mettre une distances-seuils d = ");
    scanf("%d", &d);

    while (image_vide(m)==0){
        c= creer_liste_Point_vide();
        b = creer_liste_Bezier3_vide();
        i++;
        c=trouver_contour(I,m,&n,c); 
        int j1=0;
        int j2=(c.taille)-1;
        b = douglas_peucker_Bezier3(c, j1,j2, d);
        t=t+b.taille; // t=nombre de points apres simplification pour chaque contour
        creat_eps(f,b, h, l);
    }

    fprintf(f,"0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(f, "fill\n");
	fprintf(f,"showpage\n");
    fclose(f);
    
    printf("\nEn conclusion il ya %d contours.\nAvant simplification il y a  %d segements.\nApres simplification il y a %d segements.\n",i, n-i,t);
    return 0;
}
