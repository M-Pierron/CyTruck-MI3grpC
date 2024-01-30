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

Etape* creerEtape(char *id, char* etape, char* ville);
Etape *rotationAGauche(Etape *a);
Etape *rotationADroite(Etape *a);
Etape *doubleRotationAGauche(Etape *a);
Etape *doubleRotationADroite(Etape *a);
Etape *equilibrerAVLA(Etape *a);
Etape* insertionAVLrecup(Etape* a, Etape* e, int* h);


// -- fichier Ville.c --
typedef struct Ville {
  struct Ville *gauche, *droit;
  int equilibre, nbparcourus, nbvilledepart;
  char *ville;
} Ville;

Ville *creerVille(char* nom);
Ville* rotationVGauche(Ville* a);
Ville* rotationVDroite(Ville* a);
Ville* doubleRotationVGauche(Ville* a);
Ville* doubleRotationVDroite(Ville* a);
Ville* equilibrerAVLV(Ville* a);
Ville* insertionAVL(Ville* a, Ville* e, int* h);
Ville* insertionAVLville(Ville* a, Ville* e, int* h);
Ville* triVille (Ville *a, Ville* e, int *h);
void compterparcours(Ville *a, Etape *e);
Ville* rechercherVille(Ville *a, char *nom);
Ville* dixpremiers (Ville* v, Ville *racine, int* dixpremiers);
void affichageAVL(Ville *racine);



// -- Fichier calcul --
int max(int a, int b);
int min(int a, int b);

#endif