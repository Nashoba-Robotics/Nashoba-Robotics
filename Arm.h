/*
 * Arm.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#ifndef ARM_H_
#define ARM_H_

#include "WPILib.h"
#include "conc/Thread.h"
#include "conc/Mutex.h"
#include "diag/ObservableWPI.h"

/**
* @brief Class that controls the upper and lower arms. 
*/

class Arm
{
public:
	/**
	* @brief Constructs an instance of the arm class.
	*/
	Arm();

	/**
	 * @brief simple lower arm function
	 */
	void SimpleUpperArm (float value);
	
	/**
	 * @brief Moves the lower arm to the given position.
	 * @param position The desired position of the lower arm, where true corresponds to raiseed and false corresponds to lowered.
	 */
	void SetLowerArm( bool position );
	
	/**
	* @brief Returns the current angle of the upper arm
	*/
	double GetTilt();
	
	/**
	* @brief Begins to move the upper arm to the desired angle.
	* @param angle The desired angle of the upper arm
	*/
	void SetUpperArm( double angle );
	
	/*
	* @brief The current position of the lower arm 
	*/
	bool lowerArm;

private:
	double upperArmAngle;
	CANJaguar armMotor;
	Solenoid armSolenoidRaise;
	Solenoid armSolenoidLower;
	Encoder armEncoder;
	nr::conc::Thread arm_control_thread;
	nr::conc::Mutex arm_control_mutex;
	// TODO: Determine this value
	static const float kCloseEnough = 5.0;
	static void control_arm_motor ( void* );
	volatile double arm_control_angle;
};

#endif /* ARM_H_ */
