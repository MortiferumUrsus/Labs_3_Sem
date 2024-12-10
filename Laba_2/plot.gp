set terminal png size 800,600
set output 'performance.png'
set title "Sorting Performance"
set xlabel "Data Size"
set ylabel "Time (ms)"
set grid
set key outside
plot "performance_tests.csv" using 2:3 with linespoints title columnheader(1)
