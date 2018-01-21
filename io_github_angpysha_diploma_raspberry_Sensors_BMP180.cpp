//
// Created by andre on 13.01.2018.
//
#include "io_github_angpysha_diploma_raspberry_Sensors_BMP180.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include "BMP180.h"
#include <sys/time.h>
#include <unistd.h>
#include <tuple>

JNIEXPORT void JNICALL Java_io_github_angpysha_diploma_1raspberry_Sensors_BMP180_Testing
  (JNIEnv *env, jobject obj) {
    float temperature=11,pressure=12,altitude = 13;

    BMP180& ff = BMP180::getInstance();

    auto data  = ff.getDataTuple();


    std::cout << "Temperature: " << std::get<0>(data) << "; Pressure: " << std::get<2>(data) << "; Altitude: " << std::get<1>(data) <<std::endl;

    delay(1000);
}


JNIEXPORT jfloatArray JNICALL Java_io_github_angpysha_diploma_1raspberry_Sensors_BMP180_GetData
        (JNIEnv *env, jobject obj) {

    BMP180& ff = BMP180::getInstance();

    auto data  = ff.getDataTuple();


    jfloatArray j_result = env->NewFloatArray(3);
    jfloat result[3];

   // float pressure = static_cast<float >(std::get<2>(data));
    result[0] = (jfloat) std::get<0>(data);
    result[1] = (jfloat) std::get<1>(data);
    result[2] = (jfloat) std::get<2>(data);

  //  std::cout << "Temperature: " << std::get<0>(data) << "; Pressure: " << std::get<2>(data) << "; Altitude: " << std::get<1>(data) <<std::endl;

  //    std::cout << "Temperature: " << result[0] << "; Pressure: " << result[2] << "; Altitude: " << result[1] << std::endl;
//    result[0] = 1;
//    result[1] = 2;
//    result[2] = 2;
    env->SetFloatArrayRegion(j_result, 0, 3, result);
    return j_result;
}
