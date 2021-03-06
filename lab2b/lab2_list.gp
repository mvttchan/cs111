#! /usr/bin/gnuplot
#
# purpose:
#	generate data reduction graphs for partitioned shared resources
#
# input: lab2b_list.csv
# 	 1. test name
#	 2. # threads
#	 3. # iterations per thread
#	 4. # lists
#	 5. # operations performed
#	 6. run time (ns)
#	 7. run time per operation (ns)
#	 8. average wait for lock (mutex)
#
# output:
#	lab2b_1.png ... throughput vs number of threads for mutex and spin-lock synchronized list operations
#	lab2b_2.png ... mean time per mutex wait and mean time per operation for mutex-synchronized list operations
#	lab2b_3.png ... successful iterations vs threads for each synchronization method
#	lab2b_4.png ... throughput vs number of threads for mutex synchronized partitioned lists
#	lab2b_5.png ... throughput vs number of threads for spin lock synchronized partitioned lists
#

# general plot parameters
set terminal png
set datafile separator ","

# Graph 1: Throughput vs thread count mutex and spin lock
set title "List-1: Throughput vs Thread Count"
set xlabel "Thread Count"
set xrange [0.75:]
set logscale x 2
set ylabel "Throughput"
set logscale y 10
set output 'lab2b_1.png'

# grep this stuff
plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title 'mutex' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title 'spin lock' with linespoints lc rgb 'green'



# Graph 2:
set title "List-2 Mutex wait for lock vs time per operation"
set xlabel "Thread Count"
set xrange [0.75:]
set logscale x 2
set ylabel "Average time"
set logscale y 10
set output 'lab2b_2.png'

# grep this stuff
plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($7) \
     title 'timer per operation' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($8) \
     title 'wait for lock' with linespoints lc rgb 'green'



# Graph 3:
set title "List-3 Successful iterations vs threads, all sync types"
set xlabel "Thread Count"
set xrange [0.75:]
set logscale x 2
set ylabel "Iterations"
set logscale y 10
set output 'lab2b_3.png'

# grep this stuff
plot \
     "< grep -e 'list-id-none,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
     title 'unprotected with yield=id' with points lc rgb 'red', \
     "< grep -e 'list-id-m,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
     title 'mutex with yield=id' with points lc rgb 'green', \
     "< grep -e 'list-id-s,[0-9]*,[0-9]*,4' lab2b_list.csv" using ($2):($3) \
     title 'spin lock with yield=id' with points lc rgb 'blue'



# Graph 4:
set title "List-4 Throughput vs thread count for mutex partitioned lists"
set xlabel "Thread Count"
set xrange [0.75:]
set logscale x 2
set ylabel "Throughput"
set logscale y 10
set output 'lab2b_4.png'

# grep this stuff
plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '1 list' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-m,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '4 lists' with linespoints lc rgb 'green', \
     "< grep -e 'list-none-m,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '8 lists' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-m,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '16 lists' with linespoints lc rgb 'gold'



# Graph 5:
set title "List-5 Throughput vs thread count for spin lock partitioned lists"
set xlabel "Thread Count"
set xrange [0.75:]
set logscale x 2
set ylabel "Throughput"
set logscale y 10
set output 'lab2b_5.png'

# grep this stuff
plot \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '1 list' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-s,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '4 lists' with linespoints lc rgb 'green', \
     "< grep -e 'list-none-s,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '8 lists' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-s,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000/($7)) \
     title '16 lists' with linespoints lc rgb 'gold'