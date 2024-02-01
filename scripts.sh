#!/bin/bash
set datafile separator ";"
set xtics nomirror offset -3,-2.5
set xtic rotate by 45
set terminal png size 1600,800
set xrange[0:*]

set xlabel "Route ID" offset 0,-3
set ylabel "Distance (KM)"
set title "Option -s" 

set terminal png 
set output 'graphique-s.png'
plot "data_s.dat" using ($1-1):5:($5-$6):xtic(2) with filledcurve lc rgb "#32D365", '' using 4 smooth mcspline lw 2