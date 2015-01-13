#include <libplayerc++/playerc++.h>
#include <iostream>

    using namespace PlayerCc;
    using namespace std;

    std::string  gHostname(PLAYER_HOSTNAME);
    // NOTE !!! PLAYER_PORTNUM is the port number and has to be unique for each student,
   // and be set in the plaer server with -p
    uint32_t        gPort(6677); // Replace this with your port number !!



int main(int argc, char **argv)
{

  // we throw exceptions on creation if we fail
  try {

    PlayerClient robot(gHostname, gPort); // Conect to server
    Position2dProxy pp(&robot, 0);   // Get a motor control device (index is 0)

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true); // Turn on Motors
    double preX = 0.00;
    double preY = 0.00;
    
    // go into  a loop
    for(;;){
	double Xpos = pp.GetXPos();
	double Ypos = pp.GetYPos();
	double newspeed = 0.5;
	double turnrate;
	double dist = sqrt((preX - Xpos)*(preX - Xpos)+(preY - Ypos)*(preY-Ypos));
	double angle = atan2(preY-Ypos,preX-Xpos);
	
	if (dist >0.3){
		double mis = pp.GetYaw() - angle;
		double mie = -1*mis;
		if (((Xpos-preX)>0)&&((Ypos-preY)>0) ){
			if(mie>3.14){turnrate = mie-6.28;}// number 1 space 3.14+mis
			else if(mie<-3.14){turnrate = mie+6.28;}
			else{turnrate = mie;}
			}
		else if(((Xpos-preX)<0)&&((Ypos-preY)<0)){
			if(mis>0){turnrate =  -1*mis;}
			else{turnrate = -1*mis;}}// number 3 space
		else if(((Xpos-preX)<0)&&((Ypos-preY)>0)){
			if(mis<0){turnrate =-1*mis;}
			else{turnrate= -1*mis;}}//number 2space
		else if(((Xpos-preX)>0)&&((Ypos-preY)<0)){
			if(mie>3.14){turnrate = mie-6.28;}//3.14-mis
			else if(mie<-3.14){turnrate = mie +6.28;}
			//else if((mis >-0.01)&&(mis<0.01)){turnrate =0;}
			else{turnrate = mie;}
		}
		
	}
	else{
		turnrate =0;
		newspeed = 0;
		cout << "reached"<<endl;
		//break;
	}
	
	pp.SetSpeed(newspeed, turnrate);
	robot.Read();
	//cout << angle<<"\t"<<turnrate<<"\t"<<pp.GetYaw()<<endl;
      /*double newspeed = 1 ;
      double newturnrate = 0;
      
      for(int e=0;e <= 10;e++){
	pp.SetSpeed(newspeed, newtuFrnrate);
	robot.Read();
	}
      for(int i=0;i <=5 ;i++){
	newturnrate = 1.2;
	pp.SetSpeed(0, newturnrate);
	robot.Read();
	}*/
      // this blocks until new data comes; 10Hz by default
      //robot.Read();

      // write commands to robot
     
    }
  }
  catch (PlayerCc::PlayerError & e) {
    std::cerr << e << std::endl;
    return -1;
  }
}
