/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_andrewpetrowski_diploma_raspberry_Sensors_DHT11 */

#ifndef _Included_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11
#define _Included_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11
#ifdef __cplusplus
extern "C" {
#endif
#undef com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_MAXTIMINGS
#define com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_MAXTIMINGS 85L
/*
 * Class:     com_andrewpetrowski_diploma_raspberry_Sensors_DHT11
 * Method:    GetDhtData
 * Signature: (I)Lcom/andrewpetrowski/diploma/bridgelib/Models/DHT11_Data;
 */
JNIEXPORT jobject JNICALL Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_GetDhtData
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_andrewpetrowski_diploma_raspberry_Sensors_DHT11
 * Method:    readData
 * Signature: (I)[F
 */
JNIEXPORT jfloatArray JNICALL Java_com_andrewpetrowski_diploma_raspberry_Sensors_DHT11_readData
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
