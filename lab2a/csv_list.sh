#!/bin/bash

#Name: Matthew Chan
#Email: matthew_2185@yahoo.com
#ID: 805291212

#Part 1
./lab2_list --iterations=10 > lab2_list.csv
./lab2_list --iterations=100 >> lab2_list.csv
./lab2_list --iterations=1000 >> lab2_list.csv
./lab2_list --iterations=10000 >> lab2_list.csv
./lab2_list --iterations=20000 >> lab2_list.csv


#Part 2 w/o yield
./lab2_list --threads=2 --iterations=1 >> lab2_list.csv
./lab2_list --threads=2 --iterations=10 >> lab2_list.csv
./lab2_list --threads=2 --iterations=100 >> lab2_list.csv
./lab2_list --threads=2 --iterations=1000 >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 >> lab2_list.csv
./lab2_list --threads=4 --iterations=10 >> lab2_list.csv
./lab2_list --threads=4 --iterations=100 >> lab2_list.csv
./lab2_list --threads=4 --iterations=1000 >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 >> lab2_list.csv
./lab2_list --threads=8 --iterations=10 >> lab2_list.csv
./lab2_list --threads=8 --iterations=100 >> lab2_list.csv
./lab2_list --threads=8 --iterations=1000 >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 >> lab2_list.csv
./lab2_list --threads=12 --iterations=10 >> lab2_list.csv
./lab2_list --threads=12 --iterations=100 >> lab2_list.csv
./lab2_list --threads=12 --iterations=1000 >> lab2_list.csv


#Part 2 w/ yield i
./lab2_list --threads=2 --iterations=1 --yield=i >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=i >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=i >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=i >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=i >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=i >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=i >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=i >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=i >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=i >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=i >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=i >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=i >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=i >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=i >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=i >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=i >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=i >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=i >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=i >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=i >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=i >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=i >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=i >> lab2_list.csv


#Yield d
./lab2_list --threads=2 --iterations=1 --yield=d >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=d >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=d >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=d >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=d >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=d >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=d >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=d >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=d >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=d >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=d >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=d >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=d >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=d >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=d >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=d >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=d >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=d >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=d >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=d >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=d >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=d >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=d >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=d >> lab2_list.csv


#Yield il
./lab2_list --threads=2 --iterations=1 --yield=il >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=il >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=il >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=il >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=il >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=il >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=il >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=il >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=il >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=il >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=il >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=il >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=il >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=il >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=il >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=il >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=il >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=il >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=il >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=il >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=il >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=il >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=il >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=il >> lab2_list.csv


#Yield dl
./lab2_list --threads=2 --iterations=1 --yield=dl >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=dl >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=dl >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=dl >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=dl >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=dl >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=dl >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=dl >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=dl >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=dl >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=dl >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=dl >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=dl >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=dl >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=dl >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=dl >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=dl >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=dl >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=dl >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=dl >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=dl >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=dl >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=dl >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=dl >> lab2_list.csv


#Part 3 Sync m yield i
./lab2_list --threads=2 --iterations=1 --yield=i --sync=mm >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=i --sync=mm >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=i --sync=mm >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=i --sync=mm >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=i --sync=mm >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=i --sync=mm >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=i --sync=m >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=i --sync=m >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=i --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab2_list.csv


#Sync m yield d
./lab2_list --threads=2 --iterations=1 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=d --sync=m >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=d --sync=m >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=d --sync=m >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=d --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab2_list.csv


#Sync m yield il
./lab2_list --threads=2 --iterations=1 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=il --sync=m >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=il --sync=m >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=il --sync=m >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=il --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv


#Sync m yield dl
./lab2_list --threads=2 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=dl --sync=m >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=dl --sync=m >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=dl --sync=m >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv


#Part 3 Sync s yield i
./lab2_list --threads=2 --iterations=1 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=i --sync=s >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=i --sync=s >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=i --sync=s >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=i --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab2_list.csv


#Sync s yield d
./lab2_list --threads=2 --iterations=1 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=d --sync=s >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=d --sync=s >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=d --sync=s >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=d --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab2_list.csv


#Sync s yield il
./lab2_list --threads=2 --iterations=1 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=il --sync=s >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=il --sync=s >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=il --sync=s >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=il --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv


#Sync s yield dl
./lab2_list --threads=2 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=32 --yield=dl --sync=s >> lab2_list.csv

./lab2_list --threads=4 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=32 --yield=dl --sync=s >> lab2_list.csv

./lab2_list --threads=8 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=32 --yield=dl --sync=s >> lab2_list.csv

./lab2_list --threads=12 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv


#Part 4 Sync
./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv
./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv

./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv
./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv



