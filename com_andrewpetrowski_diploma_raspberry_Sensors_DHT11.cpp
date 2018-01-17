/*
 *    Copyright 2017 Andrew Petrowsky
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "com_andrewpetrowski_diploma_raspberry_Sensors_DHT11.h"
#include "DHTAdapter.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>
#include "DHT11.h"
#include <tuple>

/**
 * Get sensor's data as DHT11_Data object
 * @deprecated Use @see Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_readData
 * @param env Java environment
 * @param jobj Java class
 * @param pin Pin number (wiringPi mode)
 * @return DHT11_Data object
 */
JNIEXPORT jobject JNICALL Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_GetDhtData
        (JNIEnv *env, jobject jobj, jint pin) {
    float humidity = 2, temperature = 5;

    // ReadDhtData((int)pin,&temperature,&humidity);
    std::cout << temperature << " " << humidity;
    jclass cls = env->FindClass("com/andrewpetrowski/diploma/bridgelib/Models/DHT11_Data");
    jmethodID constructor = env->GetMethodID(cls, "<init>", "(FF)V");
    return env->NewObject(cls, constructor, temperature, humidity);

}

/**
 * Reserved for testing
 * @param env Java environment
 * @param jobj Java class
 * @return Console output of sensor data
 */
JNIEXPORT jstring JNICALL Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_Test
        (JNIEnv *env, jobject jobj) {
    jstring strr;
    while (1) {
        const char *str = "";
        strr = env->NewStringUTF(str);
        printf(str);

        delay(1000);
    }

    return strr;
}

///**
// * Override JNI_OnLoad maethod to initialize wiringPi library
// * @param vm Java machine
// * @param reserved System reserved
// * @return
// */
//jint JNI_OnLoad(JavaVM* vm, void* reserved) {
//    if (wiringPiSetup() == -1) {
//        exit(1);
//    }
//    return JNI_VERSION_1_8;
//}

/**
 * Get data from DHT11 sensor
 * @param env Java environment
 * @param jclass1 Java class
 * @param pin Pin number (wiringPi mode)
 * @return Java array, which contains 2 elements.
 * First is temperature
 * Second is humidity
 */
JNIEXPORT jfloatArray JNICALL Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_readData
        (JNIEnv *env, jobject jclass1, jint pin) {
    jfloatArray j_result = env->NewFloatArray(2);
    jfloat result[2];
    float t, h;
    int _pin = (int) pin;
    DHT11 &dht11 = DHT11::getInstance(pin);
    std::tuple<float, float> data = std::make_tuple(0, 0);
    do {
        data = dht11.GetDataTuple();
    } while (std::get<0>(data) == 0);
//    auto data = dht11.GetDataTuple();
    //ReadDhtData(_pin,&t,&h);
    result[0] = (jfloat) std::get<0>(data);
    result[1] = (jfloat) std::get<1>(data);
    env->SetFloatArrayRegion(j_result, 0, 2, result);
    return j_result;
}