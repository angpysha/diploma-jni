cmake_minimum_required(VERSION 3.9)
project(raspiinfo)

set(CMAKE_CXX_STANDARD 11)

add_library(raspiinfo SHARED
        io_github_angpysha_diploma_raspberry_Sensors_DHT11.cpp
        io_github_angpysha_diploma_raspberry_Sensors_DHT11.h
        io_github_angpysha_diploma_raspberry_Sensors_BMP180.h
        io_github_angpysha_diploma_raspberry_Sensors_BMP180.cpp
        DHTAdapter.cpp
        DHTAdapter.h DHT11.cpp DHT11.h)
#include_directories("C:\\Program Files\\Java\\jdk1.8.0_144\\include"
#        "C:\\Program Files\\Java\\jdk1.8.0_144\\include\\win32"
#        "C:\\Users\\andre\\wiringPi\\wiringPi\\wiringPi")

include_directories(.
        /mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include
        /mnt/d/Downloads/jdk-8u151-linux-arm32-vfp-hflt/jdk1.8.0_151/include/linux
        WiringPi/wiringPi
        )

#link_directories(
#        /mnt/d/IdeaProjects/com.andrewpetrowski.diploma.raspberry/src/main/jni/WiringPi/wiringPi/cmake-build-debug-arm
#        /mnt/d/IdeaProjects/com.andrewpetrowski.diploma.raspberry/src/main/jni/WiringPi/devLib/cmake-build-debug-arm
#)


target_compile_options(raspiinfo PRIVATE -fPIC)
find_library(WIRINGPI wiringPi)
find_library(WIRINGPIDEV wiringPiDev HINTS WiringPi/devLib)
target_link_libraries(raspiinfo ${CMAKE_CURRENT_SOURCE_DIR}/WiringPi/wiringPi/libwiringPi.so.2.44
        ${CMAKE_CURRENT_SOURCE_DIR}/WiringPi/devLib/libwiringPiDev.so.2.44)