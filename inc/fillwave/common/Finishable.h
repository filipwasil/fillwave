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
	 * setFinished
	 * \brief Sets indicator that the object was finished.
	 */
	void setFinished(bool state);

	/*
	 * getFinished
	 * \brief Returns state of the object.
	 */
	bool getFinished() const;

 protected:
	bool mFinished;
	float mTimeToFinish;
	float mTimePassed;
	float mPercentageDone;
};

} /* framework */
} /* fillwave */

#endif /* FINISHABLE_H_ */
