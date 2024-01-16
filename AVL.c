#include "header.h"
#define TAILLE_LIGNE 128

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int min (int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

Arbre* creerArbre(char* x) {
    Arbre* nouvelArbre = malloc(sizeof(Arbre));
    if (nouvelArbre == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }
  nouvelArbre->gauche = NULL;
  nouvelArbre->droit = NULL;
  nouvelArbre->equilibre = 0;
  nouvelArbre->ville = malloc(strlen(x) + 1); 
  strcpy(nouvelArbre->ville, x);
  nouvelArbre->nbparcourus = 0;
  nouvelArbre->nb_conducteurs = 0;
  nouvelArbre->conducteur = "";
  nouvelArbre->id = ""; 
  return nouvelArbre;
}

Arbre* creerArbreID(char* x, char* id, char* conducteur) {
    Arbre* nouvelArbre = malloc(sizeof(Arbre));
    if (nouvelArbre == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(1);
    }
  nouvelArbre->gauche = NULL;
  nouvelArbre->droit = NULL;
  nouvelArbre->equilibre = 0;
  nouvelArbre->ville = malloc((strlen(x) + 1)); 
  strcpy(nouvelArbre->ville, x);
  nouvelArbre->nbparcourus = 0;
  nouvelArbre->nb_conducteurs = 0;
  nouvelArbre->conducteur = malloc((strlen(conducteur) + 1));
  strcpy(nouvelArbre->conducteur, conducteur);
  nouvelArbre->id = malloc((strlen(id) + 1));
  strcpy(nouvelArbre->id, id);
  return nouvelArbre;
}

Arbre* rotationGauche(Arbre* a) {
    Arbre* pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
    a = pivot;
    return a;
}

Arbre* rotationDroite(Arbre* a) {
    Arbre* pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
    a = pivot;
    return a;
}


Arbre* doubleRotationGauche(Arbre* a) {
    a->droit = rotationDroite(a->droit);
    return rotationGauche(a);
}

Arbre* doubleRotationDroite(Arbre* a) {
    a->gauche = rotationGauche(a->gauche);
    return rotationDroite(a);
}


Arbre* insertionAVL(Arbre* a, Arbre* e, int* h) {
  if (a == NULL) {
      *h = 1;
      return e;

  }
  else if (e->nbparcourus <= a->nbparcourus) {
      a->gauche = insertionAVL(a->gauche, e, h);
      *h = -*h;
  }
  else if (e->nbparcourus > a->nbparcourus) {
      a->droit = insertionAVL(a->droit, e, h);
  }
  else {
      *h= 0;
      return a;
  }
  if (*h != 0) {
      a->equilibre = a->equilibre + *h;
      if (a->equilibre == 0) {
          *h = 0;
      }
      else {
        *h = 1;
      }    
  }
  return a;
}

Arbre* insertionAVLID(Arbre* a, Arbre* e, int* h, int* taille){
  if (a == NULL) {
    *h = 1;
    *taille += 1;
    return e;
  }
    
  else if (atoi(e->id) == atoi(a->id)) {
    if (strcmp(e->ville,a->ville) < 0) {
        a->gauche = insertionAVLID(a->gauche, e, h, taille);
        *h = -*h;
    }
    else if (strcmp(e->ville,a->ville) > 0) {
        a->droit = insertionAVLID(a->droit, e, h, taille);
    }
    else {
        *h += 0;
        return a;
    }
    if (*h != 0) {
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0) {
            *h = 0;
        }
        else {
          *h = 1;
      }
    }
  }
  else {
    *h = 1;
    a->droit = insertionAVLID(a->droit, e, h, taille);
    if (*h != 0) {
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0) {
            *h = 0;
        }
        else {
          *h = 1;
      }
    }
  }
  return a;
}


Arbre* equilibrerAVL(Arbre* a) {
    if (a->equilibre >= 2) {
        if (a->droit->equilibre >= 0) {
            return rotationGauche(a);
        } 
        else {
            return doubleRotationGauche(a);
        }
    } 
    else if (a->equilibre <= -2) {
        if (a->gauche->equilibre <= 0) {
            return rotationDroite(a);
        } 
        else {
            return doubleRotationDroite(a);
        }
    }
    return a;
}


void affichageAVL(Arbre *racine, int* dixpremiers) {
  if (racine != NULL && *dixpremiers < 10) {
    affichageAVL(racine->droit, dixpremiers);
    if (*dixpremiers < 10) {
      printf("%s %d\n", racine->ville, racine->nbparcourus);
      (*dixpremiers)++;
      if (*dixpremiers < 10) {
        affichageAVL(racine->gauche, dixpremiers);
      }
    }
  }
}

 
char ***creerTab(char*** colonne_etapes, Arbre *a, int* compteur) {
  if (colonne_etapes == NULL) {
    printf("Erreur d'allocation mémoire.\n");
    exit(1);
  }

  if (a == NULL) {
    *compteur -= 1;
    return colonne_etapes;
  }
    
  else {
    colonne_etapes[*compteur] = malloc(3*sizeof(char*));
    for (int i = 0; i < 3; i++) {
      colonne_etapes[*compteur][i] = malloc(TAILLE_LIGNE * sizeof(char*));
      if (colonne_etapes[*compteur][i] == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
      }
    }
    strcpy(colonne_etapes[*compteur][0], a->id);
    strcpy(colonne_etapes[*compteur][1], a->ville);
    strcpy(colonne_etapes[*compteur][2], a->conducteur);
    *compteur += 1;
    colonne_etapes = creerTab(colonne_etapes, a->gauche, compteur);
    *compteur += 1;
    colonne_etapes = creerTab(colonne_etapes, a->droit, compteur);
  }
  return colonne_etapes;
}

