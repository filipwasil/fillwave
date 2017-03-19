/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <jni.h>
#include <errno.h>
#include <pthread.h>
#include <android/sensor.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>
#include <fillwave/Log.h>
#include <fillwave/Profiler.h>

#include <assert.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <zconf.h>
#include <zlib.h>

#include <fstream>
#include "../../../android/inc/ContextEGL/egl_helper.h"
#include "../../../android/inc/ContextEGL/native_app_glue.h"
#include "../../../android/inc/ContextOpenSL/native_audio.h"
#include "../../../android/inc/example.h"

FLOGINIT("Fillwave android example", FERROR | FFATAL)

using namespace fillwave;

static int CLIP_NONE = 0;
static int CLIP_HELLO = 1;
static int CLIP_ANDROID = 2;
static int CLIP_SAWTOOTH = 3;
static int CLIP_PLAYBACK = 4;

static jboolean isPlayingAsset = false;
jboolean created = false;

/**
 * Our saved state data.
 */
struct saved_state {
  float angle;
  float rotationDirection;
  int32_t x;
  int32_t y;
};


/**
 * Shared state for our app.
 */
struct engine {
  struct android_app *app;

  int animating;
  EGL::EGLContextInfo eglInfo;
  struct saved_state state;

  Engine *fillwave;
//    pText fpsCounter;
  /* Accelerometer */
  ASensorManager *sensorManager;
  const ASensor *accelerometerSensor;
  ASensorEventQueue *sensorEventQueue;
};

// -------------------------------------------

const EGLint attribs[] = {
    EGL_RENDERABLE_TYPE,
    EGL_OPENGL_ES2_BIT,
    EGL_BLUE_SIZE,
    8,
    EGL_GREEN_SIZE,
    8,
    EGL_RED_SIZE,
    8,
    EGL_DEPTH_SIZE,
    16, // DEPTH BUFFER !!
    EGL_NONE
};

const EGLint context_attrib_list[] = {
    EGL_CONTEXT_CLIENT_VERSION,
    3,
    EGL_NONE
};

std::string resolveApkWorkspace(Engine *engine, struct android_app *app) {

  ANativeActivity *activity = app->activity;
  JNIEnv *env = 0;

  activity->vm->AttachCurrentThread(&env, NULL);

  jclass clazz = env->GetObjectClass(activity->clazz);
  jmethodID methodID = env->GetMethodID(clazz, "getPackageCodePath", "()Ljava/lang/String;");
  jobject result = env->CallObjectMethod(activity->clazz, methodID);

  jboolean isCopy;
  std::string assets_path = env->GetStringUTFChars((jstring) result, &isCopy);

  activity->vm->DetachCurrentThread();
  return assets_path;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine *engine) {
  if (engine->eglInfo.display == NULL) {
    // No display.
    fLogE("No Display");
    return;
  }

  static uint64_t mLastFrameNs = 0;

  Engine *ptr = reinterpret_cast<Engine *>(engine);

  timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  uint64_t nowNs = now.tv_sec * 1000000000ull + now.tv_nsec;

  float dt = 0;
  if (mLastFrameNs > 0) {
    dt = float(nowNs - mLastFrameNs) * 0.000000001f;
  }

  mLastFrameNs = nowNs;

  engine->fillwave->draw(dt);

  pthread_mutex_lock(&engine->app->mutex);
  EGL::SwapDisplay(&engine->eglInfo);
  pthread_mutex_unlock(&engine->app->mutex);
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app *app, AInputEvent *event) {

  struct engine *engine = (struct engine *) app->userData;

  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
    int key_val = AKeyEvent_getKeyCode(event);
    if (key_val == AKEYCODE_BACK) {
      // turn off all audio
      isPlayingAsset = false;
      selectClip(CLIP_NONE, 0);
      setPlayingAssetAudioPlayer(isPlayingAsset);
      engine->animating = 0;
      fLogE("Animation stop");
      return 1;
    } else if (key_val == AKEYCODE_VOLUME_UP || key_val == AKEYCODE_VOLUME_DOWN) {
      if (!created) {
        ANativeActivity *activity = app->activity;
        JNIEnv *env = 0;

        activity->vm->AttachCurrentThread(&env, NULL);

        jclass clazz = env->GetObjectClass(activity->clazz);

        created = createAssetAudioPlayer(env, clazz, activity->assetManager, "background.mp3");
        if (created) {
          fLogE("CREATED ASSET AUDIO PLAYER");
          isPlayingAsset = true;
          setPlayingAssetAudioPlayer(true);
          selectClip(CLIP_PLAYBACK, 3);
        } else {
          fLogE("NOT CREATED ASSET AUDIO PLAYER");
        }
        activity->vm->DetachCurrentThread();
      } else {
        isPlayingAsset = true;
        selectClip(CLIP_PLAYBACK, 3);
        setPlayingAssetAudioPlayer(isPlayingAsset);
      }
      engine->animating = 1;
      fLogE("Animation start");
      return 1;
    }
    return 1;
  } else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    switch (AInputEvent_getSource(event)) {
      case AINPUT_SOURCE_TOUCHSCREEN:
        switch (AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK) {
          case AMOTION_EVENT_ACTION_DOWN:
            if (engine->fillwave != NULL) {
              GLfloat x = AMotionEvent_getX(event, 0);
              GLfloat y = AMotionEvent_getY(event, 0);
              framework::TouchEventData data;
              data.xPos = x;
              data.yPos = y;
              framework::TouchEvent event(data);
              engine->fillwave->insertResizeScreen(engine->eglInfo.width, engine->eglInfo.height);
              engine->fillwave->insertInput(event);
            } else {
              fLogE("Null scene pointer");
            }
            break;
          case AMOTION_EVENT_ACTION_UP:
            break;
          case AMOTION_EVENT_ACTION_MOVE:
            break;
        }
        break;
    }
  }
  return 0;
}

