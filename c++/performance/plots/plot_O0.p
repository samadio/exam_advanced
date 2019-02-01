reset
set logscale y 10
set format x "%2.0t{/Symbol \264}10^{%L}"
set xlabel "Number of nodes"
set ylabel "log(time)"
set key right bottom
set title "Time taken by find() functions, -O0."

plot "O0.txt" u 1:2 w lp pointtype 7 ps 0.2 t "Unbalanced BSTree", "" u 1:3 w lp pointtype 7 ps 0.2 t "Balanced BSTree", "" u 1:4 w lp pointtype 7 ps 0.2 t "std::map"
