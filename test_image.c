#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

int main(int argc, char** argv){
    
    if (argc < 2) {
    printf("Usage: %s <fichier d'entree>\n", argv[0]);
    return 1;
    }
    Image I;
    I=lire_fichier_image(argv[1]);
    printf("l'image recue :\n");
    ecrire_image(I);
    printf("\n###################################################\n\n");
    printf("l'inverse du l'image :\n");
    ecrire_image(negatif_image(I));
    return 0;
}