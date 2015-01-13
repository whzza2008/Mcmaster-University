#include <libplayerc++/playerc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

    using namespace PlayerCc;

    std::string  gHostname(PlayerCc::PLAYER_HOSTNAME);
    // NOTE !!! PLAYER_PORTNUM is the port number and has to be unique for each student,
   // and be set in the plaer server with -p
    uint32_t        gPort(6888); // Replace this with your port number !!



int main(int argc, char **argv)
{

  // we throw exceptions on creation if we fail
  try {

    PlayerClient robot(gHostname, gPort); // Conect to server
    Position2dProxy pp(&robot, 0);   // Get a motor control device (index is 0)

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true); // Turn on Motors
    RangerProxy ranger(&robot, 0 ); // Could also be 1 for the laser

   // ONE READ IS NEEDED AT THE BEGINNING TO CONNECT
    robot.Read();

   // These calls are needed to populate the structure else the calles to other functions
   // will not work
    ranger.RequestGeom();
    ranger.RequestConfigure();


    // go into  a loop
    for(;;){
      double newspeed =1;
      double newturnrate=0;
      pp.SetSpeed(newspeed, newturnrate);
      robot.Read();
      while(1){
	double val0 = ranger[0];
      	double val1 = ranger[1];
      	double val2 = ranger[2];
      	if(val0 < 1||val1<1||val2<1){
		newspeed = 0; newturnrate=0.5;
		pp.SetSpeed(newspeed, newturnrate);
		robot.Read();
		}

	else{break;}
      }
     /* //while(1){
      	else if(val1<1){
		newspeed = 0;newturnrate=0.5;
		pp.SetSpeed(newspeed, newturnrate);
		}
	//else{break;}
      //}
     // while(1){
       	else if(val2<1){
		newspeed=0;newturnrate=-0.5;
       		pp.SetSpeed(newspeed, newturnrate);
		}
	//else{break;}
      //}  */
	
       
    }
  }
  catch (PlayerCc::PlayerError & e) {
    std::cerr << e << std::endl;
    return -1;
  }
}
