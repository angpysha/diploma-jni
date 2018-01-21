#This 
CC ?= /mnt/d/Downloads/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CXC ?= /mnt/d/Downloads/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
JAVAINCLUDE ?= -I/mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include/ -I/mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include/linux
WIRINGPIINCLUDE ?= -I/mnt/d/IdeaProjects/wiringPi/wiringPi
LINKERINCLUDE ?= -LWiringPi/wiringPi -LWiringPi/devLib -l:libwiringPi.so.2.44 -l:libwiringPiDev.so.2.44 -lm
CFLAGS ?= -c -fpic

CCE ?= g++
JAVAINCLUDEE ?= -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/ -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/linux
LINKERINCLUDEE ?= -lwiringPi -lwiringPiDev


all: io_github_angpysha_diploma_raspberry_Sensors_DHT11.cpp io_github_angpysha_diploma_raspberry_Sensors_DHT11.h DHTAdapter.cpp DHTAdapter.h
		#Compilation process Embedded
		#Compile DHTAdapter.o
		@$(CXC) -std=c++11 $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE)  DHTAdapter.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o
		@$(CXC) -std=c++11 $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE)  io_github_angpysha_diploma_raspberry_Sensors_DHT11.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_BMP180.o
		@$(CXC) -std=c++11 $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE) io_github_angpysha_diploma_raspberry_Sensors_BMP180.cpp
		#Compile BMP180.o
		@$(CXC) -std=c++11 $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE) BMP180.cpp
		#Compile DHT11.o
		@$(CXC) -std=c++11 $(CFLAGS) $(JAVAINCLUDE) $(WIRINGPIINCLUDE) DHT11.cpp
		#Linking
		@$(CXC) -std=c++11 -shared -fPIC -o libraspiinfo.so io_github_angpysha_diploma_raspberry_Sensors_DHT11.o DHTAdapter.o io_github_angpysha_diploma_raspberry_Sensors_BMP180.o BMP180.o DHT11.o $(LINKERINCLUDE)
		
clean: 
	#Cleanup project
	@rm *.o
	@rm *.so

rasp: io_github_angpysha_diploma_raspberry_Sensors_DHT11.cpp io_github_angpysha_diploma_raspberry_Sensors_DHT11.h DHTAdapter.cpp DHTAdapter.h
		#Compilation process
		#Compile DHTAdapter.o
		@$(CCE) $(CFLAGS) $(JAVAINCLUDEE)  DHTAdapter.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o
		@$(CCE) $(CFLAGS) $(JAVAINCLUDEE)  com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp
		#Compile com_andrewpetrowski_diploma_raspberry_Sensors_BMP180.o
		#Linking
		@$(CCE) -shared -fPIC -o libdhtdata.so com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.o DHTAdapter.o $(LINKERINCLUDEE)