//     INPUT EVENT

//      int32_t AInputEvent_getType(const AInputEvent* event);
//      int32_t AInputEvent_getDeviceId(const AInputEvent* event);
//      int32_t AInputEvent_getSource(const AInputEvent* event);

//     KEY EVENT

//      int32_t AKeyEvent_getAction(const AInputEvent* key_event);
//      int32_t AKeyEvent_getFlags(const AInputEvent* key_event);
//      int32_t AKeyEvent_getKeyCode(const AInputEvent* key_event);
//      int32_t AKeyEvent_getScanCode(const AInputEvent* key_event);
//      int32_t AKeyEvent_getMetaState(const AInputEvent* key_event);
//      int32_t AKeyEvent_getRepeatCount(const AInputEvent* key_event);
//      int64_t AKeyEvent_getDownTime(const AInputEvent* key_event);
//      int64_t AKeyEvent_getEventTime(const AInputEvent* key_event);

//     AKEY_EVENT_ACTION_DOWN = 0,
//     AKEY_EVENT_ACTION_UP = 1,
//     AKEY_EVENT_ACTION_MULTIPLE = 2

//     AKEY_EVENT_FLAG_WOKE_HERE = 0x1,
//     AKEY_EVENT_FLAG_SOFT_KEYBOARD = 0x2,
//     AKEY_EVENT_FLAG_KEEP_TOUCH_MODE = 0x4,
//     AKEY_EVENT_FLAG_FROM_SYSTEM = 0x8,
//     AKEY_EVENT_FLAG_EDITOR_ACTION = 0x10,
//     AKEY_EVENT_FLAG_CANCELED = 0x20,
//     AKEY_EVENT_FLAG_VIRTUAL_HARD_KEY = 0x40,
//     AKEY_EVENT_FLAG_LONG_PRESS = 0x80,
//     AKEY_EVENT_FLAG_CANCELED_LONG_PRESS = 0x100,
//     AKEY_EVENT_FLAG_TRACKING = 0x200,
//     AKEY_EVENT_FLAG_FALLBACK = 0x400

//     MOTION EVENT

