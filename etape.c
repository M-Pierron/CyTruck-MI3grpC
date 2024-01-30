#include "header.h"
#define TAILLE_LIGNE 128

Etape* creerEtape(char *id, char* etape, char* ville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - char *id : Pointeur sur le caractere pour l'id d'un trajet
                   - char *etape : Pointeur sur le caractere pour l'etape d'un trajet
                   - char *ville : Pointeur sur le caractere pour la ville d'un trajet
    
    - Fonction : Creer un Etape selon les parametres

    - Retour : Etape* : Pointeur sur l'Etape cree
  --------------------------------------------------------------------------------------*/
  
  Etape* nouvelEtape = malloc(sizeof(Etape));
  if (nouvelEtape == NULL) {
      printf("Erreur d'allocation de mémoire.\n");
      exit(1);
  }
  nouvelEtape->gauche = NULL;
  nouvelEtape->droit = NULL;
  nouvelEtape->equilibre = 0;
  if (atoi(etape) == 1) {
    nouvelEtape->villedepart = 1;
  }
  else {
    nouvelEtape->villedepart = 0;
  }
  nouvelEtape->id = strdup(id);
  nouvelEtape->ville = strdup(ville);
  return nouvelEtape;
}

Etape* rotationAGauche(Etape* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'Etape

    - Fonction : Fait une rotation Gauche sur l'Etape

    - Retour : Etape* : Pointeur sur le nouvel Etape
  --------------------------------------------------------------------------------------*/
  
  Etape* pivot = a->droit;
  a->droit = pivot->gauche;
  pivot->gauche = a;
  int eq_a = a->equilibre;
  int eq_p = pivot->equilibre;
  a->equilibre = eq_a - max(eq_p, 0) - 1;
  pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
  a = pivot;
  return a;
}

Etape* rotationADroite(Etape* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'Etape

    - Fonction : Fait une rotation Droite sur l'Etape

    - Retour : Etape* : Pointeur sur le nouvel Etape
  --------------------------------------------------------------------------------------*/

  Etape* pivot = a->gauche;
  a->gauche = pivot->droit;
  pivot->droit = a;
  int eq_a = a->equilibre;
  int eq_p = pivot->equilibre;
  a->equilibre = eq_a - min(eq_p, 0) + 1;
  pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
  a = pivot;
  return a;
}

Etape* doublerotationAGauche(Etape* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'Etape

    - Fonction : Fait une double rotation Gauche sur l'Etape

    - Retour : Etape* : Pointeur sur le nouvel Etape
  --------------------------------------------------------------------------------------*/

    a->droit = rotationADroite(a->droit);
    return rotationAGauche(a);
}

Etape* doublerotationADroite(Etape* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'Etape

    - Fonction : Fait une double rotation Droite sur l'Etape

    - Retour : Etape* : Pointeur sur le nouvel Etape
  --------------------------------------------------------------------------------------*/

  a->gauche = rotationAGauche(a->gauche);
  return rotationADroite(a);
}

Etape* equilibrerAVLA(Etape* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'Etape

    - Fonction : Equilibre l'Etape

    - Retour : Etape* : Pointeur sur le nouvel Etape
  --------------------------------------------------------------------------------------*/

  if (a->equilibre >= 2) {
    if (a->droit->equilibre >= 0) {
      return rotationAGauche(a);
    } 
    else {
        return doublerotationAGauche(a);
    }
  } 
  else if (a->equilibre <= -2) {
    if (a->gauche->equilibre <= 0) {
        return rotationADroite(a);
    } 
    else {
        return doublerotationADroite(a);
    }
  }
  return a;
}

Etape* insertionAVLrecup(Etape* a, Etape* e, int* h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *a : Pointeur sur l'AVL
                   - Etape *e : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert un nouvel Etape dans l'AVL, trié pour supprimer les doublons

    - Retour : Etape a* : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/
  if (a == NULL) {
    *h = 1;
    return e;
  }
  else if (atoi(e->id) < atoi(a->id)) {
      a->gauche = insertionAVLrecup(a->gauche, e, h);
      *h = -*h;
  }
  else if (atoi(e->id) > atoi(a->id)) {
      a->droit = insertionAVLrecup(a->droit, e, h);
  }
  else {
    if (strcmp(e->ville, a->ville) < 0) {
      a->gauche = insertionAVLrecup(a->gauche, e, h);
      *h = -*h;
    }
    else if (strcmp(e->ville, a->ville) > 0) {
      a->droit = insertionAVLrecup(a->droit, e, h);
    }
    else {
      if (e->villedepart == 1) {
        a->villedepart = 1;
      }
      *h= 0;
      return a;
    }
  }
  if (*h != 0) {
      a->equilibre = a->equilibre + *h;
      a = equilibrerAVLA(a);
      if (a->equilibre == 0) {
        *h = 0;
      }
      else {
        *h = 1;
      }    
  }
  return a;
}

