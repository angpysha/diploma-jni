#!/bin/bash
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi/wiringPi
sed -i 's#.$(VERSION)##g' Makefile 
make
cd ../devLib
sed -i 's#-I.#-I. -I../wiringPi#g' Makefile
sed -i 's#.$(VERSION)##g' Makefile 
make
cd ../..
export JAVAINCLUDE="-I/usr/lib/jvm/java-8-openjdk-amd64/include/ -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux/"
export CC=gcc
export CXC=g++
export WIRINGPIINCLUDE="-IWiringPi/wiringPi"
export LINKERINCLUDE="-LWiringPi/wiringPi -LWiringPi/devLib -l:libwiringPi.so -l:libwiringPiDev.so"
make