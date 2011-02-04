/*
 * Claw.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#ifndef CLAW_H_
#define CLAW_H_

class Claw
{
public:
	void ChangeOrientation();
	// pulls tube in, and pulls tube out
	void Grab();
	void Release();
	void RotateUp();
	void RotateDown();
private:
	Servo clawServoTop;
	Servo clawServoBottom;
	nr::conc::thread claw_control_thread;
	nr::conc::mutex claw_mutex;
	static void claw_motor_control();
};

#endif /* CLAW_H_ */
