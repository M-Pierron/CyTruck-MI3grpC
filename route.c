#include "headers.h"

Route *creerRoute(char *id) {
  /*--------------------------------------------------------------------------------------
    - Parametres: - char *id : l'identifiant de la route

    - Fonction : Initialise la structure Route avec l'identifiant donnee en parametre

    - Retour : La nouvelle Route cree
  --------------------------------------------------------------------------------------*/
  Route *nouvelRoute = malloc(sizeof(Route));
  if (nouvelRoute == NULL) {
    printf("Erreur d'allocation de mémoire.\n");
    exit(1);
  }
  nouvelRoute->gauche = NULL;
  nouvelRoute->droit = NULL;
  nouvelRoute->id = strdup(id);
  nouvelRoute->compteur = 0;
  nouvelRoute->somme = 0;
  nouvelRoute->maxi = 0;
  nouvelRoute->mini = 0;
  return nouvelRoute;
}

Route *rotationGauche(Route *AVLroute) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL

    - Fonction : Fait une rotation Gauche sur l'AVL

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  Route* pivot = AVLroute->droit;
  AVLroute->droit = pivot->gauche;
  pivot->gauche = AVLroute;
  int eq_a = AVLroute->equilibre;
  int eq_p = pivot->equilibre;
  AVLroute->equilibre = eq_a - max(eq_p, 0) - 1;
  pivot->equilibre = min(eq_a - 2, min((eq_a + (eq_p- 2)), eq_p - 1));
  AVLroute = pivot;
  return AVLroute;
}

Route *rotationDroite(Route *AVLroute) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL

    - Fonction : Fait une rotation Droite sur l'AVL

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  Route *pivot = AVLroute->gauche;
  AVLroute->gauche = pivot->droit;
  pivot->droit = AVLroute;
  int eq_a = AVLroute->equilibre;
  int eq_p = pivot->equilibre;
  AVLroute->equilibre = eq_a - min(eq_p, 0) + 1;
  pivot->equilibre = max(eq_a + 2, max((eq_a + (eq_p + 2)), eq_p + 1));
  AVLroute = pivot;
  return AVLroute;
}

Route *doublerotationGauche(Route *AVLroute) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL

    - Fonction : Fait une double rotation Gauche sur l'AVL

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

    AVLroute->droit = rotationDroite(AVLroute->droit);
    return rotationGauche(AVLroute);
}

Route *doublerotationDroite(Route *AVLroute) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL

    - Fonction : Fait une double rotation Droite sur l'AVL

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  AVLroute->gauche = rotationGauche(AVLroute->gauche);
  return rotationDroite(AVLroute);
}

Route *equilibrerAVL(Route *AVLroute) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL

    - Fonction : Equilibre l'AVL

    - Retour : Route* : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/

  if (AVLroute->equilibre >= 2) {
    if (AVLroute->droit->equilibre >= 0) {
      return rotationGauche(AVLroute);
    } 
    else {
        return doublerotationGauche(AVLroute);
    }
  } 
  else if (AVLroute->equilibre <= -2) {
    if (AVLroute->gauche->equilibre <= 0) {
        return rotationDroite(AVLroute);
    } 
    else {
        return doublerotationDroite(AVLroute);
    }
  }
  return AVLroute;
}

Route *insertionAVL(Route *AVLroute, Route *nouvelleroute, int *h) {
/*--------------------------------------------------------------------------------------
  - Parametres : - route *AVLroute : Pointeur sur l'AVL
                 - route *nouvelleroute : Pointeur sur la route
                 - int *h : Pointeur sur le boolen

  - Fonction : Insert une nouvelle route dans l'AVL, trié selon le nombre de passage

  - Retour : Pointeur sur le nouvel AVL
--------------------------------------------------------------------------------------*/ 
if (nouvelleroute != NULL) {
    if (AVLroute == NULL) {
      *h = 1;
      return nouvelleroute;
    }
    else if (nouvelleroute->ecart <= AVLroute->ecart) {
      AVLroute->gauche = insertionAVL(AVLroute->gauche, nouvelleroute, h);
      *h = -*h;
    }
    else if (nouvelleroute->ecart > AVLroute->ecart) {
      AVLroute->droit = insertionAVL(AVLroute->droit, nouvelleroute, h);
    }
    else {
      *h = 0;
      return AVLroute;
    }

    if (*h != 0) {
      AVLroute->equilibre = AVLroute->equilibre + *h;
      if (AVLroute->equilibre == 0) {
        *h = 0;
      }
      else {
        *h = 1;
      }    
    }
  }

  return AVLroute;
}

