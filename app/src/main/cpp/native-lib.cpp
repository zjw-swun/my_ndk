#include <jni.h>
#include <string>
#include<android/log.h>
#include"valid.cpp"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndk_ndkdemo_SignHelper_getSignaturesSha1(
        JNIEnv *env,
        jobject,
        jobject contextObject) {

    return env->NewStringUTF(getSha1(env, contextObject));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndk_ndkdemo_SignHelper_getSign(
        JNIEnv *env,
        jobject,
        jobject contextObject) {

    return getSign(env, contextObject);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_ndk_ndkdemo_SignHelper_checkSha1(
        JNIEnv *env,
        jobject,
        jobject contextObject) {

    char *sha1 = getSha1(env, contextObject);

    jboolean result = checkValidity(env, sha1);

    return result;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndk_ndkdemo_SignHelper_getSignToken(
        JNIEnv *env,
        jobject,
        jobject contextObject,
        jstring userId) {
    char *sha1 = getSha1(env, contextObject);
    jboolean result = checkValidity(env, sha1);

    if (result) {
        return env->NewStringUTF("获取Token成功");
    } else {
        return env->NewStringUTF("获取失败，请检查valid.cpp文件配置的sha1值");
    }
}


// 测试crash
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_ndkdemo_SignHelper_throwNativeCrash(JNIEnv *env, jobject thiz) {
//    int i = 0 / 0;
//    jstring j = (jstring) "132" + i;
//    char *name = const_cast<char *>(env->GetStringUTFChars(j, NULL));
//    __android_log_print(ANDROID_LOG_INFO, "hello", "%s", &"jni will crash"[(*name)]);
    // 向自身发送一个信号
    raise(SIGQUIT);

}