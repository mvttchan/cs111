#!/bin/bash

#NAME: Matthew Chan
#EMAIL: matthew_2185@yahoo.com
#ID: 805291212

#Number of threads to consistently fail a set of iterations
#Range of number of threads tested taken from the yield-none test cases
./lab2_add --threads=2 --iterations=100 > lab2_add.csv
./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
./lab2_add --threads=12 --iterations=100 >> lab2_add.csv

./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=12 --iterations=1000 >> lab2_add.csv

./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv

./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
./lab2_add --threads=4 --iterations=100000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv
./lab2_add --threads=12 --iterations=100000 >> lab2_add.csv

#Threads 2,4,8,12 Iterations 10,20,40,80,100,1k,10k,100k, with yield
./lab2_add --threads=2 --iterations=10 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=20 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=40 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=80 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv

./lab2_add --threads=4 --iterations=10 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=20 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=40 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=80 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=4 --iterations=100000 --yield >> lab2_add.csv

./lab2_add --threads=8 --iterations=10 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=20 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=40 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=80 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv

./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv

#Comparing yield and non yield for threads 2 and 8 iterations 100,1k,10k,100k
./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv

./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv

#Single thread, average cost per operation no yield
./lab2_add --threads=1 --iterations=10 >> lab2_add.csv
./lab2_add --threads=1 --iterations=20 >> lab2_add.csv
./lab2_add --threads=1 --iterations=40 >> lab2_add.csv
./lab2_add --threads=1 --iterations=80 >> lab2_add.csv
./lab2_add --threads=1 --iterations=100 >> lab2_add.csv
./lab2_add --threads=1 --iterations=1000 >> lab2_add.csv
./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=1 --iterations=100000 >> lab2_add.csv

#Sync with yield, make sure it doesn't fail
./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> lab2_add.csv

./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> lab2_add.csv
./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> lab2_add.csv
./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> lab2_add.csv
./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> lab2_add.csv

./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> lab2_add.csv

#No yield, large (10000) iterations, all four run types, threads 1,2,4,8,12
./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv

./lab2_add --threads=1 --iterations=10000 --sync=m >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 --sync=m >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --sync=m >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --sync=m >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv

./lab2_add --threads=1 --iterations=10000 --sync=s >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 --sync=s >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --sync=s >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --sync=s >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv

./lab2_add --threads=1 --iterations=10000 --sync=c >> lab2_add.csv
./lab2_add --threads=2 --iterations=10000 --sync=c >> lab2_add.csv
./lab2_add --threads=4 --iterations=10000 --sync=c >> lab2_add.csv
./lab2_add --threads=8 --iterations=10000 --sync=c >> lab2_add.csv
./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv
