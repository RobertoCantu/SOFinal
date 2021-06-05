#pragma once


using namespace std;
#include <iostream>
class ProcPages
{
    public:
        ProcPages();
        ProcPages (int currTime, int f);
        //virtual ~ProcPages();
        void setCurrentTime (int currTime);
        void setFrame (int f);
        int getCurrentTime ();
        int getFrame ();


    private:
        int currentTime;
        int frame;
};


//Default Constructor
ProcPages ::ProcPages(){

}
//Constructor
ProcPages::ProcPages(int currTime, int f){

currentTime= currTime;
frame= f;
}

//Setters and getters
void ProcPages::setCurrentTime(int currTime){
currentTime=currTime;
}

void ProcPages::setFrame(int f){
frame=f;
}

int ProcPages::getCurrentTime(){
return currentTime;
}

int ProcPages::getFrame(){
return frame;
}


