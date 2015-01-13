#include <libplayerc++/playerc++.h>
#include <iostream>

    using namespace PlayerCc;

    std::string  gHostname(PLAYER_HOSTNAME);
    // NOTE !!! PLAYER_PORTNUM is the port number and has to be unique for each student,
   // and be set in the plaer server with -p
    uint32_t        gPort(6665); // Replace this with your port number !!



int main(int argc, char **argv)
{

  // we throw exceptions on creation if we fail
  try {

    PlayerClient robot(gHostname, gPort); // Conect to server
    Position2dProxy pp(&robot, 0);   // Get a motor control device (index is 0)

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true); // Turn on Motors


    // go into  a loop
    for(;;){
      double newspeed = 1 ;
      double newturnrate = 0;
      
      for(int e=0;e <= 10;e++){
	pp.SetSpeed(newspeed, newturnrate);
	robot.Read();
	}
      for(int i=0;i <=5 ;i++){
	newturnrate = 1.2;
	pp.SetSpeed(0, newturnrate);
	robot.Read();
	}
      // this blocks until new data comes; 10Hz by default
      robot.Read();

      // write commands to robot
     
    }
  }
  catch (PlayerCc::PlayerError & e) {
    std::cerr << e << std::endl;
    return -1;
  }
}
