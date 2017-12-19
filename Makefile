#This 
CC ?= /mnt/d/Downloads/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CXC ?= /mnt/d/Downloads/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
JAVAINCLUDE ?= -I/mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include/ -I/mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include/linux
WIRINGPIINCLUDE ?= -I/mnt/d/IdeaProjects/wiringPi/wiringPi
LINKERINCLUDE ?= -L/mnt/c/Users/andre/wiringPi/wiringPi/wiringPi -L/mnt/c/Users/andre/wiringPi/wiringPi/devLib -l:libwiringPi.so.2.44 -l:libwiringPiDev.so.2.44
CFLAGS ?= -c -fpic

CCE ?= g++
JAVAINCLUDEE ?= -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/ -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/linux
LINKERINCLUDEE ?= -lwiringPi -lwiringPiDev


all: com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.h DHTAdapter.cpp DHTAdapter.h
		#Compilation process Embedded
		#Compile DHTAdapter.o
		@$(CXC) $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE)  DHTAdapter.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o
		@$(CXC) $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE)  com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp
		#Linking
		@$(CXC) -shared -fPIC -o libdhtdata.so com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o DHTAdapter.o $(LINKERINCLUDE)
		
clean: 
	#Cleanup project
	@rm *.o
	@rm libdhtdata.so

rasp: com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.h DHTAdapter.cpp DHTAdapter.h
		#Compilation process
		#Compile DHTAdapter.o
		@$(CCE) $(CFLAGS) $(JAVAINCLUDEE)  DHTAdapter.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o
		@$(CCE) $(CFLAGS) $(JAVAINCLUDEE)  com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp
		#Linking
		@$(CCE) -shared -fPIC -o libdhtdata.so com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o DHTAdapter.o $(LINKERINCLUDEE)