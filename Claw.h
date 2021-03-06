/*
 * Claw.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#ifndef CLAW_H_
#define CLAW_H_

#include "WPILib.h"
#include "conc/thread.h"
#include "conc/mutex.h"
#include "diag/ObservableWPI.h"
/**
* @brief Class that controls the claw and gripper
*/

class Claw
{
public:
	
	
	/**
	* @brief Constructs an instance of the claw class.
	*/
	Claw();
	
	/**
	* @brief Runs the claw servos to pull the game piece in.
	*/
	void Grab();
	
	/**
	* @brief Runs the claw servos to push the game piece out.
	*/
	void Release();

	/**
	* @brief Rotates the game piece above the claw.
	*/
	void RotateUp();

	/**
	* @brief Rotates the game piece below the claw.
	*/
	void RotateDown();
		

	Servo clawServoTop4;
	Servo clawServoTop3;
	Servo clawServoBottom1;
	Servo clawServoBottom2;
	
private:
	nr::conc::Thread claw_control_thread;
	nr::conc::Mutex claw_control_mutex;
	static void claw_servo_stop( void* );
	float time;
	bool clawControlRunning;
};

#endif /* CLAW_H_ */
