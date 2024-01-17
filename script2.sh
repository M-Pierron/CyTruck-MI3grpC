#!/bin/bash

#TRAITEMENT [D2] : conducteurs et la plus grande distance:

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


	# Trier les trajets par distance décroissante et afficher les 10 premiers avec le nom du conducteur
	echo "Top 10 des conducteur ayant parcouru la plus grande distance totales"
	awk -F ';' '{arr[$2]+=$5; drivers[$2]=$6} END {for (i in arr) printf "%s %.3f\n", drivers[i], arr[i]}' "$fichier" \
	    | sort -t ';' -k2 -nr | head -n 10 \
	    >> résultatd2.txt
