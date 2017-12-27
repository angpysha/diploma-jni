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

#include <vector>
#define MAXTIMINGS	85
#define DHTPIN		7

int read_dht11_dat(int pin);
void ReadDhtData(int pin,float* temperature,float* humidity);
float getAverage(float nums[],int size);

#ifdef _cplusplus
extern "C" int read_dht11_dat(int pin);
extern "C" void ReadDhtData(int pin,float* temperature,float* humidity);
extern "C" float getAverage(float nums[],int size);
#else
int read_dht11_dat(int pin);
void ReadDhtData(int pin,float* temperature,float* humidity);
float getAverage(float nums[],int size);
#endif
