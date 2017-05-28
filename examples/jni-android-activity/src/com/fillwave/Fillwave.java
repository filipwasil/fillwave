package com.fillwave;

import java.util.Vector;


public class Fillwave {

   public class Vector3f {
         public float x;
         public float y;
         public float z;
   }
   
   public class Vector4f {
       public float x;
       public float y;
       public float z;
       public float w;
 }

   public class Vector2i {
       public int x;
       public int y;
   }
   
   public class PhysicsMeshBuffer {
	   public int mNumFaces;
	   public Vector<Vector3f> mVertices;
//	   public Vector<int> mIndices;
   }
   
   public class Quaternion {
	   public float x;
	   public float y;
	   public float z;
	   public float w;
   }
   
   public class KeyboardEvent {

   }

   public class MouseButtonEvent {

   }
   
   public class ScrollEvent {

   }
   
   public class CharacterEvent {

   }
   
   public class CharacterModsEvent {

   }
   
   public class CursorEnterEvent {

   }
   
   public class CursorPositionEvent {

   }
   
   public class TouchEvent {
      public TouchEvent(float X, float Y) {
    	  x = X;
    	  y = Y;
      }
      float x;
      float y;
   }

   public native long createEngine(String rootPath);
   public native void deleteEngine(long engine);

          /* Configuration */
   public native void configureDebugger(long engine, int state);
   public native void configureFileLogging(long engine, String fileName /*= ""*/);
   public native void configFPSCounter(long engine,
		                                  String fontName/* = ""*/,
                                          float xPosition/* = -0.95*/,
                                          float yPosition /*= 0.95*/,
                                          float size /*= 100.0*/);
   public native void configureBackgroundColor(long engine, Vector3f color);
   public native void configureTime(long engine, float timeFactor);

          /* Draw */
   public native void draw(long engine);
   public native void drawLines(long engine, float time);
   public native void drawPoints(long engine, float time);
   public native void drawTexture(long engine, long t, long p);

          /* Assets */
   public native PhysicsMeshBuffer getPhysicalMeshBuffer(long engine, String shapePath);
   public native long getLightManager(long engine);

   /* Scene */
   public native void setCurrentScene(long engine, long scene);
   public native long getCurrentScene(long engine);

   /* Time */
   public native int getFramesPassed(long engine);

   /* Store shaders */
   //   public native long storeShaderCompute(String shaderPath);
   public native long storeShaderFragment(long engine, String shaderPath);
   public native long storeShaderVertex(long engine, String shaderPath);
   //   public native long storeShaderCompute(String shaderPath, String shaderSource);
   public native long storeShaderFragment(long engine, String shaderPath, String shaderSource);
   public native long storeShaderVertex(long engine, String shaderPath, String shaderSource);
//   public native long storeProgram(String name, Vector<long> shaders, boolean skipLinking);

   /* Store textures */
   public native long storeTexture(long engine, String texturePath, int mapType);
   public native long storeTextureDynamic(long engine, String fragmentShaderPath);
   public native long storeTexture3D(long engine, String posX,
                                    String negX,
                                    String posY,
                                    String negY,
                                    String posZ,
                                    String negZ);

          /* Store lights */
   public native long storeLightSpot(long engine,
		                             Vector3f position,
		                             Quaternion rotation,
		                             Vector4f color,
                                     long entity);
   public native long storeLightPoint(long engine,
		                              Vector3f position,
                                      Vector4f color,
                                      long entity);
   public native long storeLightDirectional(long engine,
		                                    Vector3f position,
		                                    Quaternion rotation,
                                            Vector4f color,
                                            long entity);

          /* Store text */
   public native long storeText(long engine,
                          String content,
                          String fontName,
                          float startingPositionX,
                          float startingPositionY,
                          float scale,
                          Vector4f color,
                          int effect);
   public native void clearText(long engine, long text);
   public native void clearLightSpot(long engine, long light);
   public native void clearLightDirectional(long engine, long light);
   public native void clearLightPoint(long engine, long light);
   public native void clearLights(long engine);

