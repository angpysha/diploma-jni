cmake_minimum_required(VERSION 3.9)
project(raspiinfo)

set(CMAKE_CXX_STANDARD 11)

include_directories(.
        /mnt/e/Diploma/toolchains/jdk1.8.0_172/include
        /mnt/e/Diploma/toolchains/jdk1.8.0_172/include/linux
        wiringPi/wiringPi
        )

find_library(WIRINGPI wiringPi
        HINTS wiringPi/wiringPi
        NO_CMAKE_FIND_ROOT_PATH)


add_definitions(-Wall -fPIC)

add_library(raspiinfo SHARED
        io_github_angpysha_diploma_raspberry_Sensors_DHT11.cpp
        io_github_angpysha_diploma_raspberry_Sensors_DHT11.h
        io_github_angpysha_diploma_raspberry_Sensors_BMP180.h
        io_github_angpysha_diploma_raspberry_Sensors_BMP180.cpp
        DHTAdapter.cpp
        DHTAdapter.h DHT11.cpp DHT11.h BMP180.cpp BMP180.h)
#include_directories("C:\\Program Files\\Java\\jdk1.8.0_144\\include"
#        "C:\\Program Files\\Java\\jdk1.8.0_144\\include\\win32"
#        "C:\\Users\\andre\\wiringPi\\wiringPi\\wiringPi")



#link_directories(
#        /mnt/d/IdeaProjects/com.andrewpetrowski.diploma.raspberry/src/main/jni/WiringPi/wiringPi/cmake-build-debug-arm
#        /mnt/d/IdeaProjects/com.andrewpetrowski.diploma.raspberry/src/main/jni/WiringPi/devLib/cmake-build-debug-arm
#)


target_compile_options(raspiinfo PRIVATE -fPIC)

find_library(WIRDEV wiringPiDev
        HINTS wiringPi/devLib)
target_link_libraries(raspiinfo
        PUBLIC ${WIRINGPI}
        PUBLIC ${WIRDEV})