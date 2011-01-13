/*
 * Manipulator.h
 *
 *  Created on: Jan 10, 2011
 *      Author: Nick Alberts
 */

#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "WpiLib.h"
#inlcude "nr/thread.h"
#include "nr/diag/debug.h"

class Manipulator : public nr::conc::thread::entry
{

public:
	//constructer with arguments
	Manipulator (Jaguar ArmMotor, Jaguar ClawMotorTop, Jaguar ClawMotorBottom, AnalogInput ArmPotentiometer, AnalogInput ClawPotentiometer){};

	//general run function
	void Run();

	//raise and lower
	void ChangeOrientation();
	//pulls tube in, and pulls tube out
	void Grab();
	void Release();
	//Positions are 1, which corresponds to level, and 2 which corresponds to elevated
	void SetLowerArm(int position);
	double GetTilt();
	void SetUpperArm (double angle);
	int currentPosition;

private:
	nr::conc::mutex object_mutex;

};




#endif /* MANIPULATOR_H_ */
