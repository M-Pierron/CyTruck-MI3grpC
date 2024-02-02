#include "headers.h"
#define TAILLE_LIGNE 128
int main() {
  /*--------------------------------------------------------------------------------------
  - Prametres : - Aucun

  - Fonction : Fonction principale du programme, execute le traitement t

  - Retour : Affiche les 10 villes les plus traversees, ainsi que 0 si bon
  fonctionnement
  ---------------------------------------------------------------------------------------*/
  // -- Ouverture du fichier CSV --
  FILE *fichier;
  fichier = fopen("../data/data.csv", "r");
  // -- Verification de l'ouverture du fichier --
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  // - Declaration de variable
  char ligne[TAILLE_LIGNE];
  char **colonnes_1_5 = NULL;
  int nb_lignes = 0, colonne_voulue = 0, nb_etapes = 0, h1 = 0, h2 = 0, compteur = 0;
  char *decalage = NULL;
  Route *AVLrecup = NULL, *AVLfinal = NULL;
  
  colonnes_1_5 = realloc(colonnes_1_5, 2 * sizeof(char *));
  if (colonnes_1_5 == NULL) {
    printf("Erreur lors de l'allocation de mémoire.\n");
    exit(1);
  }
  for (int i = 0; i < 2; i++) {
    colonnes_1_5[i] = malloc(TAILLE_LIGNE * sizeof(char));
    if (colonnes_1_5[i] == NULL) {
      printf("Erreur lors de l'allocation de mémoire.\n");
    }
  }

  // -- Lecture des lignes du fichier --
  while (fgets(ligne, TAILLE_LIGNE, fichier) != NULL) {
    // -- Diviser la ligne en colonnes en utilisant la virgule comme délimiteur--
    char *colonne = strtok(ligne, ";");
    colonne_voulue = 1;
    // -- Stocker les colonnes voulues dans les tableaux correspondants --
    while (colonne != NULL && colonne_voulue < 6) {
      if (colonne_voulue == 1) {
        strcpy(colonnes_1_5[0], colonne);
      }

      if (colonne_voulue == 5) {
        strcpy(colonnes_1_5[1], colonne);
      }

      colonne = strtok(NULL, ";");
      colonne_voulue++;
    }

    AVLrecup = insertionAVLrecup(AVLrecup, creerRoute(colonnes_1_5[0]), strtof(colonnes_1_5[1], &decalage), &h1);

    nb_lignes++;
  }
  AVLfinal = triroute(AVLfinal, AVLrecup, &h2);
  afficherRoute(AVLfinal, &compteur);

  return 0;
}
