#!/bin/bash

## -- Creation des dossiers et deplacement des programmes C et tout ce qui s'y rapporte dans le dossier 'progc' 
cd ~
mkdir -p CyTruck-MI3grpC
cd CyTruck-MI3grpC
mkdir -p temp
mkdir -p images
mkdir -p data
mkdir -p progc
mkdir -p demo
cd ~
mv makefile *.c CyTruck-MI3grpC/progc

## -- Verification du nombre d'argument(s)
if [ "$#" -lt 2 ]; then
    aide
fi

fichier= "$1"
if [ ! -f "$fichier" ]; then
	    echo "Le fichier $fichier n'existe pas."
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

	# Obtient le nom des conducteurs avec le plus grand nombre de trajets
	conducteurs_trajets=$(tail -n +2 "$fichier" | awk -F';' '{count[$6]++} END {for (driver in count) print count[driver], driver}' | sort -nr)

	# Affiche les trois conducteurs avec le plus grand nombre de trajets
	echo "Top 10 conducteurs avec le plus grand nombre de trajets :"
	echo "$conducteurs_trajets" | head -n 10   \
	>> résultatd1.txt
fi
if [ "$argument" == "-d2" ]; then
#TRAITEMENT [D2] : conducteurs et la plus grande distance:

	# Trier les trajets par distance décroissante et afficher les 10 premiers avec le nom du conducteur
	echo "Top 10 des conducteur ayant parcouru la plus grande distance totales"
	awk -F ';' '{arr[$2]+=$5; drivers[$2]=$6} END {for (i in arr) printf "%s %.3f\n", drivers[i], arr[i]}' "$fichier" \
	    | sort -t ';' -k2 -nr | head -n 10 \
	    >> résultatd2.txt
fi
if [ "$argument" == "-l" ]; then
	#Trier les trajets par distances décroissante et afficher les 10 trajets les plus longs dans l'ordre croissant en fonction de leur ID route (identifaint de trajet) 

	echo "Les 10 trajets les plus longs dans l'odre croissant de leur Identifiant de trajet"

	awk -F ';' '{arr[$1]+=$5} END {for (i in arr) printf "%s %.3f\n", i, arr[i]}' "$fichier"\
		| sort -t ';' -k2 -nr | head -n 10 \
		| sort -t ';' -k1 -n | head -n 10  \
		>> résultatl.txt
fi
if [ "$argument" == "-t" ]; then
    ## script t
    ## script t
fi
if [ "$argument" == "-s" ]; then
    ## script s
    ## script s
fi
