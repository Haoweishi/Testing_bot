#include "CANTalon.h"
#include "Joystick.h"
#include "Math.h"
class Driving_test{
public:
	Driving_test(CANTalon* _leftMot,CANTalon* _rightMot,Joystick* _leftJoy,Joystick* _rightJoy):leftMot(_leftMot),rightMot(_rightMot),leftJoy(_leftJoy),rightJoy(_rightJoy){
		resetPos();
		printf("Subsystem Driving_test init\n");
	}
	void resetPos(){
		setRightPos(0);
		setLeftPos(0);
	}
	void setRightPos(double d){
		leftMot->SetPosition(d-leftMot->GetEncVel());
	}
	void setLeftPos(double d){
		rightMot->SetPosition(d-rightMot->GetEncVel());
	}
	~Driving_test();
	void execute(){
		leftMot->Set(leftJoy->GetY());
		rightMot->Set(rightJoy->GetY());
	}
	void moveFeet(double feet=1,double speed=.5){
		resetPos();
		printf("moving %f feet", feet);
		int destination=abs(feet/(3.1415*diameter)*1000.0);
		while(abs(leftMot->GetEncPosition())< destination){
			//note on syntax boolean?x:y returns x if boolean is true and y if boolean is false
			leftMot->Set((feet>0?-speed:speed)*(1-abs(leftMot->GetEncPosition())/destination)*.85);
			rightMot->Set((feet>0?speed:-speed)*(1-abs(leftMot->GetEncPosition())/destination));
			printf("left:%d  right%d \n",abs(leftMot->GetEncPosition()),abs(rightMot->GetEncPosition()));
		}
		printf("done moving straight");
		leftMot->Set(0);rightMot->Set(0);
	}

private:
	//all units are in feet.
	const double diameter=.5;
	CANTalon* leftMot;
	CANTalon* rightMot;
	Joystick* leftJoy;
	Joystick* rightJoy;
	//wheel to wheel width of robot
	const double width=3.0;
};
