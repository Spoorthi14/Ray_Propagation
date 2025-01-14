set grid
set yrange [-1500.0:100.0]
set xrange [0.0:4000.0]
unset key
set tics font "Courier,22"
set xlabel "Horizontal Distance (m)" offset 0,-2 font "Courier,26"
set ylabel "Vertical Distance (m)" offset -4,0 font "Courier,26"
set title "Index: Fit to Spice Core, angle 35" font "Courier,18"
set lmargin 14.0
set rmargin 9.0
set bmargin 7.0
set tmargin 3.0
set style line 1 linecolor -1 linewidth 0.8 dashtype 2 pointtype 2 pointsize default pointinterval 1
set arrow 1 from 0,-100 to 4000,-100 nohead ls 1
set arrow 2 from 0,-90 to 4000,-90 nohead ls 1
set arrow 3 from 0,-75 to 4000,-75 nohead ls 1
set arrow 4 from 0,-70 to 4000,-70 nohead ls 1
set arrow 5 from 0,-65 to 4000,-65 nohead ls 1
set arrow 6 from 0,-60 to 4000,-60 nohead ls 1
set terminal postscript color enhanced
set output "DiffuseSpiceModels.eps"

plot for [i=0:2999] 'data/propagation_path_'.i.'.dat' w l lw 0.2 lc rgb "#999999"
