//
// Created by andre on 13.01.2018.
//

#include "BMP180.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <tuple>

//short AC1,AC2,AC3,B1,B2,MB,MC,MD;
//unsigned short AC4,AC5,AC6;
//int fd;

void BMP180::getData(float *temperature,
                     float *altitude,
                     float *pressure) {

    float temp = read_temperature();
    float alti = read_altitude();
    float pres = read_pressure();
//    std::cout << "Temperature: " << temp << "; Pressure: " << pres << "; Altitude: " << alti <<std::endl;
//    *temperature = temp;
//    *altitude = alti;
//    *pressure = pres;
   // delay(1000);
}

char BMP180::I2C_readByte(int reg) {
    return (char) wiringPiI2CReadReg8(fd, reg);
}

unsigned short BMP180::I2C_readU16(int reg) {
    int MSB, LSB;
    MSB = I2C_readByte(reg);
    LSB = I2C_readByte(reg + 1);
    int value = (MSB << 8) + LSB;
    return (unsigned short) value;
}

short BMP180::I2C_readS16(int reg) {
    int result;
    result = I2C_readU16(reg);
    if (result > 32767)result -= 65536;
    return (short) result;
}

void BMP180::I2C_writeByte(int reg, int val) {
    wiringPiI2CWriteReg8(fd, reg, val);
}

void BMP180::load_calibration() {
    AC1 = I2C_readS16(BMP180_CAL_AC1);
    AC2 = I2C_readS16(BMP180_CAL_AC2);
    AC3 = I2C_readS16(BMP180_CAL_AC3);
    AC4 = I2C_readU16(BMP180_CAL_AC4);
    AC5 = I2C_readU16(BMP180_CAL_AC5);
    AC6 = I2C_readU16(BMP180_CAL_AC6);
    B1 = I2C_readS16(BMP180_CAL_B1);
    B2 = I2C_readS16(BMP180_CAL_B2);
    MB = I2C_readS16(BMP180_CAL_MB);
    MC = I2C_readS16(BMP180_CAL_MC);
    MD = I2C_readS16(BMP180_CAL_MD);
}

int BMP180::read_raw_temp() {
    int raw;
    I2C_writeByte(BMP180_CONTROL, BMP180_READTEMPCMD);
    delay(5);  //5ms;
    raw = I2C_readByte(BMP180_TEMPDATA) << 8;
    raw += I2C_readByte(BMP180_TEMPDATA + 1);
    return raw;
}

int BMP180::read_raw_pressure() {
    int MSB, LSB, XLSB, raw;
    I2C_writeByte(BMP180_CONTROL, BMP180_READPRESSURECMD + (OSS << 6));
    switch (OSS) {
        case BMP180_ULTRALOWPOWER:
            delay(5);
            break;
        case BMP180_HIGHRES:
            delay(14);
            break;
        case BMP180_ULTRAHIGHRES:
            delay(26);
            break;
        default :
            delay(8);
    }
    MSB = I2C_readByte(BMP180_PRESSUREDATA);
    LSB = I2C_readByte(BMP180_PRESSUREDATA + 1);
    XLSB = I2C_readByte(BMP180_PRESSUREDATA + 2);
    raw = ((MSB << 16) + (LSB << 8) + XLSB) >> (8 - OSS);
    return raw;
}

float BMP180::read_temperature() {
    float T;
    int UT, X1, X2, B5;
    UT = read_raw_temp();
    X1 = ((UT - AC6) * AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    T = ((B5 + 8) >> 4) / 10.0;
    return T;
}

int BMP180::read_pressure() {
    int P;
    int UT, UP, X1, X2, X3, B3, B5, B6;
    unsigned int B4;
    int B7;
    UT = read_raw_temp();
    UP = read_raw_pressure();

    X1 = ((UT - AC6) * AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;

    //Pressure Calculations
    B6 = B5 - 4000;
    X1 = (B2 * (B6 * B6) >> 12) >> 11;
    X2 = (AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((AC1 * 4 + X3) << OSS) + 2) / 4;
    X1 = (AC3 * B6) >> 13;
    X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (AC4 * (X3 + 32768)) >> 15;
    B7 = (UP - B3) * (50000 >> OSS);
    if (B7 < 0x80000000) { P = (B7 * 2) / B4; }
    else { P = (B7 / B4) * 2; }
    X1 = (P >> 8) * (P >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * P) >> 16;
    P = P + ((X1 + X2 + 3791) >> 4);
    float ret = P + ((X1 + X2 + 3791) >> 4);
    return P;

}

float BMP180::read_altitude() {
    float pressure, altitude;
    float sealevel_pa = 101325.0;
    pressure = (float) read_pressure();
    altitude = 44330.0 * (1.0 - pow(pressure / sealevel_pa, (1.0 / 5.255)));
    return altitude;
}

float BMP180::read_sealevel_pressure() {
    float altitude_m = 0.0;
    float pressure, p0;
    pressure = (float) read_pressure();
    p0 = pressure / pow(1.0 - altitude_m / 44330.0, 5.255);
    return p0;
}

float BMP180::getTemp() {
    return read_temperature();
}

std::tuple<float, float, float> BMP180::getDataTuple() {
    return std::make_tuple(read_temperature(),read_altitude(),read_pressure());
}





















