#pragma once

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

namespace flw {
namespace flf {

constexpr float FILLWAVE_ENDLESS = 0.0f;

/*! \class Finishable
 * \brief Base for every finishable callback.
 */
class Finishable {
public:
  Finishable(float timeToFinish);

  virtual ~Finishable();

  Finishable(const Finishable& arg);

  Finishable& operator= (const Finishable& postProcessingPass);

  /*
   * checkTime
   * \brief checks if the lifetime time elapsed
   */
  void checkTime(float timePassed);

  /*
   * getPercentageDone
   * \brief returns the time progress in percentages
   */
  float getPercentageDone() const;

  /*
   * finish
   * \brief Sets indicator that the object was finished
   */
  void finish();

  /*
   * finish
   * \brief Sets indicator that the object is not finished
   */
  void reset();

  /*
   * finish
   * \brief Returns state of the object
   */
  bool isFinished() const;

protected:
  bool mFinished;
  float mTimeToFinish;
  float mTimePassed;
  float mPercentageDone;
};

} /* flf */
} /* flw */
