/*
 * Copyright 2013 The Android Open Source Project
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
 */

package com.fillwave;

import android.content.Context;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.EditText;


public class FillwaveView extends GLSurfaceView {

	public Fillwave mFillwave;

	public long mEngine;

	private String mRootPath;

    public FillwaveView(Context context, String rootPath) {
        super(context);

        mRootPath = rootPath;

        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 3.0 or later backwards-compatible versions.
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);
        setRenderer(new Renderer());
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
    	int type = 0;
        switch (event.getAction()) {
	        case MotionEvent.ACTION_MOVE:
	        	type = 1;
	        	break;
	        case MotionEvent.ACTION_UP:
	        	type = 2;
	        	break;
	        case MotionEvent.ACTION_DOWN:
	        	type = 0;
	        	break;
        }
    	if (event.getAction() == MotionEvent.ACTION_DOWN) {
    	   mFillwave.insertInputTouchScreen(mEngine, (int)event.getX(), (int)event.getY(), type);
    	}
    	return super.onTouchEvent(event);
    }
    
    private class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 unused) {
        	mFillwave.draw(mEngine);
        }

        public void onSurfaceChanged(GL10 unused, int width, int height) {
        	mFillwave.insertResizeScreen(mEngine, width, height);
        }

        public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        	mFillwave = new Fillwave();
        	mEngine = mFillwave.createEngine(mRootPath);
        	mFillwave.configureFPSCounter(mEngine, "fonts/bridgenorth", -0.95f, -0.8f, 100.0f);
        	mFillwave.buildTestScene(mEngine);
        }
    }
}