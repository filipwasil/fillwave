/*
 * Finishable.h
 *
 *  Created on: Sep 16, 2014
 *      Author: Filip Wasil
 */

#ifndef FINISHABLE_H_
#define FINISHABLE_H_

namespace fillwave {
namespace framework {

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
	bool mFinished;
	float mTimeToFinish;
	float mTimePassed;
	float mPercentageDone;
};

} /* framework */
} /* fillwave */

#endif /* FINISHABLE_H_ */
