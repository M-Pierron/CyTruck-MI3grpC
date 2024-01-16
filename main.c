#include "header.h"
#define TAILLE_LIGNE 128
#define NB_COLONNES 6
int main() {
  /*--------------------------------------------------------------------------------------
  - Prametres : - Aucun

  - Fonction : Fonction principale du programme, execute le traitement t

  - Retour : Affiche les 10 villes les plus traversees, ainsi que 0 si bon
  fonctionnement
  ---------------------------------------------------------------------------------------*/

  // -- Ouverture du fichier CSV --
  FILE *fichier;
  fichier = fopen("data.csv", "r, ccs=UTF-8");
  // -- Verification de l'ouverture du fichier --
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  // -- Lecture des lignes du fichier --
  char ligne[TAILLE_LIGNE];
  char ***colonnes_1_3_6 = malloc(1);
  char ***colonnes_1_4_6 = malloc(1);
  int nb_lignes = 0;
  while (fgets(ligne, TAILLE_LIGNE, fichier) != NULL) {
    // -- Allouer de la mémoire pour stocker les colonnes 1 et 3 de cette ligne --
    colonnes_1_3_6 = realloc(colonnes_1_3_6, (nb_lignes + 1) * sizeof(char **));
    if (colonnes_1_3_6 == NULL) {
      printf("Erreur d'allocation mémoire 1.\n");
      fclose(fichier);
      exit(2);
    }

    colonnes_1_3_6[nb_lignes] = malloc(3 * sizeof(char *));
    if (colonnes_1_3_6[nb_lignes] == NULL) {
      printf("Erreur d'allocation mémoire 2.\n");
      fclose(fichier);
      exit(3);
    }

    for (int j = 0; j < 3; j++) {
      colonnes_1_3_6[nb_lignes][j] = malloc(TAILLE_LIGNE * sizeof(char *));
      if (colonnes_1_3_6[nb_lignes][j] == NULL) {
        printf("Erreur d'allocation mémoire 3.\n");
        fclose(fichier);
        exit(4);
      }
    }

    // -- Allouer de la mémoire pour stocker les colonnes 1 et 4 de cette ligne
    // --
    colonnes_1_4_6 = realloc(colonnes_1_4_6, (nb_lignes + 1) * sizeof(char **));
    if (colonnes_1_4_6 == NULL) {
      printf("Erreur d'allocation mémoire 5.\n");
      fclose(fichier);
      exit(5);
    }

    colonnes_1_4_6[nb_lignes] = malloc(3 * sizeof(char *));
    if (colonnes_1_4_6[nb_lignes] == NULL) {
      printf("Erreur d'allocation mémoire 6.\n");
      fclose(fichier);
      exit(6);
    }

    for (int j = 0; j < 3; j++) {
      colonnes_1_4_6[nb_lignes][j] = malloc(TAILLE_LIGNE * sizeof(char *));
      if (colonnes_1_4_6[nb_lignes][j] == NULL) {
        printf("Erreur d'allocation mémoire 7.\n");
        fclose(fichier);
        exit(7);
      }
    }

    // -- Diviser la ligne en colonnes en utilisant la virgule comme délimiteur
    // --
    char *colonne = strtok(ligne, ";");
    int colonne_voulue = 1;
    // -- Stocker les colonnes voulues dans les tableaux correspondants --
    while (colonne != NULL && colonne_voulue < 5) {
      if (colonne_voulue == 1) {
        strcpy(colonnes_1_3_6[nb_lignes][0], colonne);
        strcpy(colonnes_1_4_6[nb_lignes][0], colonne);
      }

      if (colonne_voulue == 3) {
        strcpy(colonnes_1_3_6[nb_lignes][1], colonne);
      }

      if (colonne_voulue == 4) {
        strcpy(colonnes_1_4_6[nb_lignes][1], colonne);
      }

      if (colonne_voulue == 6) {
        strcpy(colonnes_1_3_6[nb_lignes][2], colonne);
        strcpy(colonnes_1_4_6[nb_lignes][2], colonne);
      }
      colonne = strtok(NULL, ";");
      colonne_voulue++;
    }

    nb_lignes++;
  }

  // -- Fusionner colonnes_1_3_6 et colonnes_1_4_6 dans un nouveau tableau --
  int nb_lignes2 = 0;
  Arbre **tabAVLID = malloc(1);
  if (tabAVLID == NULL) {
    printf("Erreur d'allocation mémoire 8.\n");
    fclose(fichier);
    exit(8);
  }

  Arbre *AVLID = NULL;
  int taille = 0;
  for (int i = 1; i < nb_lignes; i++) {
    tabAVLID = realloc(tabAVLID, (nb_lignes2+1)* sizeof(Arbre **));
    if (tabAVLID == NULL) {
      printf("Erreur d'allocation mémoire 9.\n");
      fclose(fichier);
      exit(9);
    }
    tabAVLID[nb_lignes2] = malloc(sizeof(Arbre *));
    if (tabAVLID[nb_lignes2] == NULL) {
      printf("Erreur d'allocation mémoire 9.\n");
      fclose(fichier);
      exit(9);
    }
    int h = 0;
    tabAVLID[nb_lignes2] = creerArbreID(colonnes_1_3_6[i][1], colonnes_1_3_6[i][0], colonnes_1_3_6[i][2]);
    AVLID = insertionAVLID(AVLID, tabAVLID[nb_lignes2], &h, &taille);
    nb_lignes2++;
    tabAVLID = realloc(tabAVLID, (nb_lignes2+1)* sizeof(Arbre **));
    if (tabAVLID == NULL) {
      printf("Erreur d'allocation mémoire 9.\n");
      fclose(fichier);
      exit(9);
    }
    
    tabAVLID[nb_lignes2] = malloc(sizeof(Arbre *));
    if (tabAVLID[nb_lignes2] == NULL) {
      printf("Erreur d'allocation mémoire 9.\n");
      fclose(fichier);
      exit(9);
    }
    
    tabAVLID[nb_lignes2] = creerArbreID(colonnes_1_4_6[i][1], colonnes_1_4_6[i][0],colonnes_1_4_6[i][2]);
    h = 0;
    AVLID = insertionAVLID(AVLID, tabAVLID[nb_lignes2], &h, &taille);
    nb_lignes2++;
  }
  AVLID = equilibrerAVL(AVLID);

  int nb_lignes3 = 0;
  char ***colonne_etapes = malloc((taille + 1) * sizeof(char **));
  if (colonne_etapes == NULL) {
    printf("Erreur d'allocation mémoire 10.\n");
    fclose(fichier);
    exit(10);
  }

  colonne_etapes = creerTab(colonne_etapes, AVLID, &nb_lignes3);

  // -- Creer une liste des villes et des conducteurs--
  char **villes = malloc(1);
  char **conducteurs = malloc(1);
  if (villes == NULL) {
    printf("Erreur d'allocation mémoire 16.\n");
    fclose(fichier);
    exit(14);
  }

  if (conducteurs == NULL) {
    printf("Erreur d'allocation mémoire 16.\n");
    fclose(fichier);
    exit(14);
  }

  // -- Creer une liste des villes et des conducteurs--
  int nb_villes = 0;
  int nb_conducteurs = 0;
  int existe_deja = 0;
  for (int i = 0; i < nb_lignes3; i++) {
    existe_deja = 0;
    for (int j = 0; j < nb_villes; j++) {
      if (strcmp(villes[j], colonne_etapes[i][1]) == 0) {
        existe_deja = 1;
        break;
      }
    }

    if (!existe_deja) {
      villes = realloc(villes, (nb_villes + 1) * sizeof(char *));
      if (villes == NULL) {
        printf("Erreur d'allocation mémoire 17.\n");
        fclose(fichier);
        exit(15);
      }

      villes[nb_villes] = malloc(TAILLE_LIGNE * sizeof(char *));
      if (villes[nb_villes] == NULL) {
        printf("Erreur d'allocation mémoire 18.\n");
        fclose(fichier);
        exit(16);
      }
      strcpy(villes[nb_villes], colonne_etapes[i][1]);
      nb_villes++;
    }
  }

  
  for (int i = 0; i < nb_lignes3; i++) {
    existe_deja = 0;
    for (int j = 0; j < nb_conducteurs; j++) {
      if (strcmp(conducteurs[j], colonne_etapes[i][2]) == 0) {
        existe_deja = 1;
        break;
      }
    }

    if (!existe_deja) {
      conducteurs = realloc(conducteurs, (nb_conducteurs + 1) * sizeof(char *));
      if (conducteurs == NULL) {
        printf("Erreur d'allocation mémoire 17.\n");
        fclose(fichier);
        exit(15);
      }

      conducteurs[nb_conducteurs] = malloc(TAILLE_LIGNE * sizeof(char *));
      if (conducteurs[nb_conducteurs] == NULL) {
        printf("Erreur d'allocation mémoire 18.\n");
        fclose(fichier);
        exit(16);
      }
      strcpy(conducteurs[nb_conducteurs], colonne_etapes[i][2]);
      nb_conducteurs++;
    }
  }
  
  
  // -- Creation de l'AVL pour trier et compter les passages --
  Arbre **tabAVL = malloc(nb_villes * sizeof(Arbre **));
  if (tabAVL == NULL) {
    printf("Erreur d'allocation mémoire 19.\n");
    fclose(fichier);
    exit(17);
  }

  Arbre *AVL = NULL;
  for (int i = 0; i < nb_villes; i++) {
    tabAVL[i] = malloc(sizeof(Arbre *));
    if (tabAVL[i] == NULL) {
      printf("Erreur d'allocation mémoire 20.\n");
      fclose(fichier);
      exit(18);
    }

    tabAVL[i] = creerArbre(villes[i]);
    for (int j = 0; j < nb_lignes3; j++) {
      if (strcmp(villes[i], colonne_etapes[j][1]) == 0) {
        tabAVL[i]->nbparcourus += 1;
      }
    }

    int h = 0;
    AVL = insertionAVL(AVL, tabAVL[i], &h);
  }

  // -- Affichage de l'AVL --
  int dixpremiers = 0;
  affichageAVL(AVL, &dixpremiers);

  // -- Libérer la mémoire occupée --
  for (int i = 0; i < nb_lignes; i++) {
    for (int j = 0; j < 3; j++) {
      free(colonnes_1_3_6[i][j]);
      free(colonnes_1_4_6[i][j]);
    }
    free(colonnes_1_3_6[i]);
    free(colonnes_1_4_6[i]);
  }
  free(colonnes_1_3_6);
  free(colonnes_1_4_6);

  for (int i = 0; i < nb_villes; i++) {
    free(villes[i]);
    free(tabAVL[i]);
  }
  free(villes);
  free(tabAVL);

  for (int i = 0; i < nb_conducteurs; i++) {
    free(conducteurs[i]);
  }
  free(conducteurs);

  for (int i = 0; i < nb_lignes2; i++) {
    free(tabAVLID[i]);
  }
  free(tabAVLID);

  for (int i = 0; i < nb_lignes3; i++) {
    for (int j = 0; j < 2; j++) {
      free(colonne_etapes[i][j]);
    }
    free(colonne_etapes[i]);
  }
  free(colonne_etapes);

  fclose(fichier);
  return 0;
}
