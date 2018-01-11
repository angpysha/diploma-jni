//
// Created by andre on 07.01.2018.
//

#ifndef JNI_SENSOR_H
#define JNI_SENSOR_H


#include <bits/shared_ptr.h>

class Sensor {
public:
    float Temperature;
    float Humidity;

    bool GetData(int pin,std::shared_ptr<float> temperature,std::shared_ptr<float> humidity);

};


#endif //JNI_SENSOR_H
