#include "CANTalon.h"
#include "Joystick.h"
class Driving_test{
public:
	Driving_test(CANTalon* _leftMot,CANTalon* _rightMot,Joystick* _leftJoy,Joystick* _rightJoy):leftMot(_leftMot),rightMot(_rightMot),leftJoy(_leftJoy),rightJoy(_rightJoy){
		printf("Subsystem Driving_test init\n");
	}
	~Driving_test();
	void execute(){
		printf("left vel: %f.02 right vel: %f.02 \n left pos: %f.02 right pos: %f.02",leftMot->GetEncVel(),rightMot->GetEncVel(),leftMot->GetEncPosition(),rightMot->GetEncPosition());
	}
private:
	CANTalon* leftMot;
	CANTalon* rightMot;
	Joystick* leftJoy;
	Joystick* rightJoy;
};
