#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string.h>

#define TAG    "jni-log"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

//签名信息
const char *app_sha1="F723DBC981112F4B39985717177B3F871435E920";
const char hexcode[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

char* getSha1(JNIEnv *env, jobject context_object){
    //上下文对象
    jclass context_class = env->GetObjectClass(context_object);

    //反射获取PackageManager
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject package_manager = env->CallObjectMethod(context_object, methodId);
    if (package_manager == NULL) {
        LOGD("package_manager is NULL!!!");
        return NULL;
    }

    //反射获取包名
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name = (jstring)env->CallObjectMethod(context_object, methodId);
    if (package_name == NULL) {
        LOGD("package_name is NULL!!!");
        return NULL;
    }
    env->DeleteLocalRef(context_class);

    //获取PackageInfo对象
    jclass pack_manager_class = env->GetObjectClass(package_manager);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info = env->CallObjectMethod(package_manager, methodId, package_name, 0x40);
    if (package_info == NULL) {
        LOGD("getPackageInfo() is NULL!!!");
        return NULL;
    }
    env->DeleteLocalRef(package_manager);

    //获取签名信息
    jclass package_info_class = env->GetObjectClass(package_info);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info, fieldId);
    if (signature_object_array == NULL) {
        LOGD("signature is NULL!!!");
        return NULL;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info);

    //签名信息转换成sha1值
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_class);
    jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_object, methodId);
    jclass byte_array_input_class=env->FindClass("java/io/ByteArrayInputStream");
    methodId=env->GetMethodID(byte_array_input_class,"<init>","([B)V");
    jobject byte_array_input=env->NewObject(byte_array_input_class,methodId,signature_byte);
    jclass certificate_factory_class=env->FindClass("java/security/cert/CertificateFactory");
    methodId=env->GetStaticMethodID(certificate_factory_class,"getInstance","(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring=env->NewStringUTF("X.509");
    jobject cert_factory=env->CallStaticObjectMethod(certificate_factory_class,methodId,x_509_jstring);
    methodId=env->GetMethodID(certificate_factory_class,"generateCertificate",("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert=env->CallObjectMethod(cert_factory,methodId,byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    jclass x509_cert_class=env->GetObjectClass(x509_cert);
    methodId=env->GetMethodID(x509_cert_class,"getEncoded","()[B");
    jbyteArray cert_byte=(jbyteArray)env->CallObjectMethod(x509_cert,methodId);
    env->DeleteLocalRef(x509_cert_class);
    jclass message_digest_class=env->FindClass("java/security/MessageDigest");
    methodId=env->GetStaticMethodID(message_digest_class,"getInstance","(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring=env->NewStringUTF("SHA1");
    jobject sha1_digest=env->CallStaticObjectMethod(message_digest_class,methodId,sha1_jstring);
    methodId=env->GetMethodID(message_digest_class,"digest","([B)[B");
    jbyteArray sha1_byte=(jbyteArray)env->CallObjectMethod(sha1_digest,methodId,cert_byte);
    env->DeleteLocalRef(message_digest_class);

    //转换成char
    jsize array_size=env->GetArrayLength(sha1_byte);
    jbyte* sha1 =env->GetByteArrayElements(sha1_byte,NULL);
    char *hex_sha=new char[array_size*2+1];
    for (int i = 0; i <array_size ; ++i) {
        hex_sha[2*i]=hexcode[((unsigned char)sha1[i])/16];
        hex_sha[2*i+1]=hexcode[((unsigned char)sha1[i])%16];
    }
    hex_sha[array_size*2]='\0';

    LOGD("hex_sha %s ",hex_sha);
    return hex_sha;
}

jboolean checkValidity(JNIEnv *env,char *sha1){
    //比较签名
    if (strcmp(sha1,app_sha1)==0)
    {
        LOGD("验证成功");
        return true;
    }
    LOGD("验证失败");
    return false;
}

jstring getSign(JNIEnv *env, jobject contextObject){
        //上下文对象
        jclass context_class = env->GetObjectClass(contextObject);

        //反射获取PackageManager
        jmethodID pm_id = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
        jobject pm_obj = env->CallObjectMethod(contextObject, pm_id);
        if (pm_obj == NULL) {
            LOGD("pm_obj is NULL!!!");
            return NULL;
        }

         //获取PackageInfo对象
        jclass pm_clazz = env->GetObjectClass(pm_obj);
        jmethodID  package_info_id = env->GetMethodID(pm_clazz, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
//        jclass context_class = env->GetObjectClass(contextObject);
        //反射获取包名
        jmethodID mid = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
        jstring pkg_str = (jstring)env->CallObjectMethod(contextObject, mid);
        if (pkg_str == NULL) {
            LOGD("package_name is NULL!!!");
            return NULL;
        }
        //env->DeleteLocalRef(pack_manager_class);
        jobject pi_obj = env->CallObjectMethod(pm_obj, package_info_id, pkg_str, 0x40);
        if (pi_obj == NULL) {
             LOGD("getPackageInfo() is NULL!!!");
             return NULL;
        }
        //获取签名信息
        jclass pi_clazz = env->GetObjectClass(pi_obj);
        jfieldID signatures_filedId = env->GetFieldID(pi_clazz, "signatures", "[Landroid/content/pm/Signature;");
        jobjectArray signaturesArray = (jobjectArray) env->GetObjectField(pi_obj, signatures_filedId);
        jobject signature_obj = env->GetObjectArrayElement(signaturesArray, 0);
        jclass signature_clazz = env->GetObjectClass(signature_obj);
        jmethodID string_id = env->GetMethodID(signature_clazz,"toCharsString","()Ljava/lang/String;");
        jstring str = static_cast<jstring>(env->CallObjectMethod(signature_obj,string_id));
        return str;

}