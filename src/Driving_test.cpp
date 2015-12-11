#include "CANTalon.h"
#include "Joystick.h"
#include "Math.h"
class Driving_test{
public:
	Driving_test(CANTalon* _leftMot,CANTalon* _rightMot,Joystick* _leftJoy,Joystick* _rightJoy):leftMot(_leftMot),rightMot(_rightMot),leftJoy(_leftJoy),rightJoy(_rightJoy){
		leftMot->SetPosition(0);
		rightMot->SetPosition(0);
		printf("Subsystem Driving_test init\n");
	}
	~Driving_test();
	void execute(){
		leftMot->Set(leftJoy->GetY());
		rightMot->Set(rightJoy->GetY());
		printf("left vel: %d right vel: %d \n left pos: %d right pos: %d",leftMot->GetEncVel(),rightMot->GetEncVel(),leftMot->GetEncPosition(),rightMot->GetEncPosition());
	}
	void moveFeet(double feet){
		while(leftMot->GetEncPosition()< feet*3.1415*diameter*1000.0){
				leftMot->Set(.5);
				rightMot->Set(.5);
		}
	}
private:
	double diameter=.5;
	CANTalon* leftMot;
	CANTalon* rightMot;
	Joystick* leftJoy;
	Joystick* rightJoy;
};
