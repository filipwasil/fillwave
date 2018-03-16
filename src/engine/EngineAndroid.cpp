/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Debug  */
#include <fillwave/Config.h>

namespace flw {

EngineAndroid::EngineAndroid(string rootPath) {
  mImpl = make_unique<EngineImpl>(this, rootPath);
  /* This init has to be outside of the initializer list,
  *  because it needs mImpl to be created fully before Initialization.
  *  mImpl uses Engine functions  */
  mImpl->init();
}

EngineAndroid::EngineAndroid(ANativeActivity* activity) {
  mImpl = make_unique<EngineImpl>(this, activity);
  /* This init has to be outside of the initializer list,
  *  because it needs mImpl to be created fully before Initialization.
  *  mImpl uses Engine functions  */
  mImpl->init();
}

Engine::EngineImpl(Engine* engine, std::string rootPath)
: mEngine(engine)
, mFileLoader(rootPath)
, mProgramLoader(engine)
, mFrameCounter(0)
, mTimeFactor(1.0)
, mTextFPSCallback(nullptr)
, mStartupTime(0.0f)
, mIsOQ(GL_FALSE)
, mBackgroundColor(0.1, 0.1, 0.1) {
}

Engine::EngineImpl(Engine* engine, ANativeActivity* activity)
: mEngine(engine)
, mFileLoader(activity->internalDataPath)
, mProgramLoader(engine)
, mFrameCounter(0)
, mTimeFactor(1.0)
, mTextFPSCallback(nullptr)
, mStartupTime(0.0f)
, mIsOQ(GL_FALSE)
, mBackgroundColor(0.1, 0.1, 0.1) {

  flf::androidSetActivity(activity);

  flf::androidExtractAll();
}

/* flw  */
