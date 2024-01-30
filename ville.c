#include "header.h"
#define TAILLE_LIGNE 128

Ville* creerVille(char* nom) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - char *nom : Pointeur sur le caractere pour la ville d'un trajet

    - Fonction : Creer une Ville selon les parametres

    - Retour : Ville* : Pointeur sur la Ville cree
  --------------------------------------------------------------------------------------*/

  Ville* nouvelleVille = malloc(sizeof(Ville));
  if (nouvelleVille == NULL) {
    printf("Erreur d'allocation de mémoire.\n");
    exit(1);
  }
  nouvelleVille->gauche = NULL;
  nouvelleVille->droit = NULL;
  nouvelleVille->equilibre = 0;
  nouvelleVille->nbparcourus = 0;
  nouvelleVille->nbvilledepart = 0;
  nouvelleVille->ville = strdup(nom);
  return nouvelleVille;
}

Ville* rotationVGauche(Ville* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'Ville

    - Fonction : Fait une rotation Gauche sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  if (a != NULL && a->droit != NULL) {
    Ville* pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
    a = pivot;
  }
  return a;
}

Ville* rotationVDroite(Ville* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'Ville

    - Fonction : Fait une rotation Droite sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/

  if (a != NULL && a->gauche != NULL) {
    Ville* pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;
    int eq_a = a->equilibre;
    int eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
    a = pivot;
  }
  return a;
}

Ville* doublerotationVGauche(Ville* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'Ville

    - Fonction : Fait une double rotation Gauche sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  a->droit = rotationVDroite(a->droit);
  return rotationVGauche(a);
}

Ville* doublerotationVDroite(Ville* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'Ville

    - Fonction : Fait une double rotation Droite sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/

  a->gauche = rotationVGauche(a->gauche);
  return rotationVDroite(a);
}

Ville* equilibrerAVLV(Ville* a) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'Ville

    - Fonction : Equilibre l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  if (a != NULL) {
    if (a->equilibre >= 2) {
      if (a->droit->equilibre >= 0) {
        return rotationVGauche(a);
      } 
      else {
          return doublerotationVGauche(a);
      }
    } 
    else if (a->equilibre <= -2) {
      if (a->gauche->equilibre <= 0) {
          return rotationVDroite(a);
      } 
      else {
          return doublerotationVDroite(a);
      }
    }
  }
  return a;
}

Ville* insertionAVL(Ville* a, Ville* e, int* h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'AVL
                   - Ville *e : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert une nouvelle ville dans l'AVL, trié selon le nombre de passage

    - Retour : Ville a* : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/
   if (e != NULL) {
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
        *h = 0;
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

    return a;
  }


Ville* insertionAVLville(Ville* a, Ville* e, int* h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'AVL
                   - Ville *e : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert une nouvelle ville dans l'AVL, trié pour avoir une liste de ville

    - Retour : Ville a* : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/ 
  if (a == NULL) {
    *h = 1;
    return e;
  }
    
  else if (strcmp(e->ville, a->ville) < 0) {
    a->gauche = insertionAVLville(a->gauche, e, h);
    *h = -*h;
  }
    
  else if (strcmp(e->ville, a->ville) > 0) {
    a->droit = insertionAVLville(a->droit, e, h);
  }
    
  else {
    *h = 0;
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

Ville* triVille(Ville* a, Ville* e, int* h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'AVL
                   - Ville *e : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Organise le nouveau trie

    - Retour : Ville a* : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/ 
  if (e != NULL) {
    *h = 0;
    Ville* nouvelleVille = creerVille(e->ville);
    nouvelleVille->nbparcourus = e->nbparcourus;
    nouvelleVille->nbvilledepart = e->nbvilledepart;
    a = insertionAVL(a, nouvelleVille, h);
    a = triVille(a, e->droit, h); 
    a = triVille(a, e->gauche, h); 
  }
  return a;
}

void compterparcours(Ville *a, Etape *e) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *a : Pointeur sur l'AVL
                   - Ville *e : Pointeur sur la ville

    - Fonction : Compte le nombre de passage de chaque ville

    - Retour : void
  --------------------------------------------------------------------------------------*/ 
  if (a != NULL && e != NULL) {
      Ville *villeTrouvee = rechercherVille(a, e->ville); 
      if (villeTrouvee != NULL) {
        villeTrouvee->nbparcourus++;
        if (e->villedepart == 1) {
          villeTrouvee->nbvilledepart++;
        }
      }

      compterparcours(a, e->gauche);
      compterparcours(a, e->droit);
    }
  }

Ville* rechercherVille(Ville *a, char* nom) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville* a : Pointeur sur l'AVL
                   - char* nom : Pointeur sur le nom de la ville à chercher

    - Fonction : Recherche la ville dans l'AVL

    - Retour : Ville a* : Pointeur sur l'AVL, à l'endroit trouvé de la ville ou non
  --------------------------------------------------------------------------------------*/ 
  if (a == NULL) {
    return NULL;
  }

  int comparaison = strcmp(nom, a->ville);
  if (comparaison == 0) {
    return a;
  } 

  else if (comparaison < 0) {
    return rechercherVille(a->gauche, nom);
  }

  else {
    return rechercherVille(a->droit, nom);
  }
}

Ville* dixpremiers(Ville* v, Ville *racine, int* compteur) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville* racine : Pointeur sur l'AVL
                   - int* compteur : Pointeur sur le boolen

    - Fonction : Recupere les 10 villes les plus visitées, par ordre alphabétique

    - Retour : Ville v* : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/ 
  if (racine != NULL && *compteur < 10) {
      v = dixpremiers(v, racine->droit, compteur);

      if (*compteur < 10) {
        Ville* a = creerVille(racine->ville);
        a->nbparcourus = racine->nbparcourus;
        a->nbvilledepart = racine->nbvilledepart;
        int h = 0;
        v = insertionAVLville(v, a, &h);
        (*compteur)++;
        if (*compteur < 10) {
          v = dixpremiers(v, racine->gauche, compteur);
        }
      }
    }
  
    return v;
  }

void affichageAVL(Ville *racine) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville* racine : Pointeur sur l'AVL
    
    - Fonction : Affiche l'AVL
    
    - Retour : void
  --------------------------------------------------------------------------------------*/

  if (racine != NULL) {
    affichageAVL(racine->gauche);
    printf("%s %d %d\n", racine->ville, racine->nbparcourus, racine->nbvilledepart);
    affichageAVL(racine->droit);
  }
}