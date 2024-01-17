#!/bin/bash

#TRAITEMENT [D1] : conducteurs avec le plus de trajets :

	if [ "$#" -eq 0 ]; then
	  echo "Usage: $0 <data/data.csv>"
	  exit 1
	fi

	chemin_fichier="$1"

	# Obtient le nom des conducteurs avec le plus grand nombre de trajets
	conducteurs_trajets=$(tail -n +2 "$chemin_fichier" | awk -F';' '{count[$6]++} END {for (driver in count) print count[driver], driver}' | sort -nr)

	# Affiche les trois conducteurs avec le plus grand nombre de trajets
	echo "Top 10 conducteurs avec le plus grand nombre de trajets :"
	echo "$conducteurs_trajets" | head -n 10   \
	>> résultatd1.txt





















