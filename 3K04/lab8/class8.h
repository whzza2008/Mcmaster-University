#include <libplayerc++/playerc++.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace PlayerCc;


class Behaviors
{
    
public:
    Behaviors(Position2dProxy* pp); // Constructor (Default constructor is private)
    virtual void Init(void){}; // Overwritten by childeren to given them information
    virtual bool Tick(void) =0; //  Called every frame, true is Behavior complete
    virtual void Resume(void){}; // Resume after other behavior was done
    //virtual int  process(void)=0;
    double GetIntendedSpeed(){return(speed);};
    double GetIntendedRotation(){return(rotation);};
    
    void DoMove(void); //Perform the intended move (not overwriten by childen !!)
    
protected:
    double speed,rotation; // The intended speed in this frame
    Position2dProxy* posProxy; // The position proxy to obain information !!
    
private:
    Behaviors(){}; // Private !!
    
};

Behaviors::Behaviors(Position2dProxy* pp)
{
    posProxy=pp;
}

/*Behaviors::~Behaviors()
 {
 
 }*/
void Behaviors::DoMove(void)
{
    posProxy->SetSpeed(speed,rotation);
}

/*----------------------------------------------*/
// Constants
#define PI_TWO  3.14159265358979323846  *2.
#define PI  3.14159265358979323846
#define PI_HALF  3.14159265358979323846 *.5

//Macros
#define Square(x) ((x)*(x))



/*-------------------------------------------------------------*/
// Go straight for one meter Mode
// Call go_straight_init initially
// Call go_straight repeatedly into it returns 0

#define STRAIGHT_DISTANCE 1.
#define STRAIGH_MAX_SPEED .5
#define STRAIGH_CRAWL_SPEED .1

#define STRAIGHT_TOLERANCE 0.1


class MoveStraight : public Behaviors
{
public:
    MoveStraight(Position2dProxy* pp);
    ~MoveStraight();
    void Init(double distance);
    bool Tick(void);
private:
    Position2dProxy* posProxy;
    double goal_x;
    double goal_y;
    
};

MoveStraight::MoveStraight(Position2dProxy* pp):Behaviors(pp)
{
    posProxy=pp;
    goal_x=0.;
    goal_y=0.;
}

MoveStraight::~MoveStraight()
{
}



void MoveStraight::Init( double distance )
{
    goal_x=posProxy->GetXPos()+ distance * cos(posProxy->GetYaw());
    goal_y=posProxy->GetYPos()+ distance * sin(posProxy->GetYaw());
    
    //printf(" Straight Move to %f %f \n" ,goal_x,goal_y);
    
}

bool MoveStraight::Tick(void)
{
    // How far do we still have to go?
    double dist = sqrt( Square((goal_x - posProxy->GetXPos()))+
                       Square((goal_y - posProxy->GetYPos())));
    
    rotation = 0;
    if(dist>1.) // Proportional speed control
        speed=STRAIGH_MAX_SPEED;
    else
        speed= dist* STRAIGH_MAX_SPEED +STRAIGH_CRAWL_SPEED;
    
    // posProxy->SetSpeed(speed,0.);
    
    
    if(dist<STRAIGHT_TOLERANCE)
    {
        return (1);
    }
    else
    {
        return (0);
    }
    
}



/*-------------------------------------------------------------*/

// Turn Left 90 Degrees Mode
// Call turn_left_int initially
// Call turn_let into it returns 0

#define TURN_MAX_SPEED 1.
#define TURN_CRAWL_SPPED .01

#define TURN_TOLERANCE  .01


class Turn : public Behaviors
{
public:
    Turn(Position2dProxy* pp);
    ~Turn();
    void Init(double angle);
    bool Tick(void);
private:
    double  turn_to;
    
    
    
};

Turn::Turn(Position2dProxy* pp):Behaviors(pp)
{
    turn_to=0.0;
}

Turn::~Turn()
{
}

void Turn::Init( double angle )
{
    turn_to=posProxy->GetYaw() + angle;
    // NOTE GetYaw returns negative numbers for lower quadarnts !!
    if(turn_to>PI)turn_to=turn_to-PI_TWO;
    
    // printf(" Turn Turn to %f \n",turn_to);
}


bool Turn::Tick(void)
{
    // Note, we do not  check for overshoot here!!
    double error=fabsf(turn_to-posProxy->GetYaw());
    //double turn_rate;
    if(error>1.) // Proportional turn speed control
        rotation=TURN_MAX_SPEED;
    else
        rotation=TURN_MAX_SPEED*error+TURN_CRAWL_SPPED;
    
    
    if(error<TURN_TOLERANCE)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

/*----------------------------------------------*/
//Robot on random walk
#define SCALE .3
class RandomWalk : public Behaviors
{
public:
    RandomWalk(Position2dProxy* pp);
    ~RandomWalk();
    void Init(void);
    bool Tick(void);
    //void DoMove(void);
private:
    Position2dProxy* posProxy;
};

RandomWalk::RandomWalk(Position2dProxy* pp):Behaviors(pp)
{
    posProxy = pp;
}

RandomWalk::~RandomWalk()
{
}

void RandomWalk::Init(void)
{
}

bool RandomWalk::Tick(void)
{
    srand((unsigned)time(NULL));
    rotation = (SCALE * rotation) + ( (1-SCALE)*( (rand()%628-314) /100) );
    speed = 3.0;
    return(0);
}