Route *insertionAVLrecup(Route* AVLroute, Route *nouvelleroute, float km, int* h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'AVL
                   - Route *nouvelleroute : Pointeur sur la route
                   - int *h : Pointeur sur le boolen

    - Fonction : Insert un nouvel Route dans l'AVL, trié pour supprimer les doublons

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/
  if (strcmp(nouvelleroute->id, "Route ID") == 0) {
    return AVLroute;
  }
  
  if (AVLroute == NULL) {
    nouvelleroute->compteur ++;
    nouvelleroute->maxi = km;
    nouvelleroute->mini = km;
    nouvelleroute->somme = km;
    *h = 1;
    return nouvelleroute;
  }
    
  else if (atoi(nouvelleroute->id) < atoi(AVLroute->id)) {
    AVLroute->gauche = insertionAVLrecup(AVLroute->gauche, nouvelleroute, km, h);
    *h = -*h;
  }
    
  else if (atoi(nouvelleroute->id) > atoi(AVLroute->id)) {
    AVLroute->droit = insertionAVLrecup(AVLroute->droit, nouvelleroute, km, h);
  }
    
  else {
    if (AVLroute->mini > km) {
      AVLroute->mini = km;
    }
    
    if (AVLroute->maxi < km)
      AVLroute->maxi = km;
      AVLroute->somme += km;
      AVLroute->compteur++;
      *h = 0;
      return AVLroute;
   }
  
  if (*h != 0) {
      AVLroute->equilibre = AVLroute->equilibre + *h;
      AVLroute = equilibrerAVL(AVLroute);
      if (AVLroute->equilibre == 0) {
        *h = 0;
      }
        
      else {
        *h = 1;
      }    
  }
  return AVLroute;
}

Route *triroute(Route *AVLtri, Route *AVLroute, int *h) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLtri : Pointeur sur l'AVL que l'on retournera
                   - Route *AVLroute : Pointeur sur la route que l'on veut trier
                   - int *h : Pointeur sur le boolen

    - Fonction : Organise le nouveau trie

    - Retour : Pointeur sur le nouvel AVL
  --------------------------------------------------------------------------------------*/ 
  if (AVLroute != NULL) {
    *h = 0;
    Route* nouvelleroute = creerRoute(AVLroute->id);
    nouvelleroute->maxi = AVLroute->maxi;
    nouvelleroute->mini = AVLroute->mini;
    nouvelleroute->somme = AVLroute->somme;
    nouvelleroute->compteur = AVLroute->compteur;
    nouvelleroute->moyenne = AVLroute->somme / AVLroute->compteur;
    nouvelleroute->ecart = nouvelleroute->maxi - nouvelleroute->mini;
    AVLtri = insertionAVL(AVLtri, nouvelleroute, h);
    AVLtri = triroute(AVLtri, AVLroute->droit, h); 
    AVLtri = triroute(AVLtri, AVLroute->gauche, h); 
  }
  return AVLtri;
}

void afficherRoute(Route *AVLroute, int *compteur) {
  /*--------------------------------------------------------------------------------------
    - Parametres : - Route *AVLroute : Pointeur sur l'Route

    - Fonction : Affiche les 50 trajets vec l'ecart (max - min) les plus elevees

    - Retour : void
  --------------------------------------------------------------------------------------*/
  if (AVLroute != NULL) {
    if (*compteur < 50) {
      afficherRoute(AVLroute->droit, compteur);
      if (*compteur < 50) {
        printf("%s;%f;%f;%f\n", AVLroute->id, AVLroute->maxi, AVLroute->mini, AVLroute->moyenne);
        (*compteur)++;
        if (*compteur < 50) {
          afficherRoute(AVLroute->gauche, compteur);
        }
      }
    }
  }
}
