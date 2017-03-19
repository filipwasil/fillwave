/*
 * native_audio.h
 *
 *  Created on: 15 Apr 2015
 *      Author: wasilfil
 */

#ifndef NATIVE_AUDIO_H_
#define NATIVE_AUDIO_H_

#include <assert.h>
#include <jni.h>
#include <string.h>

// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
// #include <android/log.h>

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

//__attribute__((constructor)) static void onDlOpen(void);
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

void createEngine(/*JNIEnv* env, jclass clazz*/);

void createBufferQueueAudioPlayer();

jboolean createUriAudioPlayer(JNIEnv *env, jclass clazz, jstring uri);

void setPlayingUriAudioPlayer(/*JNIEnv* env, jclass clazz, */jboolean isPlaying);

void setLoopingUriAudioPlayer(JNIEnv *env, jclass clazz, jboolean isLooping);

static SLMuteSoloItf getMuteSolo();

void setChannelMuteUriAudioPlayer(JNIEnv *env, jclass clazz, jint chan, jboolean mute);

void setChannelSoloUriAudioPlayer(JNIEnv *env, jclass clazz, jint chan, jboolean solo);

int getNumChannelsUriAudioPlayer(JNIEnv *env, jclass clazz);

static SLVolumeItf getVolume();

void setVolumeUriAudioPlayer(JNIEnv *env, jclass clazz, jint millibel);

void setMuteUriAudioPlayer(JNIEnv *env, jclass clazz, jboolean mute);

void enableStereoPositionUriAudioPlayer(JNIEnv *env, jclass clazz, jboolean enable);

void setStereoPositionUriAudioPlayer(JNIEnv *env, jclass clazz, jint permille);

jboolean enableReverb(JNIEnv *env, jclass clazz, jboolean enabled);

jboolean selectClip(/*JNIEnv* env, jclass clazz, */jint which, jint count);

jboolean createAssetAudioPlayer(JNIEnv *env, jclass clazz, AAssetManager *assetManager, const char *utf8);

void setPlayingAssetAudioPlayer(jboolean isPlaying);

jboolean createAudioRecorder(JNIEnv *env, jclass clazz);

void startRecording(JNIEnv *env, jclass clazz);

void shutdown(JNIEnv *env, jclass clazz);

#endif /* NATIVE_AUDIO_H_ */
