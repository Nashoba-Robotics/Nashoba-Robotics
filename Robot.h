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
#include "Manipulator.h"

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
	
	/**
	 *	@brief Align the robot with the pole using the IR Range Finder
	 */
	void AlignWithPole( void );
	
private:
	Joystick joy1, joy2, manipulatorJoystick;
	Drive drive;
	
	LineFollower lineFollower;
	
	Manipulator manipulator;
	Compressor compressor;
	
	Ultrasonic ultrasonic;
	Gyro gyro;
	
	AnalogChannel leftRangeFinder, centerRangeFinder, rightRangeFinder;
	DigitalOutput cameraLight;
	// Constants
	static const float kMainRunLoopDelta = 0.05;
};

START_ROBOT_CLASS(Robot);
