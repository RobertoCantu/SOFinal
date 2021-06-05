
#pragma once


class SwapPages
{
    public:
        SwapPages();
        SwapPages (int f);
        //virtual ~SwapPages();
        void setFrame (int f);
        int getFrame ();




    private:

        int frame;

};

//Default Constructor
SwapPages::SwapPages(){

}
//Constructor
SwapPages::SwapPages(int f){
    frame=f;

}

void SwapPages::setFrame(int f){
frame=f;
}

int SwapPages::getFrame(){
return frame;
}


