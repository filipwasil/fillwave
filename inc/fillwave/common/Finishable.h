/*
 * Finishable.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Filip Wasil
 */

#ifndef FINISHABLE_H_
#define FINISHABLE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

namespace fillwave {
namespace common {

#define FILLWAVE_ENDLESS 0

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
	float mPercentageDone;
	float mTimeToFinish;
	float mTimePassed;
	bool mFinished;
};

} /* common */
} /* fillwave */

#endif /* FINISHABLE_H_ */
