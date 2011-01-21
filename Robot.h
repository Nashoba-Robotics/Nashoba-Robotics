/*
 *	Robot.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"
#include "Drive.h"
#include "LineFollower.h"

class Robot : public SimpleRobot
{
public:
	Robot( void );
	
	void Autonomous( void );
	void OperatorControl( void );
	
private:
	Joystick joy1, joy2;
	Drive drive;
	
	LineFollower lineFollower;
	
	// Constants
	static const float kMainRunLoopDelta = 0.05;
};

START_ROBOT_CLASS(Robot);