          /* Picking */
   public native void pick(long engine, int x, int y);

          /* Screen */
   public native Vector2i getScreenSize(long engine);

          /* Log */
   public native void log(long engine);

          /* Screenshot */
   public native void captureFramebufferToFile(long engine, String name);
//   public native void captureFramebufferToBuffer(GLubyte* buffer,
//                                                int* sizeInBytes,
//                                                unsigned int format,
//                                                int bytesPerPixel);

   /* File system */
   public native String getExecutablePath(long engine);

   /* Post processing */
   public native void addPostProcess(long engine, String fragmentShaderPath, float lifeTime);

   /* Inputs - setFocus */
   public native void setFocusKey(long engine, long entity);
   public native void setFocusMouseButton(long engine, long entity);
   public native void setFocusScroll(long engine, long entity);
   public native void setFocusChar(long engine, long entity);
   public native void setFocusCharMods(long engine, long entity);
   public native void setFocusCursorEnter(long engine, long entity);
   public native void setFocusCursorPosition(long engine, long entity);

   /* Inputs - getFocus */
   public native long getFocusKey(long engine);
   public native long getFocusMouseButton(long engine);
   public native long getFocusScroll(long engine);
   public native long getFocusChar(long engine);
   public native long getFocusCharMods(long engine);
   public native long getFocusCursorEnter(long engine);
   public native long getFocusCursorPosition(long engine);
   public native long getFocusTouchScreen(long engine);

   /* Inputs - insert */
   public native void insertResizeScreen(long engine, int width, int height);
   public native void insertInputKey(long engine, KeyboardEvent event);
   public native void insertInputMouseButton(long engine, MouseButtonEvent event);
   public native void insertInputScroll(long engine, ScrollEvent   event);
   public native void insertInputCharacter(long engine, CharacterEvent event);
   public native void insertInputCharacterMods(long engine, CharacterModsEvent event);
   public native void insertInputCursorEnter(long engine, CursorEnterEvent event);
   public native void insertInputCursorPosition(long engine, CursorPositionEvent event);
   public native void insertInputTouchScreen(long engine, int x, int y, int action);

   /* Inputs - register */
   public native void registerTimeCallback(long engine, long callback);
   public native void registerKeyCallback(long engine, long callback);
   public native void registerMouseButtonCallback(long engine, long callback);
   public native void registerScrollCallback(long engine, long callback);
   public native void registerCharCallback(long engine, long callback);
   public native void registerCharModsCallback(long engine, long callback);
   public native void registerCursorEnterCallback(long engine, long callback);
   public native void registerCursorPositionCallback(long engine, long callback);
   public native void registerTouchScreenCallback(long engine, long callback);

   /* Inputs - unregister */
   public native void unregisterTimeCallback(long engine, long callback);
   public native void unregisterKeyCallback(long engine, long callback);
   public native void unregisterMouseButtonCallback(long engine, long callback);
   public native void unregisterScrollCallback(long engine, long callback);
   public native void unregisterCharCallback(long engine, long callback);
   public native void unregisterCharModsCallback(long engine, long callback);
   public native void unregisterCursorEnterCallback(long engine, long callback);
   public native void unregisterCursorPositionCallback(long engine, long callback);
   public native void unregisterTouchScreenCallback(long engine, long callback);

   /* Inputs - clear */
   public native void clearTimeCallbacks(long engine);
   public native void clearKeyCallbacks(long engine);
   public native void clearMouseButtonCallbacks(long engine);
   public native void clearScrollCallbacks(long engine);
   public native void clearCharCallbacks(long engine);
   public native void clearCharModsCallbacks(long engine);
   public native void clearCursorEnterCallbacks(long engine);
   public native void clearCursorPositionCallbacks(long engine);
   public native void clearTouchScreenCallbacks(long engine);
   public native long buildTestScene(long engine);

   static {
      System.loadLibrary("fillwaveJNI");
   }
}
