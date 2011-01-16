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

private:
	Jaguar clawMotorTop;
	Jaguar clawMotorBottom;
	nr::conc::thread claw_control_thread;
	nr::conc::mutex claw_mutex;
	static void claw_motor_stop();
};

#endif /* CLAW_H_ */
