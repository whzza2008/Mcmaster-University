#include <libplayerc++/playerc++.h>
#include <iostream>
#include <cstdlib>
    using namespace PlayerCc;
    void random_walk(double,double);

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
      double newspeed = 0 ;
      double newturnrate = 0;
      random_walk(newspeed,newturnrate);
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
void random_walk(double new_speed,double new_rotation){
	new_speed = rand();
	new_rotation = rand();
	pp.SetSpeed(new_speed, new_turnrate);
	double pX;
	double pY;
	for(int tim = 0; tim <= 10;tim++){
		pX = pp.GetXPos();
		pY = pp.GetYPos();
		cout << "X :"<< pX<<"\t"<<"Y :"<<pY<<endl ;
	}
}

