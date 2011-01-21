/*
 *	LineFollower.h
 *	Nashoba Robotics 2011
 *
 *	Copyright 2011 RC Howe
 *	All Rights Reserved
 */

#pragma once

#include "WPILib.h"

class LineFollower
{
public:
	typedef DigitalInput LightSensor;
	
	LineFollower( UINT8 sensor1Channel,
			UINT8 sensor2Channel,
			UINT8 sensor3Channel,
			UINT8 gyroChannel );
	LineFollower( UINT8 sensor1Slot, UINT8 sensor1Channel,
			UINT8 sensor2Slot, UINT8 sensor2Channel,
			UINT8 sensor3Slot, UINT8 sensor3Channel,
			UINT8 gyroSlot, UINT8 gyroChannel );
	
	enum FieldSide { kScoringSide, kDefendingSide };
	
	bool IsLineDetected();
	
	void WaitUntilLineDetected();
	bool WaitUntilLineDetectedOrTimeout( double timeout );
	
	void WaitUntilFacing( FieldSide side );
	
private:
	static const float kWaitDelta = 0.005;
	static const float kAngleError = 5.0f;
	
	LightSensor sensor1, sensor2, sensor3;
	Gyro gyroscope;
};
