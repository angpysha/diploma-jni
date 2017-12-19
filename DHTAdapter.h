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
