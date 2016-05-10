/*
 * Finishable.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FINISHABLE_H_
#define FINISHABLE_H_

namespace fillwave {
namespace framework {

constexpr float FILLWAVE_ENDLESS = 0.0f;

/*! \class Finishable
 * \brief Base for every finishable callback.
 */
class Finishable {
 public:
	Finishable(float timeToFinish);
	virtual ~Finishable() = default;

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

} /* framework */
} /* fillwave */

#endif /* FINISHABLE_H_ */
