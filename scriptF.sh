#!/bin/bash

# -- Création des dossiers --
cd CyTruck-MI3grpC-main
mkdir -p CyTruck-MI3grpC

# -- Vérification et création du dossier images s'il n'existe pas --
if [ ! -d "CyTruck-MI3grpC/data" ]; then
    mkdir -p CyTruck-MI3grpC/data
fi

# -- Vérification et création du dossier temp s'il n'existe pas --
if [ ! -d "CyTruck-MI3grpC/temp" ]; then
    mkdir -p CyTruck-MI3grpC/temp
else
    # -- Le dossier temp existe, donc nous le vidons --
    rm -rf CyTruck-MI3grpC/temp/*
fi

# -- Vérification et création du dossier images s'il n'existe pas --
if [ ! -d "CyTruck-MI3grpC/images" ]; then
    mkdir -p CyTruck-MI3grpC/images
fi

# -- Vérification et création du dossier progc s'il n'existe pas --
if [ ! -d "CyTruck-MI3grpC/progc" ]; then
    mkdir -p CyTruck-MI3grpC/progc
    # -- Déplacement des programmes C et des fichiers associés dans le dossier progc --
    mv headers.h traitements.c route.c calculs.c makefile CyTruck-MI3grpC/progc/
    mv headert.h traitementt.c ville.c calcult.c etape.c makefile CyTruck-MI3grpC/progc/
fi

# -- Vérification et création du dossier demo s'il n'existe pas --
if [ ! -d "CyTruck-MI3grpC/demo" ]; then
    mkdir -p CyTruck-MI3grpC/demo
fi

# -- Déplacement du fichier data.csv dans le dossier data --
cp data.csv CyTruck-MI3grpC/data/

# -- Définir la locale pour le format numérique --
export LC_NUMERIC="en_US.UTF-8"

# -- Fonction pour vérifier la présence de l'exécutable C --
verification_executable_s() {
    if [ ! -f "CyTruck-MI3grpC/progc/execs" ]; then
        # -- Compiler le programme C en exécutable en utilisant le makefile --
        cd CyTruck-MI3grpC/progc || exit
        make alls
        cd ..
        # -- Vérifier que la compilation s'est bien déroulée --
        if [ $? -ne 0 ]; then
            echo "Erreur lors de la compilation du programme C."
            exit 1
        fi
        
        cd ..
    fi
}

# -- Fonction pour vérifier la présence de l'exécutable C --
verification_executable_t() {
    if [ ! -f "CyTruck-MI3grpC/progc/execs" ]; then
        # -- Compiler le programme C en exécutable en utilisant le makefile --
        cd CyTruck-MI3grpC/progc || exit
        make allt
        cd ..
        # -- Vérifier que la compilation s'est bien déroulée --
        if [ $? -ne 0 ]; then
            echo "Erreur lors de la compilation du programme C."
            exit 1
        fi
        
        cd ..
    fi
}

# -- Définition des fonctions pour chaque traitement --
traitement_d1() {
    fichier="$1"
    # -- Obtient le nom des conducteurs avec le plus grand nombre de trajets --
    conducteurs_trajets=$(awk -F';' 'NR > 1 {if (!seen[$6,$1]) {count[$6]++}; seen[$6,$1]=1} END {for (driver in count) print count[driver], driver}' "$fichier" | sort -nr)
    # -- Affiche les conducteurs avec le plus grand nombre de trajets différents --
    echo "Top conducteurs avec le plus grand nombre de trajets différents :"
    echo "$conducteurs_trajets"| awk '{print $1 ";" $2, $3}' | head -n 10 > resultatd1.txt
    # -- Exécute le script Gnuplot --
    start_time=$(date +%s)
    gnuplot scriptd1.sh
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "Durée du traitement : $duration secondes."
    convert -rotate 90 graphique-d1.png graphd1.png
    mv graphd1.png CyTruck-MI3grpC/images/
    rm graphique-d1.png
    mv resultatd1.txt CyTruck-MI3grpC/temp/
    
}

traitement_d2() {
    fichier="$1"
    # -- Trier les trajets par distance décroissante et afficher les 10 premiers avec le nom du conducteur --
    echo "Top 10 des conducteur ayant parcouru la plus grande distance totales"
    start_time=$(date +%s)
    awk -F';' '{arr[$6]+=$5} END {for (driver in arr) printf "%s;%.2f\n", driver, arr[driver]}' $fichier | sort -t ';' -k2 -nr | head -n 10 > resultatd2.txt
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "Durée du traitement : $duration secondes."
    # -- Exécute le script Gnuplot --
    gnuplot scriptd2.sh
    convert -rotate 90 graphique-d2.png graphd2.png
    mv graphd2.png CyTruck-MI3grpC/images/
    rm graphique-d2.png
    mv resultatd2.txt CyTruck-MI3grpC/temp/  
}

traitement_l() {
    fichier="$1"
    #-- Trier les trajets par distances décroissante et afficher les 10 trajets les plus longs dans l'ordre croissant en fonction de leur ID route (identifaint de trajet) --
    echo "Les 10 trajets les plus longs dans l'ordre croissant de leur Identifiant de trajet"
    start_time=$(date +%s)
    awk -F ';' 'NR > 1 {arr[$1]+=$5} END {for (i in arr) printf "%s;%.3f\n", i, arr[i]}' "$fichier" \
    | sort -t ';' -k2 -nr | head -n 10 | sort -t ';' -k1 -n > resultatl.txt
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "Durée du traitement : $duration secondes."
    # -- Exécute le script Gnuplot --
    gnuplot scriptl.sh
    mv graphl.png CyTruck-MI3grpC/images/
    mv resultatl.txt CyTruck-MI3grpC/temp/   
}

traitement_s() {

    verification_executable_s
    
    cd CyTruck-MI3grpC/progc 
    start_time=$(date +%s)
    ./execs > ../../resultats.txt
    make clean
    cd ../..
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "Durée du traitement : $duration secondes."
    # -- Exécute le script Gnuplot --
    gnuplot scripts.sh
    mv graphs.png CyTruck-MI3grpC/images/
    mv resultats.txt CyTruck-MI3grpC/temp/
}

traitement_t() {
    
    verification_executable_t
    
    cd CyTruck-MI3grpC/progc 
    start_time=$(date +%s)
    ./exect > ../../resultatt.txt
    make clean
    cd ../..
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "Durée du traitement : $duration secondes."
    # -- Exécute le script Gnuplot --
    gnuplot scriptt.sh
    mv grapht.png CyTruck-MI3grpC/images/
    mv resultatt.txt CyTruck-MI3grpC/temp/
    
}

# -- Affichage de l'aide --
afficher_aide() {
    echo "Usage: $0 <data.csv> [-d1 | -d2 | -l | -s | -t]"
    echo "Options:"
    echo "  -d1 : Effectue le traitement D1."
    echo "  -d2 : Effectue le traitement D2."
    echo "  -l  : Effectue le traitement L."
    echo "  -s  : Effectue le traitement S."
    echo "  -t  : Effectue le traitement T."
    echo "  -h  : Affiche cette aide."
}


# -- Vérification des arguments --
if [ "$#" -lt 2 ]; then
    afficher_aide
    exit 1
fi

# -- Vérification de l'option -h --
if [ "$1" == "-h" ]; then
    afficher_aide
    exit 0
fi


# -- Récupération du chemin du fichier --
chemin_fichier="$1"
shift

# -- Vérification de l'option spécifiée --
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
    -s)
        traitement_s "$chemin_fichier"
        ;;
    -t)
        traitement_t "$chemin_fichier"
        ;;
    *)
        echo "Option invalide. Utilisez -d1, -d2 ou -l."
        exit 1
        ;;
esac

# -- Stockage du temps d'exécution dans le dossier demo --
echo "$duration secondes" > CyTruck-MI3grpC/demo/duration.txt
