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
	LineFollower( uint8_t sensor1Channel,
				  uint8_t sensor2Channel,
				  uint8_t sensor3Channel,
				  uint8_t gyroChannel );
	LineFollower( uint8_t sensor1Slot, uint8_t sensor1Channel,
				  uint8_t sensor2Slot, uint8_t sensor2Channel,
				  uint8_t sensor3Slot, uint8_t sensor3Channel,
				  uint8_t gyroSlot, uint8_t gyroChannel );
	LineFollower( LightSensor &s1,
				  LightSensor &s2,
				  LightSensor &s3,
				  Gyro &gyro );
	
	enum FieldSide { kScoringSide, kDefendingSide };
	
	bool IsLineDetected();
	
	void WaitUntilLineDetected();
	bool WaitUntilLineDetectedOrTimeout( float timeout );
	
	void WaitUntilFacing( FieldSide side );
	
private:
	static const float kWaitDelta = 0.005;
	static const float kAngleError = 5.0f;
	
	LightSensor sensor1, sensor2, sensor3;
	Gyro gyroscope;
};