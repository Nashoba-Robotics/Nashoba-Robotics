/*
 *  Robot.h
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#pragma once

#include "WPILib.h"
#include "Drive.h"
#include "LineFollower.h"

/**
 *	\brief The robot class
 *	This class contains all of the `entry points', or places where the code starts
 */
class Robot : public SimpleRobot
{
public:
	/**
	 *	\brief Sets up other objects used by the robot
	 *	The objects set up are not particular to either autonomous or teleoperated (or do both)
	 */
	Robot( void );
	
	/**
	 *	\brief The autonomous mode entry
	 *	When autonomous mode starts, this method is called
	 */
	void Autonomous( void );
	
	/**
	 *	\brief The teleoperated mode entry
	 *	When teleoperated mode starts, this method is called
	 */
	void OperatorControl( void );
	
private:
	Joystick joy1, joy2;
	Drive drive;
	
	LineFollower lineFollower;
	
	// Constants
	static const float kMainRunLoopDelta = 0.05;
};

START_ROBOT_CLASS(Robot);
