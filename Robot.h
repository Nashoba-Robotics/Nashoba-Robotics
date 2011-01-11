/*
 *  Robot.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "WPILib.h"

class Robot : public SimpleRobot
{
public:
	Robot();
	
	void Autonomous( void );
	void OperatorControl( void );
	
private:
	Joystick primaryJoystick,
			 secondaryJoystick;
};

// Macro required to start the robot
// This basically generates a main() function.
START_ROBOT_CLASS(Robot);
