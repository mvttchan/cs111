#!/bin/bash



#lab2b_1.png and lab2b_2.png
./lab2_list --iterations=1000 --sync=m --threads=1 > lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=2 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=4 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=8 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=12 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=16 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=m --threads=24 >> lab2b_list.csv

./lab2_list --iterations=1000 --sync=s --threads=1 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=2 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=4 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=8 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=12 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=16 >> lab2b_list.csv
./lab2_list --iterations=1000 --sync=s --threads=24 >> lab2b_list.csv



#lab2b_3.png
./lab2_list --yield=id --lists=4 --threads=1 --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=4 --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=8 --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=12 --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=16 --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --iterations=16 >> lab2b_list.csv


./lab2_list --yield=id --lists=4 --threads=1 --sync=s --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=s --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=s --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=s --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=s --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=4 --sync=s --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=s --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=s --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=s --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=s --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=8 --sync=s --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=s --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=s --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=s --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=s --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=12 --sync=s --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=s --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=s --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=s --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=s --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=16 --sync=s --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=s --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=s --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=s --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=s --iterations=16 >> lab2b_list.csv


./lab2_list --yield=id --lists=4 --threads=1 --sync=m --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=m --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=m --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=m --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=1 --sync=m --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=4 --sync=m --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=m --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=m --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=m --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=4 --sync=m --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=8 --sync=m --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=m --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=m --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=m --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=8 --sync=m --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=12 --sync=m --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=m --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=m --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=m --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=12 --sync=m --iterations=16 >> lab2b_list.csv

./lab2_list --yield=id --lists=4 --threads=16 --sync=m --iterations=1 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=m --iterations=2 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=m --iterations=4 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=m --iterations=8 >> lab2b_list.csv
./lab2_list --yield=id --lists=4 --threads=16 --sync=m --iterations=16 >> lab2b_list.csv



#lab2b_4-png
./lab2_list --iterations=1000 --threads=1 --lists=4 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=1 --lists=8 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=1 --lists=16 --sync=m >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=2 --lists=4 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=2 --lists=8 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=2 --lists=16 --sync=m >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=4 --lists=4 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=4 --lists=8 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=4 --lists=16 --sync=m >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=8 --lists=4 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=8 --lists=8 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=8 --lists=16 --sync=m >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=12 --lists=4 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=12 --lists=8 --sync=m >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=12 --lists=16 --sync=m >> lab2b_list.csv



#lab2b_5.png
./lab2_list --iterations=1000 --threads=1 --lists=4 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=1 --lists=8 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=1 --lists=16 --sync=s >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=2 --lists=4 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=2 --lists=8 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=2 --lists=16 --sync=s >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=4 --lists=4 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=4 --lists=8 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=4 --lists=16 --sync=s >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=8 --lists=4 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=8 --lists=8 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=8 --lists=16 --sync=s >> lab2b_list.csv

./lab2_list --iterations=1000 --threads=12 --lists=4 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=12 --lists=8 --sync=s >> lab2b_list.csv
./lab2_list --iterations=1000 --threads=12 --lists=16 --sync=s >> lab2b_list.csv
