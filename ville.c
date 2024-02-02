#include "headert.h"
#define TAILLE_LIGNE 128

Ville *creerVille(char *ville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - char *nom : Pointeur sur le caractere pour la ville d'un trajet

    - Fonction : Creer une Ville selon les parametres

    - Retour : Ville* : Pointeur sur la Ville cree
  --------------------------------------------------------------------------------------*/

  Ville *nouvelleVille = malloc(sizeof(Ville));
  if (nouvelleVille == NULL) {
    printf("Erreur d'allocation de mémoire.\n");
    exit(1);
  }
  nouvelleVille->gauche = NULL;
  nouvelleVille->droit = NULL;
  nouvelleVille->equilibre = 0;
  nouvelleVille->nbparcourus = 0;
  nouvelleVille->nbvilledepart = 0;
  nouvelleVille->ville = strdup(ville);
  return nouvelleVille;
}

Ville *rotationVGauche(Ville *AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'Ville

    - Fonction : Fait une rotation Gauche sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  if (AVLville != NULL && AVLville->droit != NULL) {
    Ville* pivot = AVLville->droit;
    AVLville->droit = pivot->gauche;
    pivot->gauche = AVLville;
    int eq_a = AVLville->equilibre;
    int eq_p = pivot->equilibre;
    AVLville->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
    AVLville= pivot;
  }
  return AVLville;
}

Ville *rotationVDroite(Ville *AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'Ville

    - Fonction : Fait une rotation Droite sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/

  if (AVLville != NULL && AVLville->gauche != NULL) {
    Ville* pivot = AVLville->gauche;
    AVLville->gauche = pivot->droit;
    pivot->droit = AVLville;
    int eq_a = AVLville->equilibre;
    int eq_p = pivot->equilibre;
    AVLville->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
    AVLville= pivot;
  }
  return AVLville;
}

Ville *doublerotationVGauche(Ville* AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'Ville

    - Fonction : Fait une double rotation Gauche sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  AVLville->droit = rotationVDroite(AVLville->droit);
  return rotationVGauche(AVLville);
}

Ville *doublerotationVDroite(Ville* AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'Ville

    - Fonction : Fait une double rotation Droite sur l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/

  AVLville->gauche = rotationVGauche(AVLville->gauche);
  return rotationVDroite(AVLville);
}

Ville *equilibrerAVLV(Ville *AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'Ville

    - Fonction : Equilibre l'Ville

    - Retour : Ville* : Pointeur sur le nouvel Ville
  --------------------------------------------------------------------------------------*/
  if (AVLville != NULL) {
    if (AVLville->equilibre >= 2) {
      if (AVLville->droit->equilibre >= 0) {
        return rotationVGauche(AVLville);
      } 
      else {
          return doublerotationVGauche(AVLville);
      }
    } 
    else if (AVLville->equilibre <= -2) {
      if (AVLville->gauche->equilibre <= 0) {
          return rotationVDroite(AVLville);
      } 
      else {
          return doublerotationVDroite(AVLville);
      }
    }
  }
  return AVLville;
}

Ville *insertionAVL(Ville *AVLville, Ville *nouvelleville, int *h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL
                   - Ville *nouvelleville : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert une nouvelle ville dans l'AVL, trié selon le nombre de passage

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/
   if (nouvelleville != NULL) {
      if (AVLville == NULL) {
        *h = 1;
        return nouvelleville;
      }
      else if (nouvelleville->nbparcourus <= AVLville->nbparcourus) {
        AVLville->gauche = insertionAVL(AVLville->gauche, nouvelleville, h);
        *h = -*h;
      }
      else if (nouvelleville->nbparcourus > AVLville->nbparcourus) {
        AVLville->droit = insertionAVL(AVLville->droit, nouvelleville, h);
      }
      else {
        *h = 0;
        return AVLville;
      }

      if (*h != 0) {
        AVLville->equilibre = AVLville->equilibre + *h;
        if (AVLville->equilibre == 0) {
          *h = 0;
        }
        else {
          *h = 1;
        }    
      }
    }

    return AVLville;
  }

