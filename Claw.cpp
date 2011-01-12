/*
 *	Claw.cpp
 *	Nashoba Robotics 2011
 */

void Claw :: RotateTubeTo( float angle )
{
	topServo.SetAngle( angle * kTopGearRatio );
	bottomServo.SetAngle( angle * kBottonGearRatio );
}

void Claw :: ReleaseTube()
{
	topServo.SetAngle( Servo::GetMaxAngle() )
	bottomServo.SetAngle( Servo::GetMinAngle() );
}

void Claw :: GrabTube()
{
	topServo.SetAngle( Servo::GetMaxAngle() )
	bottomServo.SetAngle( Servo::GetMinAngle() );
}