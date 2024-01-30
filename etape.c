#include "headert.h"
#define TAILLE_LIGNE 128

Etape *creerEtape(char *id, char* etape, char* ville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - char *id : Pointeur sur le caractere pour l'id d'un trajet
                   - char *etape : Pointeur sur le caractere pour l'etape d'un trajet
                   - char *ville : Pointeur sur le caractere pour la ville d'un trajet
    
    - Fonction : Creer un Etape selon les parametres

    - Retour : Pointeur sur l'Etape creee
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

Etape *rotationAGauche(Etape *AVLetape) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'Etape

    - Fonction : Fait une rotation Gauche sur l'Etape

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/
  
  Etape* pivot = AVLetape->droit;
  AVLetape->droit = pivot->gauche;
  pivot->gauche = AVLetape;
  int eq_a = AVLetape->equilibre;
  int eq_p = pivot->equilibre;
  AVLetape->equilibre = eq_a - max(eq_p, 0) - 1;
  pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
  AVLetape= pivot;
  return AVLetape;
}

Etape *rotationADroite(Etape *AVLetape) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'Etape

    - Fonction : Fait une rotation Droite sur l'Etape

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  Etape* pivot = AVLetape->gauche;
  AVLetape->gauche = pivot->droit;
  pivot->droit = AVLetape;
  int eq_a = AVLetape->equilibre;
  int eq_p = pivot->equilibre;
  AVLetape->equilibre = eq_a - min(eq_p, 0) + 1;
  pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
  AVLetape = pivot;
  return AVLetape;
}

Etape *doublerotationAGauche(Etape *AVLetape) {
  /*-------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'Etape

    - Fonction : Fait une double rotation Gauche sur l'Etape

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  AVLetape->droit = rotationADroite(AVLetape->droit);
  return rotationAGauche(AVLetape);
}

Etape *doublerotationADroite(Etape *AVLetape) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'Etape

    - Fonction : Fait une double rotation Droite sur l'Etape

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  AVLetape->gauche = rotationAGauche(AVLetape->gauche);
  return rotationADroite(AVLetape);
}

Etape *equilibrerAVLA(Etape *AVLetape) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'Etape

    - Fonction : Equilibre l'Etape

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  if (AVLetape->equilibre >= 2) {
    if (AVLetape->droit->equilibre >= 0) {
      return rotationAGauche(AVLetape);
    } 
    else {
        return doublerotationAGauche(AVLetape);
    }
  } 
  else if (AVLetape->equilibre <= -2) {
    if (AVLetape->gauche->equilibre <= 0) {
        return rotationADroite(AVLetape);
    } 
    else {
        return doublerotationADroite(AVLetape);
    }
  }
  return AVLetape;
}

Etape *insertionAVLrecup(Etape *AVLetape, Etape *etape, int *h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Etape *AVLetape : Pointeur sur l'AVL
                   - Etape *etape : Pointeur sur l'etape
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert un nouvel Etape dans l'AVL, trié pour supprimer les doublons

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/
  if (AVLetape == NULL) {
    *h = 1;
    return etape;
  }
  else if (atoi(etape->id) < atoi(AVLetape->id)) {
    AVLetape->gauche = insertionAVLrecup(AVLetape->gauche, etape, h);
    *h = -*h;
  }
  else if (atoi(etape->id) > atoi(AVLetape->id)) {
    AVLetape->droit = insertionAVLrecup(AVLetape->droit, etape, h);
  }
  else {
    if (strcmp(etape->ville, AVLetape->ville) < 0) {
      AVLetape->gauche = insertionAVLrecup(AVLetape->gauche, etape, h);
      *h = -*h;
    }
    else if (strcmp(etape->ville, AVLetape->ville) > 0) {
      AVLetape->droit = insertionAVLrecup(AVLetape->droit, etape, h);
    }
    else {
      if (etape->villedepart == 1) {
        AVLetape->villedepart = 1;
      }
      *h= 0;
      return AVLetape;
    }
  }
  if (*h != 0) {
      AVLetape->equilibre = AVLetape->equilibre + *h;
      AVLetape= equilibrerAVLA(AVLetape);
      if (AVLetape->equilibre == 0) {
        *h = 0;
      }
      else {
        *h = 1;
      }    
  }
  return AVLetape;
}

