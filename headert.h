#ifndef HEADER_H
#define HEADER_H
// -- Variables globales, prise arbitrairement --
#define TAILLE_LIGNE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// -- fichier main.c --
int main();

// -- fichier Etape.c --
typedef struct Etape {
  struct Etape *gauche, *droit;
  int equilibre, villedepart;
  char *ville, *id;
} Etape;

Etape *creerEtape(char *id, char* etape, char* ville);
Etape *rotationAGauche(Etape *AVLetape);
Etape *rotationADroite(Etape *AVLetape);
Etape *doublerotationAGauche(Etape *AVLetape);
Etape *doublerotationADroite(Etape *AVLetape);
Etape *equilibrerAVLA(Etape *AVLetape);
Etape *insertionAVLrecup(Etape *AVLetape, Etape *etape, int *h);


// -- fichier Ville.c --
typedef struct Ville {
  struct Ville *gauche, *droit;
  int equilibre, nbparcourus, nbvilledepart;
  char *ville;
} Ville;

Ville *creerVille(char *ville);
Ville *rotationVGauche(Ville *AVLville);
Ville *rotationVDroite(Ville *AVLville);
Ville *doubleRotationVGauche(Ville *AVLville);
Ville *doubleRotationVDroite(Ville *AVLville);
Ville *equilibrerAVLV(Ville *AVLville);
Ville *insertionAVL(Ville *AVLville, Ville *nouvelleville, int *h);
Ville *insertionAVLville(Ville *AVLville, Ville *nouvelleville, int *h);
Ville *triVille(Ville *AVLtri, Ville *AVLville, int *h);
Ville *rechercherVille(Ville *AVLville, char* nom);
Ville *dixpremiers(Ville *AVLfinal, Ville *AVLville, int *compteur);
void compterparcours(Ville *AVLville, Etape *etape);
void affichageAVL(Ville *AVLville);

// -- Fichier calcul --
int max(int a, int b);
int min(int a, int b);

#endif
