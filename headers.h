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

// -- fichier route.c --
typedef struct Route {
  struct Route *gauche, *droit;
  int equilibre, compteur;
  float mini, maxi, somme, moyenne, ecart;
  char *id;
} Route;

Route *creerRoute(char *id);
Route *rotationGauche(Route *AVLroute);
Route *rotationDroite(Route *AVLroute);
Route *doublerotationGauche(Route *AVLroute);
Route *doublerotationDroite(Route *AVLroute);
Route *equilibrerAVL(Route *AVLroute);
Route *insertionAVL(Route *AVLroute, Route *nouvelleroute, int *h);
Route *insertionAVLrecup(Route* AVLroute, Route *nouvelleroute, float km, int* h);
Route *triroute(Route *AVLtri, Route *AVLroute, int *h);
void afficherRoute(Route *AVLroute, int *compteur);



// -- Fichier calculs --
int max(int a, int b);
int min(int a, int b);


#endif