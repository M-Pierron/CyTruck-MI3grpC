#ifndef HEADER_H
#define HEADER_H
// -- Variables globales, prise arbitrairement (2^8) --

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arbre {
  struct Arbre *gauche;
  struct Arbre *droit;
  int equilibre;
  int nbparcourus;
  int nb_conducteurs;
  char *conducteur;
  char *ville;
  char *id;
} Arbre;

// -- fichier main.c --
int main();

// -- fichier AVL --
int max(int a, int b);
int min(int a, int b);
Arbre *creerArbre(char *x);
Arbre* creerArbreID(char* x, char* id, char* conducteur);
Arbre *rotationGauche(Arbre *a);
Arbre *rotationDroite(Arbre *a);
Arbre *doubleRotationGauche(Arbre *a);
Arbre *doubleRotationDroite(Arbre *a);
Arbre *insertionAVL(Arbre *a, Arbre *e, int *h);
Arbre* insertionAVLID(Arbre* a, Arbre* e, int* h, int* taille);
Arbre *equilibrerAVL(Arbre *a);
char ***creerTab(char*** colonne_etapes, Arbre *a, int* compteur);
void affichageAVL(Arbre *racine, int *dixpremiers);


#endif