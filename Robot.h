/*
 *	Robot.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"

class Robot : public SimpleRobot
{
	Joystick joy1, joy2;
	Jaguar motor1, motor2, motor3, motor4;
	RobotDrive drive;
	
	// Constants
	const float kMainRunLoopDelta = 0.05;
};

START_ROBOT_CLASS(Robot);
