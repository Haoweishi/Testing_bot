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
	void moveFeet(double feet=1,double speed=.1){
		leftMot->SetPosition(0);
		rightMot->SetPosition(0);
		printf("moving %f feet", feet);
		while(abs(leftMot->GetEncPosition())< abs(feet/(3.1415*diameter)*1000.0)){
			//note on syntax boolean?x:y returns x if boolean is true and y if boolean is false
			leftMot->Set(feet>0?speed:-speed);rightMot->Set(feet>0?speed:-speed);
		}
		printf("done moving straight");
		leftMot->Set(0);
		rightMot->SetControlMode(rightMot->kPercentVbus);
	}
	//@param theta is in radians, radius is in feet, omega is center speed.
	void arc(double theta=(3.1415/2),double radius=1,double omega=.1,bool left=true){
		radius=abs(radius);
		leftMot->SetPosition(0);
		rightMot->SetPosition(0);
		printf("moving to %f feet away curved to %s",radius*sqrt(2),left?"left":"right");
		const double arcLengthLeft=(radius-left?width:-width/2)*theta;
		const double arcLengthRight=(radius+left?width:-width/2)*theta;
		while(left?rightMot->GetEncPosition()<arcLengthRight:leftMot->GetEncPosition()<arcLengthLeft){
			leftMot->Set(omega*(radius-(left?(width/2):(-width/2))));
			rightMot->Set(omega*(radius+(left?(width/2):(-width/2))));
		}
		leftMot->Set(0);
		rightMot->Set(0);
		printf("finished the arc");
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
