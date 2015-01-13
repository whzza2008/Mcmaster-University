#include <class8.h>


std::string  gHostname(PlayerCc::PLAYER_HOSTNAME);
// NOTE !!! PLAYER_PORTNUM is the port number and has to be unique for each student,
// and be set in the plaer server with -p
uint32_t        gPort(6789); // Replace this with your port number !!
class Collision
{
        public:
                Collision(Position2dProxy* pp, RangerProxy* lp); 

                bool CheckMovement(double speed, double rotation);

                // Give a direction that has "free space to move into
                double DirectionOfFreeSpace(void); 


        private:
                Position2dProxy* pos_proxy;
                RangerProxy*  ranger;
};
Collision::Collision(Position2dProxy* pp, RangerProxy* lp)
{
	pos_proxy=pp;
	ranger = lp;
	
}
bool Collision::CheckMovement(double speed, double rotation)
{	
	double F_sor = (*ranger)[0];
	std::cout<<F_sor<<std::endl;

	double disY = abs(F_sor * sin(pos_proxy->GetYaw()));
	double disX =abs( F_sor * cos(pos_proxy->GetYaw()));
	double predictY = disY - speed*0.1*sin(pos_proxy->GetYaw());
	double predictX = disX - speed*0.1*cos(pos_proxy->GetYaw());
	double leftside = (*ranger)[1];
	double rightside = (*ranger)[2];
	if(predictY < 0.1||predictX<0.1||leftside<0.2||rightside<0.2){return(1);}
	else{return(0);}	

}
double Collision::DirectionOfFreeSpace(void)
{
	
	srand((unsigned)time(NULL));
	double left = 0.5;
	double right = -0.5;
	double L_sor = ranger->GetRange(1);
	double R_sor = ranger->GetRange(2);
	if((R_sor<4)&&(L_sor>R_sor)){return left+(rand()%628-314) /100;}
	else if((L_sor<4)&&(R_sor>L_sor)){return right+(rand()%628-314) /100;}
	else{}
}


int main(int argc, char **argv)
{
    
    // we throw exceptions on creation if we fail
    try {
        
        PlayerClient robot(gHostname, gPort); // Conect to server
        Position2dProxy pp(&robot, 0);   // Get a motor control device (index is 0)
        
        std::cout << robot << std::endl;
        
        pp.SetMotorEnable (true); // Turn on Motors
        
        // IN INIT A BEABVIOR
        RangerProxy ranger(&robot, 0 );
	robot.Read();
	ranger.RequestGeom();
   	ranger.RequestConfigure();
	

	//std::cout<<"1"<<std::endl;

	

        Behaviors* behav;
        
        behav = new RandomWalk(&pp); // This could be any of the ones defined above
       // ((MoveStraight*) behav)->Init(20.0); 
	Collision coll(&pp,&ranger);
		// Initialize it accoringely
        // (NOTE: call the right Init via casting !!)
	
        
        //behav = new Turn(&pp);
        //((Turn*) behav)->Init(PI_HALF);
        
        //behav = new RandomWalk(&pp);
        
        
        // go into  a loop

	//std::cout<<"2"<<std::endl;
        for(;;){
            double speed = sqrt(pp.GetXSpeed()*pp.GetXSpeed()+pp.GetYSpeed()*pp.GetYSpeed());
		
            robot.Read();
		//std::cout<<"3"<<std::endl;
	    if(coll.CheckMovement(speed,pp.GetYawSpeed()))
		{pp.SetSpeed(0,coll.DirectionOfFreeSpace());}
	    
	    else{
                pp.SetSpeed(1,0);
            }
            // write commands to robot
            //pp.SetSpeed(newspeed, newturnrate);
        }
    }
    catch (PlayerCc::PlayerError & e) {
        std::cerr << e << std::endl;
        return -1;
    }
}
