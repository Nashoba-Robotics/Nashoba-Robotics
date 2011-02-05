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

#include "conc/thread.h"
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
	void Run( void* ) throw ();

private:
	Claw claw;
	Arm arm;
	Joystick &joystick;

	//TODO: fix angle ratio to correspond to actual geometry
	const static double kAngleRatio = 1.0;
};




#endif /* MANIPULATOR_H_ */
