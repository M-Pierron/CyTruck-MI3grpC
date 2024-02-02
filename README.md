README - CyTruck 
-----------------
Auteurs : Yanis, Adrien, Mathias

__Description__ :

Programme qui analyse le contenu du fichier de données et génére des graphiques résumant le contenu de ce fichier.


__Comment l'utiliser__ : 

1. Telecharger l'integralité du github
2. Placer le fichier data.csv dans le dossier telechargé par Github nommé CyTruck-MI3grC-main .
3. Donner les permissions d'execution au fichier scriptF.sh
4. Executer le script shell scriptF.sh, en prenant en paramètres le chemin du fichier CSV d’entrée contenant les données des trajets routiers effectués. Il prendra également d’autres. paramètres qui seront les choix des traitements à faire (si jamais il y a une mauvaise commande, un manuel d'aide va être affiché)
exemple d'exécution : ./CyTruck-MI3grC-main/scriptF.sh data.csv - aux choix entre d1,d2,l,s,t suivant les traitements désirés
5. Recuperer les graphiques voulus dans le dossier demo, le reste etant dans temp, automatiquement supprimé après une nouvelle execution du programme.

__Liste des fichiers__ : 

- calculs.c : Fontions de calcul pour le traitement s (min() et max()).
- calcult.c : Fontions de calcul pour le traitement t (min() et max()).
- etape.c : Fonctions qui permettent de gerer les AVL du type Etape (traitement t).
- headers.h : Fonction header, qui rassemble et declare les fonctions du traitement s.
- headert.h : Fonction header, qui rassemble et declare les fonctions du traitement t.
- makefile : Permet de compiler les programmes .c.
- route.c : Fonctions qui permettent de gerer les AVL du type Route (traitement s).
- scriptF.sh : Programme principale, regroupant l'ensemble du programme.
- scriptd1.sh : Programme gnuplot permettant de faire le graphique du traitement d1.
- scriptd2.sh : Programme gnuplot permettant de faire le graphique du traitement d2.
- scriptl.sh : Programme gnuplot permettant de faire le graphique du traitement l.
- scripts.sh : Programme gnuplot permettant de faire le graphique du traitement s.
- scriptt.sh : Programme gnuplot permettant de faire le graphique du traitement t.
- traitements.c : Fonction main() du traitement s.
- traitementt.c : Fonction main() du traitement t.
- ville.c : Fonctions qui permettent de gerer les AVL du type Ville (traitement t).
