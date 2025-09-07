/****************************************************************************** 
  Interface du module de calcul geometrique en dimenson 2
******************************************************************************/

typedef struct Vecteur_{
    double x,y;
} Vecteur;

typedef struct Point_{
    double x,y;
} Point;

typedef struct Bezier_2{
    Point c0,c1,c2;
} Bezier2;

typedef struct Bezier_3{
    Point c0,c1,c2,c3;
} Bezier3;


Point set_point( double x , double y );

Point add_point( Point p1 , Point p2 );

Vecteur vec_bispoint( Point p1 , Point p2 );

Vecteur add_vecteur(Vecteur v1, Vecteur v2);

Vecteur homothetie( Vecteur v , double m );

double produit_scalaire(Vecteur v1, Vecteur v2);

double norme(Vecteur v);

double distance_2points(Point x , Point y);

double distance_seg(Point p1, Point p2, Point p3);

double distance_point_bezier2(Point Pj, Bezier2 B, double ti);

double distance_point_bezier3(Point Pj, Bezier3 B, double ti);

