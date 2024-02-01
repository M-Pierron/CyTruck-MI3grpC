README - CyTruck 
-----------------
Auteurs : Yanis, Adrien, Mathias

__Description__ :

Programme qui analyse le contenu du fichier de données et génére des graphiques résumant le contenu de ce fichier.


__Comment l'utiliser__ : 

1. Telecharger l'integralité du github, et le placer à la racine ~.
2. Mettre le fichier data.csv egalement à la racine.
3. Executer le script shell script_global.sh, en prenant en paramètres le chemin du fichier CSV d’entrée contenant les données des trajets routiers effectués. Il prendra également d’autres paramètres qui seront les choix des traitements à faire (si jamais il y a une mauvaise commande, un manuel d'aide va être affiché)
4. Recuperer les résultats voulus dans les dossiers concernés en fonction du cahier des charges.


__Liste des fichiers__ : 

- calculs.c : Fontions de calcul pour le traitement s (min() et max()).
- calcult.c : Fontions de calcul pour le traitement t (min() et max()).
- etape.c : Fonctions qui permettent de gerer les AVL du type Etape (traitement t).
- headers.h : Fonction header, qui rassemble et declare les fonctions du traitement s.
- headert.h : Fonction header, qui rassemble et declare les fonctions du traitement t.
- makefiles.txt : Permet de compiler le traitement s.
- makefilet.txt : Permet de compiler le traitement t.
- route.c : Fonctions qui permettent de gerer les AVL du type Route (traitement s).
- script_global.sh : Programme principale, regroupant l'ensemble du programme.
- scriptd1.sh : Programme gnuplot permettant de faire le graphique du traitement d1.
- scriptd2.sh : Programme gnuplot permettant de faire le graphique du traitement d2.
- scriptl.sh : Programme gnuplot permettant de faire le graphique du traitement l.
- scripts.sh : Programme gnuplot permettant de faire le graphique du traitement s.
- scriptt.sh : Programme gnuplot permettant de faire le graphique du traitement t.
- traitements.c : Fonction main() du traitement s.
- traitementt.c : Fonction main() du traitement t.
- ville.c : Fonctions qui permettent de gerer les AVL du type Ville (traitement t).
