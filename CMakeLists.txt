cmake_minimum_required(VERSION 3.9)
project(jni)

set(CMAKE_CXX_STANDARD 11)

add_executable(jni
        com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.cpp
        com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.h
        DHTAdapter.cpp
        DHTAdapter.h)
include_directories("C:\\Program Files\\Java\\jdk1.8.0_144\\include"
        "C:\\Program Files\\Java\\jdk1.8.0_144\\include\\win32"
        "C:\\Users\\andre\\wiringPi\\wiringPi\\wiringPi")