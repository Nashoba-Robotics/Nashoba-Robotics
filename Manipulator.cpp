/*
 * manipulator.cpp
 *
 *  Created on: Jan 10, 2011
 *      Author: Nick Alberts
 */

#include "Manipulator.h"

Manipulator::Manipulator (Jaguar ArmMotor, Jaguar ClawMotorTop, Jaguar ClawMotorBottom, AnalogInput ArmPotentiometer, AnalogInput ClawPotentiometer){};

{

}

void Manipulator::Run()
{

}

void Manipulator::ChangeOrientation()
{

}

void Manipulator::Grab()
{
	clawMotorBottom.Set(.2);
		clawMotorTop.Set(.2);
		Wait(.7);
		clawMotorBottom.Set(0);
		clawMotorTop.Set(0);
}

void Manipulator::Release()
{
	clawMotorBottom.Set(-.2);
		clawMotorTop.Set(-.2);
		Wait(.7);
		clawMotorBottom.Set(0);
		clawMotorTop.Set(0);
}

void Manipulator::SetLowerArm(int position)
{

}

void Manipulator::SetUpperArm(double angle)
{

}
//Rough
double Manipulator::GetTilt()
{
//actual code
	return tilt;

}

