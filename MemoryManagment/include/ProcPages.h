#pragma once


using namespace std;
#include <iostream>
class ProcPages
{
    public:
        ProcPages();
        ProcPages (int currTime, int f);
//virtual ~ProcPages();


    private:
        int currentTime;
        int frame;
};

//Constructor
ProcPages::ProcPages(int currTime, int f){

currentTime= currTime;
frame= f;
}


