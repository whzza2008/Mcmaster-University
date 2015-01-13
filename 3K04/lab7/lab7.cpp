#include <libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

    using std::ifstream;
    using namespace PlayerCc;
    using namespace std;

    std::string  gHostname(PLAYER_HOSTNAME);
    // NOTE !!! PLAYER_PORTNUM is the port number and has to be unique for each student,
   // and be set in the plaer server with -p
    uint32_t        gPort(6677); // Replace this with your port number !!
class Behaviors
{

        public:
                Behaviors(Position2dProxy* pp); // Constructor (Default constructor is private)
                virtual void Init(void){}; // Overwritten by childeren to given them information
                virtual bool Tick(void) =0; //  Called every frame, true is Behavior complete
                virtual void Resume(void){}; // Resume after other behavior was done
		
                double GetIntendedSpeed(){return(speed);};
                double GetIntendedRotation(){return(rotation);};

                void DoMove(void); //Perform the intended move (not overwriten by childen !!)

        protected:
                double speed,rotation; // The intended speed in this frame
                Position2dProxy* posProxy; // The position proxy to obain information !!

        private:
                Behaviors(){}; // Private !!

};
Behaviors::Behaviors(Position2dProxy* pp){
	posProxy = pp;
	speed = 0.0;
	rotation = 0.0;}
class MoveStraight: public Behaviors{
	public: 
		//double distance;
		MoveStraight(Position2dProxy* pp);
		void Init(double a);
		bool Tick(void);
	private:
		double distance;
		double goal_X;
		double goal_Y;
		
	};
MoveStraight::Init(double a){
	distance = a;
	speed = 1.0;
	rotation = 0.0;
	goal_X = pp.GetXPos()+ distance*cos(pp->GetYaw());
	goal_Y = pp.GetYPos()+ distance*sin(pp->GetYaw());
}
MoveStraight::Tick(){
	

}


int main(int argc, char **argv)
{

  // we throw exceptions on creation if we fail
  try {

    PlayerClient robot(gHostname, gPort); // Conect to server
    Position2dProxy pp(&robot, 0);   // Get a motor control device (index is 0)

    std::cout << robot << std::endl;

    pp.SetMotorEnable (true); // Turn on Motors
    
	
   /*while(!my_queue.empty()){
	//cl = my_queue.front();
	cout << my_queue.front()->qX<<' '<<my_queue.front()->qY<<endl;
	my_queue.pop();}
    //cout << cl->qX<<' '<<cl->qY<<endl;*/
    
	
    
    
    // go into  a loop
    for(;;){
	
	robot.Read();
	
     
    }
  }
  catch (PlayerCc::PlayerError & e) {
    std::cerr << e << std::endl;
    return -1;
  }
}