//      int32_t AMotionEvent_getAction(const AInputEvent* motion_event);
//      int32_t AMotionEvent_getFlags(const AInputEvent* motion_event);
//      int32_t AMotionEvent_getMetaState(const AInputEvent* motion_event);
//      int32_t AMotionEvent_getButtonState(const AInputEvent* motion_event);
//      int32_t AMotionEvent_getEdgeFlags(const AInputEvent* motion_event);
//      int64_t AMotionEvent_getDownTime(const AInputEvent* motion_event);
//      int64_t AMotionEvent_getEventTime(const AInputEvent* motion_event);
//      float AMotionEvent_getXOffset(const AInputEvent* motion_event) __NDK_FPABI__;
//      float AMotionEvent_getYOffset(const AInputEvent* motion_event) __NDK_FPABI__;
//      float AMotionEvent_getXPrecision(const AInputEvent* motion_event) __NDK_FPABI__;
//      float AMotionEvent_getYPrecision(const AInputEvent* motion_event) __NDK_FPABI__;
//      size_t AMotionEvent_getPointerCount(const AInputEvent* motion_event);
//      int32_t AMotionEvent_getPointerId(const AInputEvent* motion_event, size_t pointer_index);
//      int32_t AMotionEvent_getToolType(const AInputEvent* motion_event, size_t pointer_index);
//      float AMotionEvent_getRawX(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getRawY(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getX(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getY(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getPressure(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getSize(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getTouchMajor(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getTouchMinor(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getToolMajor(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getToolMinor(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;
//      float AMotionEvent_getOrientation(const AInputEvent* motion_event, size_t pointer_index) __NDK_FPABI__;

//      float AMotionEvent_getAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index) __NDK_FPABI__;

//      size_t AMotionEvent_getHistorySize(const AInputEvent* motion_event);
//      int64_t AMotionEvent_getHistoricalEventTime(const AInputEvent* motion_event, size_t history_index);
//      float AMotionEvent_getHistoricalRawX(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalRawY(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalX(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalY(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalPressure(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalSize(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalTouchMajor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalTouchMinor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalToolMajor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalToolMinor(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalOrientation(const AInputEvent* motion_event, size_t pointer_index, size_t history_index) __NDK_FPABI__;
//      float AMotionEvent_getHistoricalAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index, size_t history_index) __NDK_FPABI__;

//      #define AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT 8

