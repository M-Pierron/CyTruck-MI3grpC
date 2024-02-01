#!/bin/bash
set style histogram clustered
set style data histograms
set style fill solid
set datafile separator ";"

set boxwidth 0.4
set xrange[0.5:*]
set yrange [0:*]
set style histogram gap 5
set xtic rotate by -45
set terminal png size 800,1000



set xlabel "Villes"
set ylabel "Nb Routes"
set title "Option -l"

set terminal png 
set output 'graphiquet.png'
plot "-t.txt" using ($0):2 with boxes lc rgb "#32D365",'' using ($0+0.2):3 with boxes lc rgb "#3D9E5C" notitle