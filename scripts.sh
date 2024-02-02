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
set output 'graphs.png'
plot "resultats.txt" using 0:2:3 with filledcurve fc rgb "#32D365" title "Distance Max/Min", "resultats.txt" using 0:4:xticlabels(1) with lines linestyle 2 title "Distance moyenne (Km)"
