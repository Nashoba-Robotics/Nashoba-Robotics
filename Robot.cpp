/*
 *  Robot.cpp
 *  Nashoba Robotics 2011
 *
 *  Copyright 2011 RC Howe
 *  All Rights Reserved
 */

#include "Robot.h"
#include "Arm.h"
#include "diag/DiagnosticsCenter.h"
#include "diag/ObservableWPI.h"
 
Robot :: Robot( void )
:	joy1( 1 ), joy2( 2 ),
	manipulatorJoystick( 3 ),
	drive( 1, 2, 3, 4, 4, 4, 4, 5, 4, 6, 4, 7 ),
	lineFollower( 1, 2, 3, 8 ),
	manipulator( manipulatorJoystick ),
	compressor( 4, 12, 4, 2 ),
	ultrasonic( 14, 13 ),
	leftRangeFinder( 1, 2 ),
	centerRangeFinder( 1, 3 ),
	rightRangeFinder( 1, 4 ),
	gyro( 1, 1 ),
	cameraLight( 8 )
{
	cameraLight.Set( false );
	compressor.Start();
	nr::conc::Thread th( &manipulator );
	th.Start();
	
	gyro.Reset();
	
	nr::diag::SharedDiagnosticsCenter().RegisterDevice( new nr::diag::ObservableAnalogChannel( leftRangeFinder ), "Left IR Range Finder" );
	nr::diag::SharedDiagnosticsCenter().RegisterDevice( new nr::diag::ObservableAnalogChannel( centerRangeFinder ), "Center IR Range Finder" );
	nr::diag::SharedDiagnosticsCenter().RegisterDevice( new nr::diag::ObservableAnalogChannel( rightRangeFinder ), "Right IR Range Finder" );
	
	nr::diag::SharedDiagnosticsCenter().RegisterDevice( new nr::diag::ObservableGyroscope( gyro ), "Gyroscope" );
}

void Robot :: Autonomous( void )
{
	GetWatchdog().SetEnabled( false );
	
	bool pastY = true;
	double speed = 1.0;
	
	while ( IsAutonomous() )
	{
		if ( ultrasonic.GetRangeInches() < 60.0 )
			speed = 0.6;
		else
			speed = 1.0;
		
		if ( pastY && lineFollower.sensor1.Get() && lineFollower.sensor2.Get() && lineFollower.sensor3.Get() )
		{
			drive.TankDrive( 0.3, 0.3 );
			Wait( 2.2 );
			drive.TankDrive( 0.0, 0.0 );
			
			// Raise the claw
			manipulator.arm.SetUpperArm( Arm::kTopMiddleRung );
			Wait(0.2);
			manipulator.arm.SetLowerArm( true );
			
			
			// Drive forwards slightly
			drive.TankDrive( -0.3, -0.3 );
			Wait( 0.4 );
			drive.TankDrive( 0.0, 0.0 );

			Wait( 6.5 );
			// Spit out the tube
			manipulator.claw.RotateDown();
			Wait(0.3f);
			manipulator.claw.Release();
			
			return;
		}
		else if ( lineFollower.sensor2.Get() )
			drive.TankDrive( -0.6 * speed, -0.6 * speed );
		else if ( lineFollower.sensor3.Get() && lineFollower.sensor1.Get() )
		{
			drive.TankDrive( -0.6 * speed, 0.6 * speed );
			Wait( 0.2 );
			pastY = true;
		}
		else if ( lineFollower.sensor3.Get() )
			drive.TankDrive( -0.6 * speed, 0.1 * speed );
		else if ( lineFollower.sensor1.Get() )
			drive.TankDrive( 0.1 * speed, -0.6 * speed );
		
		Wait( 0.001 );
	}
}

void Robot :: OperatorControl( void )
{
	GetWatchdog().SetEnabled( false );
	
	while ( IsOperatorControl() )
	{
		drive.TankDrive( joy1.GetY(), joy2.GetY() );
		
		if ( joy1.GetRawButton( 11 ) )
		{
			AlignWithPole();
			return;
		}
		Wait( kMainRunLoopDelta );
	}
}

void Robot :: AlignWithPole( void )
{
	/*
	const INT16 kPeakSlopeThreshold = 10;
	
	drive.TankDrive( 0.4, 0.0 );
	
	INT16 peak = 0;
	INT16 value;
	
	INT16 lastValue = 0;
	bool pastPeak = false;
	
	while ( true )
	{
		value = centerRangeFinder.GetVoltage();
		if ( value > 0.2 )
			drive.TankDrive( 0.4, 0.4 );
		else
			drive.TankDrive( 0.4, 0.0 );
		
		if ( value > 0.9 )
			break;
		
		Wait( 0.05 );
	}
	
	drive.TankDrive( 0, 0 );
	*/
	
	while ( true )
	{
		if ( centerRangeFinder.GetVoltage() > 0.15 )
			drive.TankDrive( 0.35, 0.35 );
		else if ( rightRangeFinder.GetVoltage() > 0.15 )
			drive.TankDrive( 0.4, 0.0 );
		else if ( leftRangeFinder.GetVoltage() > 0.15 )
			drive.TankDrive( 0.0, 0.4 );
		
		if ( centerRangeFinder.GetVoltage() > 0.7 )
		{
			// Deploy
			drive.TankDrive( 0.0, 0.0 );
			break;
		}
	}
}
