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

#include "DHTAdapter.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <type_traits>
#include <vector>
#include <memory>

using namespace std;

/**
 * Array which contains native DHT11 sensor data
 */
int dht11_dat[5] = {0, 0, 0, 0, 0};

/**
 * Read data from DHT11 sensor
 * @param pin Pin (wiringPi configuration)
 * @return Success result
 */
int read_dht11_dat(int pin) {
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    float f;

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(20);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);
    delayMicroseconds(10);

    for (i = 0; i < MAXTIMINGS; i++) {
        counter = 0;
        while (digitalRead(pin) == laststate) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = digitalRead(pin);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0)) {
            dht11_dat[j / 8] <<= 1;
            if (counter > 50)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) &&
        (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
        f = dht11_dat[2] * 9. / 5. + 32;
//		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
//			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
        return 1;
    } else {
//		printf( "Data not good, skip\n" );
        return 0;
    }
}

/**
 * Read temperature and humidity in human understand view
 * @param pin Pin number (wiringPi configuration)
 * @param temperature Temperature to return
 * @param humidity Humidity to return
 */
void ReadDhtData(int pin, float *temperature, float *humidity) {
    const int SIZE = 5;
    float temperatures[SIZE] = {0};
    float humidities[SIZE] = {0};

    bool res = false;
    for (int i = 0; i < SIZE;) {

        res = read_dht11_dat(pin);
        if (res) {
            temperatures[i] = dht11_dat[2]**dht11_dat[3]*0.1*/;
            humidities[i] = dht11_dat[0]/**dht11_dat[1]*0.1)*/;
            i++;
        }
        delay(1000);
    }
//    printf("Temperature1: %f",temperatures[0]);
    *temperature = getAverage(temperatures, SIZE);
    *humidity = getAverage(humidities, SIZE);
}

#ifdef _cplusplus
template<typename T>
void ReadDhtDataEx(int pin,shared_ptr<T> temperature, shared_ptr<T> humidity) {
    vector<float> temperatures, humidities;
    const int SIZE = 5;
    bool res = false;
    for (int i = 0; i < SIZE;) {
        res = read_dht11_dat(pin);

        if (res) {
            temperatures.push_back(dht11_dat[2]);
            humidities.push_back(dht11_dat[0]);
            i++;
        }
        delay(1000);
    }

    temperature = std::make_shared<T>(getAverageEx(temperatures));
}
#endif

/**
 * Get average of array
 * @param nums Array of numbers
 * @param size Array's size
 * @return Average value
 */
float getAverage(float nums[], int size) {
    float sum = 0;

    for (int i = 0; i < size; i++) {
        sum += nums[i];
    }

    return sum / (size);
}
#ifdef _cplusplus
/**
 * Generalized average method
 * @tparam T arithmetic type
 * @param els Elements
 * @return Average value
 */
template<typename T>
T getAverageEx(vector<T> els) {
    if (is_arithmetic<T>::value) {
        T sum = 0;

        for (auto &it : els) {
            sum += it;
        }

        return sum / els.capacity();
    } else {
        T val = T();
        return val;
    }
}
#endif

