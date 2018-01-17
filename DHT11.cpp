//
// Created by andre on 07.01.2018.
//

#include <wiringPi.h>
#include "DHT11.h"

std::tuple<float, float> DHT11::GetDataTuple() {
    int dht11_dat[5] = {0};
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

    for (i = 0; i < max_timings; i++) {
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
        float temperature = dht11_dat[2]+ dht11_dat[3]*0.1;
        float humidity = dht11_dat[0]+dht11_dat[1]*0.1;
//		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
//			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
        return std::make_tuple(temperature,humidity);
    } else {
//		printf( "Data not good, skip\n" );
        return std::make_tuple(0,0);
    }
}
