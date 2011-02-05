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
#include "diag/observable_wpi.h"

class Claw
{
public:
	Claw();
	void ChangeOrientation();
	// pulls tube in, and pulls tube out
	void Grab();
	void Release();
	void RotateUp();
	void RotateDown();
private:
	Servo clawServoTop1;
	Servo clawServoTop2;
	Servo clawServoBottom1;
	Servo clawServoBottom2;
	nr::conc::thread claw_control_thread;
	nr::conc::mutex claw_control_mutex;
	static void claw_servo_stop( void* );
};

#endif /* CLAW_H_ */
