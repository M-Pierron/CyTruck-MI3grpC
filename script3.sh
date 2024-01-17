#!/bin/bash

#TRAITEMENT [L] : les 10 trajets les plus longs :

	# Vérifier si le nombre d'arguments est correct
	if [ "$#" -ne 1 ]; then
	    echo "Usage: $0 <data/data.csv>"
	    exit 1
	fi

	# Récupérer le chemin du fichier depuis le premier argument
	fichier="$1"

	# Vérifier si le fichier existe
	if [ ! -f "$fichier" ]; then
	    echo "Le fichier $fichier n'existe pas."
	    exit 1
	fi

	#Trier les trajets par distances décroissante et afficher les 10 trajets les plus longs dans l'ordre croissant en fonction de leur ID route (identifaint de trajet) 

	echo "Les 10 trajets les plus longs dans l'odre croissant de leur Identifiant de trajet"

	awk -F ';' '{arr[$1]+=$5} END {for (i in arr) printf "%s %.3f\n", i, arr[i]}' "$fichier"\
		| sort -t ';' -k2 -nr | head -n 10 \
		| sort -t ';' -k1 -n | head -n 10  \
		>> résultatl.txt