Ville *insertionAVLville(Ville *AVLville, Ville *nouvelleville, int *h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL
                   - Ville *nouvelleville : Pointeur sur la ville
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert une nouvelle ville dans l'AVL, trié pour avoir une liste de ville

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/ 
  if (AVLville == NULL) {
    *h = 1;
    return nouvelleville;
  }
    
  else if (strcmp(nouvelleville->ville, AVLville->ville) < 0) {
    AVLville->gauche = insertionAVLville(AVLville->gauche, nouvelleville, h);
    *h = -*h;
  }
    
  else if (strcmp(nouvelleville->ville, AVLville->ville) > 0) {
    AVLville->droit = insertionAVLville(AVLville->droit, nouvelleville, h);
  }
    
  else {
    *h = 0;
    return AVLville;
  }
  
  if (*h != 0) {
    AVLville->equilibre = AVLville->equilibre + *h;
    if (AVLville->equilibre == 0) {
      *h = 0;
    }
    else {
      *h = 1;
    }
  }
  return AVLville;
}

Ville *triVille(Ville *AVLtri, Ville *AVLville, int *h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLtri : Pointeur sur l'AVL que l'on retournera
                   - Ville *AVLville : Pointeur sur la ville que l'on veut trier
                   - int *h : Pointeur sur le boolen

    - Fonction : Organise le nouveau trie

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/ 
  if (AVLville != NULL) {
    *h = 0;
    Ville* nouvelleVille = creerVille(AVLville->ville);
    nouvelleVille->nbparcourus = AVLville->nbparcourus;
    nouvelleVille->nbvilledepart = AVLville->nbvilledepart;
    AVLtri = insertionAVL(AVLtri, nouvelleVille, h);
    AVLtri = triVille(AVLtri, AVLville->droit, h); 
    AVLtri = triVille(AVLtri, AVLville->gauche, h); 
  }
  return AVLtri;
}

Ville *rechercherVille(Ville *AVLville, char* nom) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL
                   - char* nom : Pointeur sur le nom de la ville à chercher

    - Fonction : Recherche la ville dans l'AVL

    - Retour : Pointeur sur l'AVL, à l'endroit trouvé de la ville ou non
  --------------------------------------------------------------------------------------*/ 
  if (AVLville == NULL) {
    return NULL;
  }

  int comparaison = strcmp(nom, AVLville->ville);
  if (comparaison == 0) {
    return AVLville;
  } 

  else if (comparaison < 0) {
    return rechercherVille(AVLville->gauche, nom);
  }

  else {
    return rechercherVille(AVLville->droit, nom);
  }
}

Ville *dixpremiers(Ville *AVLfinal, Ville *AVLville, int *compteur) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL que l'on veut remplir
                   - Ville *AVLville : Pointeur sur l'AVL racine
                   - int *compteur : Pointeur sur le boolen

    - Fonction : Recupere les 10 villes les plus visitées, par ordre alphabétique

    - Retour : Pointeur sur l'AVL
  --------------------------------------------------------------------------------------*/ 
  if (AVLville != NULL && *compteur < 10) {
      AVLfinal = dixpremiers(AVLfinal, AVLville->droit, compteur);

      if (*compteur < 10) {
        Ville* a = creerVille(AVLville->ville);
        a->nbparcourus = AVLville->nbparcourus;
        a->nbvilledepart = AVLville->nbvilledepart;
        int h = 0;
        AVLfinal= insertionAVLville(AVLfinal, a, &h);
        (*compteur)++;
        if (*compteur < 10) {
          AVLfinal= dixpremiers(AVLfinal, AVLville->gauche, compteur);
        }
      }
    }
  
    return AVLfinal;
  }

void compterparcours(Ville *AVLville, Etape *etape) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL
                   - Ville *etape : Pointeur sur la ville

    - Fonction : Compte le nombre de passage de chaque ville

    - Retour : void
  --------------------------------------------------------------------------------------*/ 
  if (AVLville != NULL && etape != NULL) {
      Ville *villeTrouvee = rechercherVille(AVLville, etape->ville); 
      if (villeTrouvee != NULL) {
        villeTrouvee->nbparcourus++;
        if (etape->villedepart == 1) {
          villeTrouvee->nbvilledepart++;
        }
      }

      compterparcours(AVLville, etape->gauche);
      compterparcours(AVLville, etape->droit);
    }
  }

void affichageAVL(Ville *AVLville) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Ville *AVLville : Pointeur sur l'AVL
    
    - Fonction : Affiche l'AVL
    
    - Retour : void
  --------------------------------------------------------------------------------------*/

  if (AVLville != NULL) {
    affichageAVL(AVLville->gauche);
    printf("%s;%d;%d\n", AVLville->ville, AVLville->nbparcourus, AVLville->nbvilledepart);
    affichageAVL(AVLville->droit);
  }
}
