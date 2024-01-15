#!/bin/bash

## -- Creation des dossiers et deplacement des programmes C et tout ce qui s'y rapporte dans le dossier 'progc' 
cd ..
mkdir -p CyTruck-MI3grpC
cd CyTruck-MI3grpC
mkdir -p temp
mkdir -p images
mkdir -p data
mkdir -p progc
mkdir -p demo
cd ..
mv makefile *.c CyTruck-MI3grpC/progc

## -- Verification du nombre d'argument(s)
if [ "$#" -lt 2 ]; then
    aide
fi

fichier_arg = "$1"
if [ ! -f "$fichier_arg" ]; then
    echo "Le fichier place en parametre n'existe pas."
    aide
    exit 1
fi

## -- Le fichier de donnees d entree devra etre copie dans un dossier data
cp data.csv CyTruck-MI3grpC/data


## -- Verification si -h est present dans le(s) argument(s) place(s) en parametre
for argument in "$@"; do 
    if [ "$argument" == "-h" ]; then
        aide
        exit 1
    fi 
done

function aide() {
    ## -- Fonction qui montre le manuel d'utilisation, avec les options possibles
    echo "Utilisation : Prendre en parametres le chemin du fichier CSVd entree contenant les donnees des trajets routiers effectues, et les choix des traitements a faire"
    echo "Exemple : ... "
    echo "Choix des traitements :"
    echo "-d1   conducteurs avec le plus de trajets"
    echo "-d2   conducteurs et la plus grande distance"s
    echo "-l    les 10 trajets les plus longs"
    echo "-t    les 10 villes les plus traversees"
    echo "-s    statistiques sur les etapes"
}


for argument in "$@"; do
if [ "$argument" == "-d1" ]; then
    ## script d1
    ## script d1
fi
if [ "$argument" == "-d2" ]; then
    ## script d2
    ## script d2
fi
if [ "$argument" == "-l" ]; then
    ## script l
    ## script l
fi
if [ "$argument" == "-t" ]; then
    ## script t
    ## script t
fi
if [ "$argument" == "-s" ]; then
    ## script s
    ## script s
fi
