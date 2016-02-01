#include "WPILib.h"
#include "Joystick.h"
#include "CANTalon.h"
#include "Driving_test.cpp"
#include <String>
#include "CANSpeedController.h"
#include "timer.h"
class Robot: public IterativeRobot
{
private:
	std::string mode;
	Joystick* leftstick;
	Joystick* rightstick;
	CANTalon* leftMotor;
	CANTalon* rightMotor;
	LiveWindow *lw;
	Driving_test* drive;
	void RobotInit()
	{
		printf("testing printf");
		leftMotor=new CANTalon(4,1);
		rightMotor =new CANTalon(3,1);
		leftstick =new Joystick(1);
		rightstick=new Joystick(2);
		lw = LiveWindow::GetInstance();
		drive=new Driving_test(leftMotor,rightMotor,leftstick,rightstick);
	}
	void DisabledInit(){
		printf("finished %s at %f",mode.c_str(),GetTime());
		leftMotor->SetControlMode(defaultMode);
		rightMotor->SetControlMode(defaultMode);
		leftMotor->Set(0);
		rightMotor->Set(0);
	}
	void AutonomousInit()
	{
		printf("AUTO started\n");
		mode="auto";
		drive->moveFeet(10,.45);
		Wait(.5);
		//drive->arc(3.1415,2);
		//TODO fix the arc
		Wait(5);
		printf("AUTO finished\n");
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		mode="Teleop";
	}

	void TeleopPeriodic()
	{
		drive->execute();

	}

	void TestPeriodic()
	{
		lw->Run();
	}
	const CANSpeedController::ControlMode defaultMode=CANSpeedController::kPercentVbus;
};

START_ROBOT_CLASS(Robot);
