#pragma once
#include <math.h>
#include "ProcPages.h"
#include "SwapPages.h"
using namespace std;


class Insturctions
{
    public:
        Insturctions();
        //virtual ~Insturctions();
        void instA (int d, int p, int m );
        void instP (int n, int p);
        void instL (int p);
        void instF ();



    private:
        int current_time=0;
        int page_faults=0;
        int total_swaps=0;
        int MEM_SIZE= 2048;
         int SWAP_MEM_SIZE=4096;
        const int PAGE_SIZE=16;
        bool strategy= false;

};

//Default Constructor
Insturctions::Insturctions(){

}

void Insturctions::instA(int d , int p, int m){


}

void Insturctions::instP(int n, int p ){
    cout << "Asignar " << n << "bytes al proceso " << p << endl;
    //Casos invalidos
    if (n <=0){
        cout << "Error: el tamano del proceso debe ser mayor que cero " << "\n";
        cout << "Esta instruccion no podra ejecturase " << endl;
    }

    if (n > 2048){
        cout << "Error : el tamano del proceso excede los 2048 bytes" << "\n";
        cout << "Esta instruccion no podra ejecutarse" << endl;
    }

    if (p < 0){
        cout << "Error : los id's tienes que ser igual o mayor que cero" << "\n";
    }

//Calcula cuantas paginas se necesitan para cargar el proceso
int num_of_pages= ceil(n/PAGE_SIZE);



}

void Insturctions::instL(int p){

}

void Insturctions::instF(){


}
