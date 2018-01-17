//
// Created by andre on 07.01.2018.
//

#ifndef JNI_SENSOR_H
#define JNI_SENSOR_H


#include <memory>
#include <wiringPi.h>

class DHT11 {
public:
    static DHT11& getInstance(int pin) {
        static DHT11 dht11(pin);

        return dht11;
    }
    float Temperature;
    float Humidity;

   // bool GetData(int pin,std::shared_ptr<float> temperature,std::shared_ptr<float> humidity);

    std::tuple<float,float> GetDataTuple();
private:
    int pin;
   DHT11(int pin) : pin(pin) {
       if (wiringPiSetup() == -1) {
           exit(1);
       }
   }
    const int max_timings = 85;
   // int dht11_dat[5] = {0, 0, 0, 0, 0};
    //int read_dht11_dat();
public:
    DHT11(DHT11 const&) = delete;
    void operator =(DHT11 const&) = delete;
};


#endif //JNI_SENSOR_H
