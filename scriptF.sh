#!/bin/bash

## -- Creation des dossiers et deplacement des programmes C et tout ce qui s'y rapporte dans le dossier 'progc' 

mkdir -p data progc images temp demo

cp data.csv data/

# Définir la locale pour le format numérique
export LC_NUMERIC="en_US.UTF-8"

# Définition des fonctions pour chaque traitement
traitement_d1() {
    fichier="$1"
    # Obtient le nom des conducteurs avec le plus grand nombre de trajets
    conducteurs_trajets=$(awk -F';' 'NR > 1 {if (!seen[$6,$1]) {count[$6]++}; seen[$6,$1]=1} END {for (driver in count) print count[driver], driver}' "$fichier" | sort -nr)
    # Affiche les conducteurs avec le plus grand nombre de trajets différents
    echo "Top conducteurs avec le plus grand nombre de trajets différents :"
    echo "$conducteurs_trajets"| awk '{print $1 ";" $2, $3}' | head -n 10 > resultatd1.txt
    gnuplot scriptd1.sh 
    convert -rotate 90 graphique-d1.png graphd1.png
    rm graphique-d1.png
}

traitement_d2() {
    fichier="$1"
    # Trier les trajets par distance décroissante et afficher les 10 premiers avec le nom du conducteur
    echo "Top 10 des conducteur ayant parcouru la plus grande distance totales"
    awk -F';' '{arr[$6]+=$5} END {for (driver in arr) printf "%s;%.2f\n", driver, arr[driver]}' $fichier | sort -t ';' -k2 -nr | head -n 10 > resultatd2.txt
    # Exécute le script Gnuplot
    gnuplot scriptd2.sh
    convert -rotate 90 graphique-d2.png graphd2.png
    rm graphique-d2.png   
}

traitement_l() {
    fichier="$1"
    #Trier les trajets par distances décroissante et afficher les 10 trajets les plus longs dans l'ordre croissant en fonction de leur ID route (identifaint de trajet)
    echo "Les 10 trajets les plus longs dans l'ordre croissant de leur Identifiant de trajet"
    awk -F ';' 'NR > 1 {arr[$1]+=$5} END {for (i in arr) printf "%s;%.3f\n", i, arr[i]}' "$fichier" \
    | sort -t ';' -k2 -nr | head -n 10 | sort -t ';' -k1 -n > resultatl.txt
    # Exécute le script Gnuplot
    gnuplot scriptl.sh   
}

traitement_s() {
    # Copier le programme C, le makefile et tout ce qui s'y rapporte dans le dossier 'progc'
    cp program.c makefile progc/
    cd progc
    
    # Compiler le programme C en exécutable en utilisant le makefile
    make all
    
    # Exécuter le programme C et sauvegarder les résultats dans un fichier texte
    ./program > ../demo/results.txt
    
    cd ..
}

# Vérification des arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <data/data.csv> [-d1 | -d2 | -l]"
    exit 1
fi

# Récupération du chemin du fichier
chemin_fichier="$1"
shift

# Vérification de l'option spécifiée
case $1 in
    -d1)
        traitement_d1 "$chemin_fichier"
        ;;
    -d2)
        traitement_d2 "$chemin_fichier"
        ;;
    -l)
        traitement_l "$chemin_fichier"
        ;;
    *)
        echo "Option invalide. Utilisez -d1, -d2 ou -l."
        exit 1
        ;;
esac

