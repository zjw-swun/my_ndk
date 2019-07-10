//
// Created by Liszt on 2019/7/10.
//

#include <jni.h>

#ifndef NDKDEMO_VALID_H
#define NDKDEMO_VALID_H

#endif //NDKDEMO_VALID_H

#ifdef __cplusplus
extern "C" {
#endif

char *getSha1(JNIEnv *env, jobject context_object);

jboolean checkValidity(JNIEnv *env, char *sha1);

jstring getSign(JNIEnv *env, jobject contextObject);

#ifdef __cplusplus
}
#endif

#endif
