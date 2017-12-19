# ![](https://mycloset.tech/wp-content/uploads/2017/02/1488108204_raspberry.png) diploma-jni
This repositry contains C++ code to access gpio with the help of wiringPi library. 
With the help of this one you can measure humidity and temperature
using DHT11 sensor

## Getting started
This instrunctions can help you to compile this library

### Requirements
#### If you compile on Raspberry Pi
- wiringPi library (for more info see [this](http://wiringpi.com/download-and-install/))

- JDK8 

#### If you are using Linux based PC
- Cross compiler (I use [linaro](https://www.linaro.org/downloads/))
- Build packages.
    
    For Ubuntu:
    
    ``$ sudo apt install build-essentials``
 
 - JDK8 for ARM
 ### Installation
 
 #### If you use Raspbery Pi
 1. Compile library
 
 ``$ cd yourfolderpath``
 
 ``$ make rasp``
 
 2. Copy library to convenient place or set ldlib
 
 #### If you use PC
 1. Cross compile wiringPi library
 
    1. Clone library sources from github
    
         ``$ git clone git://git.drogon.net/wiringPi``
    
    2. Compile wiringPi library
     
        You should compile wiringPi and wiringPiDev libraries. 
    
        1. Compile wiringPi library
            
            1. In terminal go to cloned folder
            
            2. Navigate to wiringPi folder
            
            2. Open Makefile and find CC line
            
            3. Replace it by your cross compiler gcc
            
            **Example**
            
              ``CC = gcc``
            
            to
            
              ``CC = ~/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc``
            
            4. Execute
            
                 ``$ make``
                
        2. Compile wiringPiDev library
            
            1. Navigate to devLib folder 
            
            2. Replace it by your cross compiler gcc
            
            3. Find INCLUDE and add -I../wiringPi
            
            4. Execute 
            
                ``$ make``
                
 2. Compile JNI project 
        
     1. Go to root of this project
        
     2. Set environment variables
        
        1. Set JAVAINCLUDE variable 
                
             ``$ export JAVAINCLUDE="-I/your_downloaded_arm_jdk_folder_path/include -I/your_downloaded_arm_jdk_folder_path/include/linux``

        2. Set cross compile variable
            
             ``$ export CXC="your_cross_compile_path/bin/arm-linux-gnueabihf-g++"``
                
             ``$ export CC="your_cross_compile_path/bin/arm-linux-gnueabihf-gcc"``
                
        3. Linker flags 
            
            ``$ export LINKERINCLUDE="-Lyour_wiring_pi_binary_path -Lyour_wiring_pi_dev_lib_binary_path" -l:libname -l:devlibname``
            
        4. Execute 
            
             ``$ make``
                     

