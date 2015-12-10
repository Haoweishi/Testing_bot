#include "WPILib.h"
#include "Joystick.h"
#include "CANTalon.h"
#include "Driving_test.cpp"
class Robot: public IterativeRobot
{
private:
	Joystick* leftstick;
	Joystick* rightstick;
	CANTalon* leftMotor;
	CANTalon* rightMotor;
	LiveWindow *lw;
	Driving_test* drive;
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		leftstick=new Joystick(1);
		rightstick=new Joystick(2);
		leftMotor=new CANTalon(3);
		rightMotor=new CANTalon(4);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		drive=new Driving_test(leftMotor,rightMotor,leftstick,rightstick);
	}

	void TeleopPeriodic()
	{
		drive->execute();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
