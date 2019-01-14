#include "android_log.h"
#include "com_twobulls_myapplication_jni_FFmpegJni.h"
#include "ffmpeg.h"

JNIEXPORT jint JNICALL Java_com_twobulls_myapplication_jni_FFmpegJni_run(JNIEnv *env, jclass obj, jobjectArray commands) {
    int argc = (*env)->GetArrayLength(env, commands);
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        argv[i] = (char*) (*env)->GetStringUTFChars(env, js, 0);
    }
    LOGD("----------command begin---------");
    return main(argc, argv);
}