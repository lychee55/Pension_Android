#include <jni.h>
#include <string>
#include "videoplayer/EnjoyPlayer.h"
#include "videoplayer/JavaCallHelper.h"

JavaVM *javaVM = 0;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT jlong JNICALL
Java_com_warehouse_video_VideoPlayer_nativeInit(JNIEnv *env, jobject thiz) {//this代表实例对象
    EnjoyPlayer *player = new EnjoyPlayer(new JavaCallHelper(javaVM, env, thiz));
    return (jlong) player;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_warehouse_video_VideoPlayer_setDataSource(JNIEnv *env, jobject thiz, jlong nativeHandle,
                                                     jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->setDataSource(path);
    env->ReleaseStringUTFChars(path_, path);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_warehouse_video_VideoPlayer_prepare(JNIEnv *env, jobject thiz, jlong nativeHandle) {
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->prepare();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_warehouse_video_VideoPlayer_start(JNIEnv *env, jobject thiz, jlong nativeHandle) {
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->start();

}



extern "C"
JNIEXPORT void JNICALL
Java_com_warehouse_video_VideoPlayer_setSurface(JNIEnv *env, jobject thiz, jlong nativeHandle,
                                                  jobject surface) {

    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    player->setWindow(window);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_warehouse_video_VideoPlayer_stop(JNIEnv *env, jobject thiz, jlong nativeHandle) {
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->stop();
    delete player;

}
