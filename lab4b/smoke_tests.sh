#!/bin/bash

#NAME: Matthew Chan
#EMAIL: matthew_2185@yahoo.com
#ID: 805291212

echo | ./lab4b --bogus &> /dev/null
if [ $? -ne 1 ]
then
    echo "bogus test failed"
else
    echo ""
fi

./lab4b --period=10 --scale=F --log=lol <<-EOF
SCALE=F
SCALE=C
PERIOD=100
STOP
START
LOG poop haha
BOGUS
OFF
EOF
if [ $? -ne 0 ]
then
    echo "Exit code not 0"
else
    echo ""
fi

if [ ! -s lol ]
then
    echo "lolfile not made, hahah"
else
    echo ""
fi

grep "SCALE=F" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Scale F not in log"
else
    echo ""
fi

grep "SCALE=C" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Scale C not in log"
else
    echo ""
fi

grep "PERIOD=100" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Period not in log"
else
    echo ""
fi

grep "STOP" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Stop not in log"
else
    echo ""
fi

grep "START" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Start not in log"
else
    echo ""
fi

grep "LOG poop haha" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "LOG poop haha not in log"
else
    echo ""
fi

grep "BOGUS" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Bogus not in log"
else
    echo ""
fi

grep "OFF" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Off not in log"
else
    echo ""
fi

grep "SHUTDOWN" lol &> /dev/null; \
if [ $? -ne 0 ]
then
    echo "Shutdown not in log"
else
    echo ""
fi

rm -f lol
