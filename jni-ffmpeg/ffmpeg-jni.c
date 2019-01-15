#include "android_log.h"
#include "com_twobulls_myapplication_jni_FFmpegJni.h"
#include "ffmpeg.h"
#include <stdlib.h>
#include <stdbool.h>
// JNIEXPORT jint JNICALL Java_com_twobulls_myapplication_jni_FFmpegJni_run(JNIEnv *env, jclass obj, jobjectArray commands) {
//     int argc = (*env)->GetArrayLength(env, commands);
//     char *argv[argc];
//     int i;
//     for (i = 0; i < argc; i++) {
//         jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
//         argv[i] = (char*) (*env)->GetStringUTFChars(env, js, 0);
//     }
//     LOGD("----------command begin---------");
//     return main(argc, argv);
// }

int main(int argc, char **argv);
JavaVM *sVm = NULL;
jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
  sVm = vm;
  return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL Java_com_twobulls_myapplication_jni_FFmpegJni_run(JNIEnv *env, jobject obj, jobjectArray args)
{
  int i = 0;
  int argc = 0;
  char **argv = NULL;
  jstring *strr = NULL;
  if (args != NULL) {
    argc = (*env)->GetArrayLength(env, args);
    argv = (char **) malloc(sizeof(char *) * argc);
    strr = (jstring *) malloc(sizeof(jstring) * argc);
    for(i=0;i<argc;i++) {
      strr[i] = (jstring)(*env)->GetObjectArrayElement(env, args, i);
      argv[i] = (char *)(*env)->GetStringUTFChars(env, strr[i], 0);
    }
  }
  LOGD("----------command begin---------");
  main(argc, argv);
  for(i=0;i<argc;i++) {
    (*env)->ReleaseStringUTFChars(env, strr[i], argv[i]);
  }
  free(argv);
  free(strr);
}
