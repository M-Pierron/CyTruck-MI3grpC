#!/bin/bash
set datafile separator ";"
set size ratio 1
set style data histogram 
set style histogram rowstacked
set style fill solid

set boxwidth 0.75
set xtic rotate by 90
set terminal png size 800,800
set y2range[0:*]
unset ytics
unset x2tics

set xtics nomirror offset 0,-11
set y2tics rotate by 45

set xlabel "Conducteurs" offset 0,-11
set xlabel rotate by 180
set y2label "Distance(km)" offset 1,0
set ylabel "Option -d2"
set title " "

set terminal png 
set output 'graphique-d2.png'
plot "resultatd2.txt" using 2:xtic(1) axes x1y2 lc rgb "skyblue" notitle

