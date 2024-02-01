#!/bin/bash
set datafile separator ";"
set style data histogram 
set style fill solid

set boxwidth 0.75
set xrange[0.5:*]
set yrange [0:*]
set style histogram gap 5

set xlabel "Route ID"
set ylabel "Distance (KM)"
set title "Option -l"

set terminal png 
set output 'graphique-l.png'
plot "traitl" using 2:xtic(1) with boxes lc rgb "skyblue"