//       AMOTION_EVENT_ACTION_MASK = 0xff,
//       AMOTION_EVENT_ACTION_POINTER_INDEX_MASK  = 0xff00,
//       AMOTION_EVENT_ACTION_DOWN = 0,
//       AMOTION_EVENT_ACTION_UP = 1,
//       AMOTION_EVENT_ACTION_MOVE = 2,
//       AMOTION_EVENT_ACTION_CANCEL = 3,
//       AMOTION_EVENT_ACTION_OUTSIDE = 4,
//       AMOTION_EVENT_ACTION_POINTER_DOWN = 5,
//       AMOTION_EVENT_ACTION_POINTER_UP = 6,
//       AMOTION_EVENT_ACTION_HOVER_MOVE = 7,
//       AMOTION_EVENT_ACTION_SCROLL = 8,
//       AMOTION_EVENT_ACTION_HOVER_ENTER = 9,
//       AMOTION_EVENT_ACTION_HOVER_EXIT = 10,
//       AMOTION_EVENT_EDGE_FLAG_NONE = 0,
//       AMOTION_EVENT_EDGE_FLAG_TOP = 0x01,
//       AMOTION_EVENT_EDGE_FLAG_BOTTOM = 0x02,
//       AMOTION_EVENT_EDGE_FLAG_LEFT = 0x04,
//       AMOTION_EVENT_EDGE_FLAG_RIGHT = 0x08

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app *app, int32_t cmd) {
  struct engine *engine = (struct engine *) app->userData;
  switch (cmd) {
    case APP_CMD_SAVE_STATE:
      // The system has asked us to save our current state.  Do so.
      engine->app->savedState = malloc(sizeof(struct saved_state));
      *((struct saved_state *) engine->app->savedState) = engine->state;
      engine->app->savedStateSize = sizeof(struct saved_state);
      break;
    case APP_CMD_INIT_WINDOW:
      // The window is being shown, get it ready.
      if (engine->app->window != NULL) {
        engine->eglInfo.major = 3;
        engine->eglInfo.major = 0;
        EGL::Initialize((EGLNativeWindowType) app->window, &engine->eglInfo, attribs, context_attrib_list);

//                if (engine->fillwave) {
//                   engine->fillwave->reload(); //xxx reloading does not work in 1.9.10
//                   engine->fillwave->insertResizeScreen(engine->eglInfo.width,
//                                                        engine->eglInfo.height);
//                } else {
        if (engine->fillwave) {
          delete engine->fillwave;
        }
        engine->fillwave = new Engine(app->activity);
        engine->fillwave->insertResizeScreen(engine->eglInfo.width, engine->eglInfo.height);
        perform(engine->fillwave);
//                }

        engine->animating = 1;
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      engine->animating = 0;
//            engine->fpsCounter.reset();
//            delete engine->fillwave;
//            engine->fillwave = nullptr;
      EGL::Terminate(&engine->eglInfo);
      break;
    case APP_CMD_GAINED_FOCUS:
      // When our app gains focus, we start monitoring the accelerometer.
      if (engine->accelerometerSensor != NULL) {
        ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
        // We'd like to get 60 events per second (in us).
        ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L / 60) * 1000);
      }
      break;
    case APP_CMD_LOST_FOCUS:
      // Also stop animating.
      engine->animating = 0;
      // When our app loses focus, we stop monitoring the accelerometer.
      // This is to avoid consuming battery while not being used.
      if (engine->accelerometerSensor != NULL) {
        ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
      }
      // Also stop animating.
      engine->animating = 0;
//            engine_draw_frame(engine); // xxx why
      break;
  }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app *state) {
  struct engine engine_g;
  // Make sure glue isn't stripped.
  app_dummy();

  memset(&engine_g, 0, sizeof(engine_g));
  state->userData = &engine_g;
  state->onAppCmd = engine_handle_cmd;
  state->onInputEvent = engine_handle_input;
  engine_g.app = state;

  // Prepare to monitor accelerometer
  engine_g.sensorManager = ASensorManager_getInstance();
  engine_g.accelerometerSensor = ASensorManager_getDefaultSensor(engine_g.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  engine_g.sensorEventQueue = ASensorManager_createEventQueue(engine_g.sensorManager,
                                                              state->looper,
                                                              LOOPER_ID_USER,
                                                              NULL,
                                                              NULL);

  if (state->savedState != NULL) {
    // We are starting with a previous saved state; restore from it.
    engine_g.state = *(struct saved_state *) state->savedState;
  }

  /* Init audio */
  createEngine();
  createBufferQueueAudioPlayer();

  // loop waiting for stuff to do.

  while (1) {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source *source;

    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident = ALooper_pollAll(engine_g.animating ? 0 : -1, NULL, &events, (void **) &source)) >= 0) {

      // Process this event.
      if (source != NULL) {
        source->process(state, source);
      }

      // Check if we are exiting.
      if (state->destroyRequested != 0) {
        EGL::Terminate(&engine_g.eglInfo);
        return;
      }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER) {
        if (engine_g.accelerometerSensor != NULL) {
          ASensorEvent event;
          while (ASensorEventQueue_getEvents(engine_g.sensorEventQueue, &event, 1) > 0) {
            if (engine_g.fillwave && engine_g.animating) {
              GLfloat speedRotationUp = 0.05;
              GLfloat speedRotationRight = 0.15;
              GLfloat speedRotationOffset = 4.0;
              GLfloat speedForward = 0.01;
              engine_g.fillwave->getCurrentScene()->getCamera()->moveInDirection(glm::vec3(0.0, 0.0, -speedForward));
              engine_g.fillwave->getCurrentScene()->getCamera()->rotateBy(glm::vec3(0.0, 1.0, 0.0),
                                                                          speedRotationRight *
                                                                          glm::radians(-event.acceleration.y));
              engine_g.fillwave->getCurrentScene()->getCamera()->rotateBy(glm::vec3(1.0, 0.0, 0.0),
                                                                          speedRotationUp * glm::radians(-(
                                                                              event.acceleration.z - speedRotationOffset
                                                                          )));
            }
//                       fLogI("accelerometer: x=%f y=%f z=%f",
//                                event.acceleration.x, event.acceleration.y,
//                                event.acceleration.z);
          }
        }
      }
    }
    if (engine_g.animating) {
      engine_draw_frame(&engine_g);
    }
  }
}

