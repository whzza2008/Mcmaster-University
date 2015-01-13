#include <libplayerc++/playerc++.h>
#include <iostream>

    using namespace PlayerCc;

    std::string  gHostname(PlayerCc::PLAYER_HOSTNAME);
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
      double newspeed =1;
      double newturnrate=0;
      pp.SetSpeed(newspeed, newturnrate);
      robot.Read();
      double val0 = ranger[0];
      double val1 = ranger[1];
      double val2 = ranger[2];
      while(1){
      	if(val0 < 1)
		newspeed = 0; newturnrate=0.1;
		pp.SetSpeed(newspeed, newturnrate);
		robot.Read();}
	else{break;}
      }
      while(1){
      	if(val1<1){
		newspeed = 0;newturnrate=-0.1;
		pp.SetSpeed(newspeed, newturnrate);
		robot.Read();}
	else{break;}
      }
      while(1){
       	if(val2<1){
		newspeed=0;newturnrate=0.1;
       		pp.SetSpeed(newspeed, newturnrate);
		robot.Read();}
	else{break;}
      }
       
    }
  }
  catch (PlayerCc::PlayerError & e) {
    std::cerr << e << std::endl;
    return -1;
  }
}
