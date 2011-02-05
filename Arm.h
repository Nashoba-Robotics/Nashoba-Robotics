/*
 * Arm.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#ifndef ARM_H_
#define ARM_H_

#include "WPILib.h"
#include "conc/thread.h"
#include "conc/mutex.h"
#include "diag/observable_wpi.h"

class Arm
{
public:
	// Positions are 1, which corresponds to level, and 2 which corresponds to elevated
	Arm();
	void SetLowerArm( bool position );
	double GetTilt();
	void SetUpperArm( double angle );
	bool lowerArm;

private:
	double upperArmAngle;
	Jaguar armMotor;
	Solenoid armSolenoidRaise;
	Solenoid armSolenoidLower;
	Encoder armEncoder;
	nr::conc::thread arm_control_thread;
	nr::conc::mutex arm_control_mutex;
	// TODO: Determine this value
	static const float kCloseEnough = 5.0;
	static void control_arm_motor ( void* );
	volatile double arm_control_angle;
};

#endif /* ARM_H_ */
