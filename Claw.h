/*
<<<<<<< HEAD
 * Claw.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Nick Alberts
 */

#ifndef CLAW_H_
#define CLAW_H_
=======
 *	Claw.h
 *	Nashoba Robotics 2011
 */

#pragma once
>>>>>>> 83d07d249ae3b4e66502441270b70214f77a6d2c

class Claw
{
public:
<<<<<<< HEAD
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
=======
	void RotateTubeTo( float angle );
	void ReleaseTube();
	void GrabTube();
	
	// Constants
	const int kTopGearRatio = 0.6;
	const int kBottomGearRatio = 0.6;
};
>>>>>>> 83d07d249ae3b4e66502441270b70214f77a6d2c
