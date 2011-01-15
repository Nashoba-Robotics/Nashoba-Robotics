/*
 *	Robot.h
 *	Nashoba Robotics 2011
 */

#pragma once

#include "WPILib.h"
#include "CAN/CANJaguar.h"

class Robot : public SimpleRobot
{
private:
	Joystick joy1, joy2;
	CANJaguar motor1, motor2, motor3, motor4;
	RobotDrive drive;
	
	LineFollower lineFollower;
	
	// Constants
	const float kMainRunLoopDelta = 0.05;
};

START_ROBOT_CLASS(Robot);
