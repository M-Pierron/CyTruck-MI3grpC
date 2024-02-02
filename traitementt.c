#include "headert.h"
#define TAILLE_LIGNE 128
#define NB_COLONNES 4
int main() {
  /*--------------------------------------------------------------------------------------
  - Prametres : - Aucun

  - Fonction : Fonction principale du programme, execute le traitement t

  - Retour : Affiche les 10 villes les plus traversees, ainsi que 0 si bon
  fonctionnement
  ---------------------------------------------------------------------------------------*/

  // -- Ouverture du fichier CSV --
  FILE *fichier;
  fichier = fopen("../data/data.csv", "r, ccs=UTF-8");
  // -- Verification de l'ouverture du fichier --
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  // - Declaration de variable
  char ligne[TAILLE_LIGNE];
  char **colonnes1a4 = NULL;
  int nb_lignes = 0, colonne_voulue = 0, nb_etapes = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0, h5 = 0, compteur = 0;
  Etape *AVLrecup = NULL;
  Ville *AVLville = NULL, *AVLtemp = NULL, *AVLfinal = NULL;

  colonnes1a4 = malloc(4 * sizeof(char*));
  if (colonnes1a4 == NULL) {
    printf("Erreur lors de l'allocation de mémoire.\n");
    exit(1);
  }
  for (int i = 0; i < 4; i++){
    colonnes1a4[i] = malloc(TAILLE_LIGNE * sizeof(char));
    if (colonnes1a4[i] == NULL) {
      printf("Erreur lors de l'allocation de mémoire.\n");
    }
  }

  // -- Lecture des lignes du fichier --
  while (fgets(ligne, TAILLE_LIGNE, fichier) != NULL) {        
    // -- Diviser la ligne en colonnes en utilisant la virgule comme délimiteur --
    char *colonne = strtok(ligne, ";");
    colonne_voulue = 1;
    // -- Stocker les colonnes voulues dans les tableaux correspondants --
    while (colonne != NULL && colonne_voulue < 5) {
      if (colonne_voulue == 1) {
        strcpy(colonnes1a4[0], colonne);
      }

      if (colonne_voulue == 2) {
        strcpy(colonnes1a4[1], colonne);	
      }

      if (colonne_voulue == 3) {
        strcpy(colonnes1a4[2], colonne);
      }

      if (colonne_voulue == 4) {
        strcpy(colonnes1a4[3], colonne);
      }
      
      colonne = strtok(NULL, ";");
      colonne_voulue++;
    }
    
    if (atoi(colonnes1a4[1]) == 1) {
    AVLrecup = insertionAVLrecup(AVLrecup, creerEtape(colonnes1a4[0], "1", colonnes1a4[2]), &h1);
    }
      
    else {
      AVLrecup = insertionAVLrecup(AVLrecup, creerEtape(colonnes1a4[0], "0", colonnes1a4[2]), &h1);
    }
    
    AVLrecup = insertionAVLrecup(AVLrecup, creerEtape(colonnes1a4[0], "0", colonnes1a4[3]), &h2);
    AVLville = insertionAVLville(AVLville, creerVille(colonnes1a4[1]), &h3);
    AVLville = insertionAVLville(AVLville, creerVille(colonnes1a4[2]), &h4);
    nb_lignes++;
  }

  // -- Libération de la mémoire allouée pour les colonnes --
  for (int i = 0; i < 4; i++){
    free(colonnes1a4[i]);
  }
  free(colonnes1a4);  
  
  // -- Affichage des 10 villes les plus traversees --
  compterparcours(AVLville, AVLrecup);
  AVLtemp = triVille(AVLtemp, AVLville, &h5);
  AVLfinal = dixpremiers(AVLfinal, AVLtemp, &compteur);
  affichageAVL(AVLfinal); 
  fclose(fichier);
  return 0;
}
