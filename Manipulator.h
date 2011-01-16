/*
 *	Manipulator.h
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 Nick Alberts
 *	All Rights Reserved
 */

#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "WPILib.h"

#include "nr/thread.h"
#include "nr/diag/debug.h"

#include "Claw.h"
#include "Arm.h"

class Manipulator : public nr::conc::thread::entry
{
public:
	/**
	 * Creates a new manipulator object
	 * @param joy The joystick to dedicate to the manipulator
	 */
	Manipulator( Joystick &joy );

	/**
	 * The thread entry function
	 */
	void Run();

private:
	Claw claw;
	Arm arm;
	Joystick joystick;

};




#endif /* MANIPULATOR_H_ */
