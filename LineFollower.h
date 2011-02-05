/*
 *	LineFollower.h
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#pragma once

#include "WPILib.h"

/**
 *	\brief Class to follow lines
 */
class LineFollower
{
public:
	typedef DigitalInput LightSensor;
	
	/**
	 *	@brief Creates a new line follower with the given sensors
	 *	@param sensor1Channel The channel of the first (leftmost) optical sensor
	 *	@param sensor2Channel The channel of the second (middle) optical sensor
	 *	@param sensor3Channel The channel of the third (rightmost) optical sensor
	 *	@param gyroChannel The channel of the gyroscope
	 */
	LineFollower( UINT8 sensor1Channel,
			UINT8 sensor2Channel,
			UINT8 sensor3Channel,
			UINT8 gyroChannel );
	
	/**
	 *	@brief Creates a new line follower with the given sensors
	 *	@param sensor1Slot The slot of the first (leftmost) optical sensor
	 *	@param sensor1Channel The channel of the first (leftmost) optical sensor
	 *	@param sensor2Slot The slot of the second (middle) optical sensor
	 *	@param sensor2Channel The channel of the second (middle) optical sensor
	 *	@param sensor3Slot The slot of the third (rightmost) optical sensor
	 *	@param sensor3Channel The channel of the third (rightmost) optical sensor
	 *	@param gyroSlot The slot of the gyroscope
	 *	@param gyroChannel The channel of the gyroscope
	 */
	LineFollower( UINT8 sensor1Slot, UINT8 sensor1Channel,
			UINT8 sensor2Slot, UINT8 sensor2Channel,
			UINT8 sensor3Slot, UINT8 sensor3Channel,
			UINT8 gyroSlot, UINT8 gyroChannel );
	
	/**
	 *	@brief The field side
	 */
	enum FieldSide {
		kScoringSide, /*!< The near side, which we score on */
		kDefendingSide /*!< The far side, which we prevent others from scoring on */
	};
	
	/**
	 *	@brief Gets if the line is detected
	 */
	bool IsLineDetected();
	
	/**
	 *	@brief Waits until the line is detected
	 */
	void WaitUntilLineDetected();
	
	/**
	 *	@brief Waits until the line is detected or this times out
	 *	@param timeout The timeout to wait, in seconds (fractions are permissible)
	 *	@return true if the line is detected, false if the timeout was triggered
	 */
	bool WaitUntilLineDetectedOrTimeout( double timeout );
	
	/**
	 *	@brief Wait until facing the side of the field
	 *	@param side The side of the field to wait for
	 */
	void WaitUntilFacing( FieldSide side );
	
	/**
	 *	@brief Initializes the diagnostics code for the devices
	 */
	void InitializeDiagnostics();
	
	LightSensor sensor1, sensor2, sensor3;
	
private:
	static const float kWaitDelta = 0.01;
	static const float kAngleError = 5.0f;
	
//	Gyro gyroscope;
};
