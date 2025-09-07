#include<stdio.h> 
#include<stdlib.h> 
#include "geometrie_2D.h"

/*---- le type Point et la fonction set_point ----*/
/* ou inclure le module de la tache 2   
        
typedef struct Point_ { double x,y; } Point;

Point set_point(double x, double y)
{
	Point P = {x,y}; return P;
} */

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;


Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* creer une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L);

void nb_segement(Liste_Point L);

/*---- le type cellule de liste de Bezier2 ----*/
typedef struct Cellule_Liste_Bezier2_
{
	Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier2;

/*---- le type liste de bezier ----*/
typedef struct Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier2 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier2;

/*---- le type tableau de Bezier ----*/
typedef struct Tableau_Bezier_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier2;

Liste_Bezier2 creer_liste_Bezier2_vide();

Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v);

Liste_Bezier2 ajouter_element_liste_Bezier2 (Liste_Bezier2 L, Bezier2 b);

Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 b1, Liste_Bezier2 b2);

Tableau_Bezier2 sequence_Bezier2_liste_vers_tableau(Liste_Bezier2 L);


/*---- le type cellule de liste de Bezier3 ----*/
typedef struct Cellule_Liste_Bezier3_
{
	Bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier3;

/*---- le type liste de bezier ----*/
typedef struct Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier3 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier3;

/*---- le type tableau de Bezier ----*/
typedef struct Tableau_Bezier3_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier3 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier3;


Liste_Bezier3 creer_liste_Bezier3_vide();

Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 v);

Liste_Bezier3 ajouter_element_liste_Bezier3 (Liste_Bezier3 L, Bezier3 b);

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 b1, Liste_Bezier3 b2);

Tableau_Bezier3 sequence_Bezier3_liste_vers_tableau(Liste_Bezier3 L);