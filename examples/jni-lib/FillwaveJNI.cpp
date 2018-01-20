#include "../jni-lib/FillwaveJNI.h"

using namespace flw;
using namespace flw::framework;

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_fillwave_Fillwave
 * Method:    newEngine
 * Signature: ()J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_createEngine(JNIEnv * env, jobject
clazz , jstring rootPath ) {
Engine *e = new Engine(env->GetStringUTFChars(rootPath, nullptr)); return reinterpret_cast <jlong>(e);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    deleteEngine
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_deleteEngine
(JNIEnv
*, jobject,
jlong engine
) {
delete reinterpret_cast<Engine*>(engine);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    configureDebugger
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_configureDebugger
(JNIEnv
*, jobject,
jlong engine, jint
configuration) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

switch (configuration) {
case 0:
ptr->
configureDebugger(EDebuggerState::eOff);
break;
case 1:
ptr->
configureDebugger(EDebuggerState::eLightsPointDepth);
break;
case 2:
ptr->
configureDebugger(EDebuggerState::eLightsSpot);
break;
case 3:
ptr->
configureDebugger(EDebuggerState::eLightsSpotColor);
break;
case 4:
ptr->
configureDebugger(EDebuggerState::eLightsSpotDepth);
break;
case 5:
ptr->
configureDebugger(EDebuggerState::eLightsPoint);
break;
case 6:
ptr->
configureDebugger(EDebuggerState::ePickingMap);
break;
default:
ptr->
configureDebugger(EDebuggerState::eToggleState);
break;
}}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    configureFileLogging
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_configureFileLogging
(JNIEnv
*env, jobject,
jlong engine, jstring
path) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

ptr->
configureFileLogging(env
->
GetStringUTFChars(path,
nullptr));
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    configFPSCounter
 * Signature: (JLjava/lang/String;FFF)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_configFPSCounter
(JNIEnv
*env, jobject,
jlong engine, jstring
fontName,
jfloat xPosition, jfloat
yPosition,
jfloat size
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

ptr->
configFPSCounter(env
->
GetStringUTFChars(fontName,
nullptr),
xPosition,
yPosition,
size);

//   void configFPSCounter(std::string fontName = "",
//                            GLfloat xPosition = -0.95,
//                            GLfloat yPosition = 0.95,
//                            GLfloat size = 100.0);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    configureBackgroundColor
 * Signature: (JLcom/fillwave/Fillwave/Vector3f;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_configureBackgroundColor
(JNIEnv
*env, jobject,
jlong engine, jobject
backgroundColor) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

jclass clazz = env->GetObjectClass(backgroundColor);

jfieldID xField = env->GetFieldID(clazz, "x", "F");
jfieldID yField = env->GetFieldID(clazz, "y", "F");
jfieldID zField = env->GetFieldID(clazz, "z", "F");

jobject xO = env->GetObjectField(backgroundColor, xField);
jobject yO = env->GetObjectField(backgroundColor, yField);
jobject zO = env->GetObjectField(backgroundColor, zField);

jfloat *x = reinterpret_cast<jfloat *>(&xO);
jfloat *y = reinterpret_cast<jfloat *>(&yO);
jfloat *z = reinterpret_cast<jfloat *>(&zO);

ptr->
configureBackgroundColor(glm::vec3(*x, *y, *z));
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    configureTime
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_configureTime
(JNIEnv
*, jobject,
jlong engine, jfloat
time) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

ptr->
configureTime(time);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    draw
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_draw
(JNIEnv
*, jobject,
jlong engine
) {
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

ptr->
draw(dt);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    drawLines
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_drawLines
(JNIEnv
*, jobject,
jlong engine, jfloat
timePassed) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//   ptr->drawLines(timePassed);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    drawPoints
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_drawPoints
(JNIEnv
*, jobject,
jlong engine, jfloat
timePassed) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//   ptr->drawPoints(timePassed);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    drawTexture
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_drawTexture
(JNIEnv
*, jobject,
jlong engine, jlong
program,
jlong texture
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

ptr->drawTexture(reinterpret_cast<flc::Texture*>(program),
reinterpret_cast<flc::Program*>(texture));
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getPhysicalMeshBuffer
 * Signature: (JLjava/lang/String;)Lcom/fillwave/Fillwave/PhysicsMeshBuffer;
 */
JNIEXPORT jobject
JNICALL Java_com_fillwave_Fillwave_getPhysicalMeshBuffer(JNIEnv * , jobject, jlong
engine,
jstring modelPath
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getLightManager
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getLightManager(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->

getLightManager()

);
}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    setCurrentScene
 * Signature: (J)V
 */
//JNIEXPORT void JNICALL Java_com_fillwave_Fillwave_setCurrentScene
//  (JNIEnv *, jobject, jlong engine, jlong scene) {
//
//   Engine* ptr = reinterpret_cast<Engine*>(engine);
//
//   for (auto& it : gScenes) {
//      if(reinterpret_cast<jlong>(it.get()) == scene) {
//         ptr->setCurrentScene(it);
//      }
//   }
//}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getCurrentScene
 * Signature: (J)J
 */
//JNIEXPORT jlong JNICALL Java_com_fillwave_Fillwave_getCurrentScene
//  (JNIEnv *, jobject, jlong engine) {
//
//   Engine* ptr = reinterpret_cast<Engine*>(engine);
//
//   return reinterpret_cast<jlong>(ptr->getCurrentScene().get());
//}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFramesPassed
 * Signature: (J)I
 */
JNIEXPORT jint
JNICALL Java_com_fillwave_Fillwave_getFramesPassed(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

int res = ptr->getFramesPassed();

return reinterpret_cast
<jint>(res);
}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeShaderFragment
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeShaderFragment__JLjava_lang_String_2(JNIEnv * env, jobject, jlong
engine,
jstring path
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeShaderFragment(
    env
->
GetStringUTFChars(path,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeShaderVertex
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeShaderVertex__JLjava_lang_String_2(JNIEnv * env, jobject, jlong
engine,
jstring path
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeShaderVertex(
    env
->
GetStringUTFChars(path,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeShaderFragment
 * Signature: (JLjava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeShaderFragment__JLjava_lang_String_2Ljava_lang_String_2(JNIEnv * env,
                                                                                                jobject,
                                                                                                jlong
engine,
jstring path, jstring
source) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeShaderFragment(
    env
->
GetStringUTFChars(path,
nullptr),
env->
GetStringUTFChars(source,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeShaderVertex
 * Signature: (JLjava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeShaderVertex__JLjava_lang_String_2Ljava_lang_String_2(JNIEnv * env,
                                                                                              jobject,
                                                                                              jlong
engine,
jstring path, jstring
source) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeShaderVertex(
    env
->
GetStringUTFChars(path,
nullptr),
env->
GetStringUTFChars(source,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeTexture
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeTexture(JNIEnv * env, jobject, jlong
engine,
jstring path, jint
type) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeTexture(
    env
->
GetStringUTFChars(path,
nullptr), aiTextureType_NONE).

get()

);

//todo type does not mean anything.
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeTextureDynamic
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeTextureDynamic(JNIEnv * env, jobject, jlong
engine,
jstring shaderPath
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeTextureDynamic(
    env
->
GetStringUTFChars(shaderPath,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeTexture3D
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeTexture3D(JNIEnv * env, jobject, jlong
engine,
jstring posXTexturePath, jstring
negXTexturePath,
jstring posYTexturePath, jstring
negYTexturePath,
jstring posZTexturePath, jstring
negZTexturePath) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

return reinterpret_cast
<jlong>(ptr
->
storeTexture3D(
    env
->
GetStringUTFChars(posXTexturePath,
nullptr),
env->
GetStringUTFChars(negXTexturePath,
nullptr),
env->
GetStringUTFChars(posYTexturePath,
nullptr),
env->
GetStringUTFChars(negYTexturePath,
nullptr),
env->
GetStringUTFChars(posZTexturePath,
nullptr),
env->
GetStringUTFChars(negZTexturePath,
nullptr)).

get()

);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeLightSpot
 * Signature: (JLcom/fillwave/Fillwave/Vector3f;Lcom/fillwave/Fillwave/Quaternion;Lcom/fillwave/Fillwave/Vector4f;J)J
 */
//JNIEXPORT jlong JNICALL Java_com_fillwave_Fillwave_storeLightSpot(
//		JNIEnv *env,
//		jobject,
//		jlong engine,
//		jobject position,
//		jobject rotation,
//		jobject color,
//		jlong entity) {
//
//	Engine* ptr = reinterpret_cast<Engine*>(engine);
//
//	jclass jposition = env->GetObjectClass(position);
//	jclass jrotation = env->GetObjectClass(rotation);
//	jclass jcolor = env->GetObjectClass(color);
//
//	jfieldID xField = env->GetFieldID(jposition, "x", "F");
//	jfieldID yField = env->GetFieldID(jposition, "y", "F");
//	jfieldID zField = env->GetFieldID(jposition, "z", "F");
//	jfieldID wField;
//
//	jobject xO = env->GetObjectField(position, xField);
//	jobject yO = env->GetObjectField(position, yField);
//	jobject zO = env->GetObjectField(position, zField);
//	jobject wO;
//
//	jfloat* x = reinterpret_cast<jfloat*>(&xO);
//	jfloat* y = reinterpret_cast<jfloat*>(&yO);
//	jfloat* z = reinterpret_cast<jfloat*>(&zO);
//	jfloat* w;
//
//	glm::vec3 _position(*x, *y, *z);
//
//	xField = env->GetFieldID(jrotation, "x", "F");
//	yField = env->GetFieldID(jrotation, "y", "F");
//	zField = env->GetFieldID(jrotation, "z", "F");
//	wField = env->GetFieldID(jrotation, "w", "F");
//
//	xO = env->GetObjectField(rotation, xField);
//	yO = env->GetObjectField(rotation, yField);
//	zO = env->GetObjectField(rotation, zField);
//	wO = env->GetObjectField(rotation, wField);
//	;
//
//	x = reinterpret_cast<jfloat*>(&xO);
//	y = reinterpret_cast<jfloat*>(&yO);
//	z = reinterpret_cast<jfloat*>(&zO);
//	w = reinterpret_cast<jfloat*>(&wO);
//
//	glm::quat _rotation(*x, *y, *z, *w);
//
//	xField = env->GetFieldID(jcolor, "x", "F");
//	yField = env->GetFieldID(jcolor, "y", "F");
//	zField = env->GetFieldID(jcolor, "z", "F");
//	wField = env->GetFieldID(jcolor, "w", "F");
//
//	xO = env->GetObjectField(color, xField);
//	yO = env->GetObjectField(color, yField);
//	zO = env->GetObjectField(color, zField);
//	wO = env->GetObjectField(color, wField);
//	;
//
//	x = reinterpret_cast<jfloat*>(&xO);
//	y = reinterpret_cast<jfloat*>(&yO);
//	z = reinterpret_cast<jfloat*>(&zO);
//	w = reinterpret_cast<jfloat*>(&wO);
//
//	glm::vec4 _color(*x, *y, *z, *w);
//
//	for (auto& it : gEntities) {
//		if (reinterpret_cast<jlong>(it.get()) == entity) {
//			ptr->storeLightSpot(_position, _rotation, _color, it);
//			return reinterpret_cast<jlong>(it.get());
//		}
//	}
//	return reinterpret_cast<jlong>(ptr->storeLightSpot(_position, _rotation,
//			_color).get());
//}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeLightPoint
 * Signature: (JLcom/fillwave/Fillwave/Vector3f;Lcom/fillwave/Fillwave/Vector4f;J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeLightPoint(JNIEnv * env, jobject, jlong
engine,
jobject position, jobject
color,
jlong entity
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeLightDirectional
 * Signature: (JLcom/fillwave/Fillwave/Vector3f;Lcom/fillwave/Fillwave/Quaternion;Lcom/fillwave/Fillwave/Vector4f;J)J
 */
//JNIEXPORT jlong JNICALL Java_com_fillwave_Fillwave_storeLightDirectional
//  (JNIEnv *env, jobject, jlong engine,
//  jobject position,
//  jobject rotation,
//  jobject color,
//  jlong entity) {
//
//   Engine* ptr = reinterpret_cast<Engine*>(engine);
//
//   jclass jposition = env->GetObjectClass(position);
//   jclass jrotation = env->GetObjectClass(rotation);
//   jclass jcolor = env->GetObjectClass(color);
//
//   jfieldID xField = env->GetFieldID(jposition, "x", "F");
//   jfieldID yField = env->GetFieldID(jposition, "y", "F");
//   jfieldID zField = env->GetFieldID(jposition, "z", "F");
//   jfieldID wField;
//
//   jobject xO = env->GetObjectField(position, xField);
//   jobject yO = env->GetObjectField(position, yField);
//   jobject zO = env->GetObjectField(position, zField);
//   jobject wO;
//
//   jfloat* x = reinterpret_cast<jfloat*>(&xO);
//   jfloat* y = reinterpret_cast<jfloat*>(&yO);
//   jfloat* z = reinterpret_cast<jfloat*>(&zO);
//   jfloat* w;
//
//   glm::vec3 _position(*x, *y, *z);
//
//   xField= env->GetFieldID(jrotation, "x", "F");
//   yField= env->GetFieldID(jrotation, "y", "F");
//   zField= env->GetFieldID(jrotation, "z", "F");
//   wField= env->GetFieldID(jrotation, "w", "F");
//
//   xO = env->GetObjectField(rotation, xField);
//   yO = env->GetObjectField(rotation, yField);
//   zO = env->GetObjectField(rotation, zField);
//   wO = env->GetObjectField(rotation, wField);;
//
//   x = reinterpret_cast<jfloat*>(&xO);
//   y = reinterpret_cast<jfloat*>(&yO);
//   z = reinterpret_cast<jfloat*>(&zO);
//   w = reinterpret_cast<jfloat*>(&wO);
//
//   glm::quat _rotation(*x, *y, *z, *w);
//
//   xField= env->GetFieldID(jcolor, "x", "F");
//   yField= env->GetFieldID(jcolor, "y", "F");
//   zField= env->GetFieldID(jcolor, "z", "F");
//   wField= env->GetFieldID(jcolor, "w", "F");
//
//   xO = env->GetObjectField(color, xField);
//   yO = env->GetObjectField(color, yField);
//   zO = env->GetObjectField(color, zField);
//   wO = env->GetObjectField(color, wField);;
//
//   x = reinterpret_cast<jfloat*>(&xO);
//   y = reinterpret_cast<jfloat*>(&yO);
//   z = reinterpret_cast<jfloat*>(&zO);
//   w = reinterpret_cast<jfloat*>(&wO);
//
//   glm::vec4 _color(*x, *y, *z, *w);
//
//   for (auto& it : gEntities) {
//      if(reinterpret_cast<jlong>(it.get()) == entity) {
//      ptr->storeLightDirectional(_position, _rotation, _color, it);
//      return reinterpret_cast<jlong>(it.get());
//      }
//   }
//   return reinterpret_cast<jlong>(ptr->storeLightDirectional(_position, _rotation, _color).get());
//}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    storeText
 * Signature: (JLjava/lang/String;Ljava/lang/String;FFFLcom/fillwave/Fillwave/Vector4f;I)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_storeText(JNIEnv * env, jobject, jlong
engine,
jstring content, jstring
font,
jfloat,
jfloat,
jfloat,
jobject,
jint) {

Engine *ptr = reinterpret_cast<Engine *>(engine);
flw::flf::ps<flw::flf::Text> t = ptr->storeText(env->GetStringUTFChars(content, nullptr),
                         env->GetStringUTFChars(font, nullptr),
                         -0.95,
                         0.80,
                         100.0);

return reinterpret_cast
<jlong>(t
.

get()

);;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearText
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearText
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearLightSpot
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearLightSpot
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearLightDirectional
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearLightDirectional
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearLightPoint
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearLightPoint
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearLights
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearLights
(JNIEnv
*, jobject,
jlong engine
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    pick
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_pick
(JNIEnv
*, jobject,
jlong engine, jint, jint
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getScreenSize
 * Signature: (J)Lcom/fillwave/Fillwave/Vector2i;
 */
JNIEXPORT jobject
JNICALL Java_com_fillwave_Fillwave_getScreenSize(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    log
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_log
(JNIEnv
*, jobject,
jlong engine
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    captureFramebufferToFile
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_captureFramebufferToFile
(JNIEnv
*, jobject,
jlong engine, jstring
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getExecutablePath
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring
JNICALL Java_com_fillwave_Fillwave_getExecutablePath(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    addPostProcess
 * Signature: (JLjava/lang/String;F)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_addPostProcess
(JNIEnv
*, jobject,
jlong engine, jstring, jfloat
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusKey
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusKey
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusMouseButton
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusMouseButton
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusScroll
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusScroll
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusChar
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusChar
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusCharMods
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusCharMods
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusCursorEnter
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusCursorEnter
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    setFocusCursorPosition
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_setFocusCursorPosition
(JNIEnv
*, jobject,
jlong engine, jlong
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusKey
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusKey(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusMouseButton
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusMouseButton(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusScroll
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusScroll(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusChar
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusChar(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusCharMods
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusCharMods(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusCursorEnter
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusCursorEnter(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusCursorPosition
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusCursorPosition(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    getFocusTouchScreen
 * Signature: (J)J
 */
JNIEXPORT jlong
JNICALL Java_com_fillwave_Fillwave_getFocusTouchScreen(JNIEnv * , jobject, jlong
engine) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
return 0;
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertResizeScreen
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertResizeScreen
(JNIEnv
*, jobject,
jlong engine, jint
screenWidth,
jint screenHeight
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

ptr->
insertResizeScreen(screenWidth, screenHeight
);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputKey
 * Signature: (JLcom/fillwave/Fillwave/KeyboardEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputKey
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputMouseButton
 * Signature: (JLcom/fillwave/Fillwave/MouseButtonEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputMouseButton
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputScroll
 * Signature: (JLcom/fillwave/Fillwave/ScrollEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputScroll
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputCharacter
 * Signature: (JLcom/fillwave/Fillwave/CharacterEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputCharacter
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputCharacterMods
 * Signature: (JLcom/fillwave/Fillwave/CharacterModsEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputCharacterMods
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputCursorEnter
 * Signature: (JLcom/fillwave/Fillwave/CursorEnterEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputCursorEnter
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputCursorPosition
 * Signature: (JLcom/fillwave/Fillwave/CursorPositionEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputCursorPosition
(JNIEnv
*, jobject,
jlong engine, jobject
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

//todo
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    insertInputTouchScreen
 * Signature: (JLcom/fillwave/Fillwave/TouchEvent;)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_insertInputTouchScreen
(JNIEnv
*, jobject,
jlong engine, jlong
x,
jlong y, jlong
action) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

TouchEventData data;
data.
xPos = x;
data.
yPos = y;
TouchEvent event(data);
ptr->
insertInput(event);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerTimeCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerTimeCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerKeyCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerKeyCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerMouseButtonCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerMouseButtonCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerScrollCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerScrollCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerCharCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerCharCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerCharModsCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerCharModsCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerCursorEnterCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerCursorEnterCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}
/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerCursorPositionCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_registerCursorPositionCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    registerTouchScreenCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_attachCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);

Callback *ptrC = reinterpret_cast<Callback *>(callback);

ptr->
attachCallback(ptrC);
}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    unregisterTouchScreenCallback
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_unattachCallback
(JNIEnv
*, jobject,
jlong engine, jlong
callback) {

Engine *ptr = reinterpret_cast<Engine *>(engine);
Callback *ptrC = reinterpret_cast<Callback *>(callback);
ptr->
unattachCallback(ptrC);
}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    clearTimeCallbacks
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_clearCallbacks
(JNIEnv
*, jobject,
jlong engine
) {

Engine *ptr = reinterpret_cast<Engine *>(engine);
EEventType type = EEventType::eTime; /* example */
ptr->

clearCallbacks();

}

/*
 * Class:     com_fillwave_Fillwave
 * Method:    buildScene
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_fillwave_Fillwave_buildTestScene
(JNIEnv
*, jobject,
jlong engine
) {

Engine *e = reinterpret_cast<Engine *>(engine);
ProgramLoader loader(e);
pModel m = pModel(new Model(e, loader.getDefaultBones(), "animations/beast/beast.dae"));

/* Scene */
pScenePerspective s = buildScenePerspective();

/* Camera */
pCameraPerspective c = pCameraPerspective(new CameraPerspective(glm::vec3(0.0, 0.0, 6.0),
                                                                glm::quat(),
                                                                glm::radians(90.0),
                                                                1.0,
                                                                0.1,
                                                                1000.0));
/* Textures */
flw::flf::ps<flw::flf::Text>ure t = e->storeTexture("textures/particle.png");

/* Attach camera to scene */
s->
setCamera(c);

/* Set current scene */
e->
setCurrentScene(s);

/* Particle Emiter */
pIEmiterPoint pe = pIEmiterPoint(new ::EmiterPointCPU(e,
                                                      0.3,
                                                      60000.0,
                                                      glm::vec4(0.1, 0.1, 1.0, 1.0),
                                                      glm::vec3(0.0, 0.0, 0.0),
                                                      glm::vec3(0.0, 0.0, 0.0),
                                                      glm::vec3(0.9, 0.9, 0.9),
                                                      glm::vec3(0.0, 0.0, 0.0),
                                                      glm::vec3(0.0, 0.0, 0.0),
                                                      10.0,
                                                      10.0,
                                                      t,
                                                      GL_SRC_ALPHA,
                                                      GL_ONE,
                                                      GL_FALSE));

s->
attach(pe);

pe->attachHierarchyCallback(new
TimedEmiterUpdateCallback(pe, FILLWAVE_ENDLESS
));
}

#ifdef __cplusplus
}
#endif
