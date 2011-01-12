/*
 *	Claw.h
 *	Nashoba Robotics 2011
 */

#pragma once

class Claw
{
public:
	void RotateTubeTo( float angle );
	void ReleaseTube();
	void GrabTube();
	
	// Constants
	const int kTopGearRatio = 0.6;
	const int kBottomGearRatio = 0.6;
};