#pragma once
#include <math.h>
#include <unordered_map>
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

        unordered_map <int,int> fifo;
        unordered_map <int, int> timestamp;
        int swa[4096] = {0};
        int mp [127]= {0};
        int m [2048]= {0};
        int page_faults=0;
        int time_stamp=0;
        int libre=128;
        int swaps=0;
        int num_pages=0;
        int c = 0;
        void FIFO(int n, int p);



};


//Default Constructor
Insturctions::Insturctions(){

}

void Insturctions::FIFO(int numB, int proc){
  int index=0;
  int temp3=0;

  c = ceil(numB/16.0);
  //libre -= c;

  for(int i=0;i<c;i++)
  {
    //Trae la última posición del mapa
    unordered_map<int,int>::iterator lastElement;
    for(auto it = fifo.begin(); it != fifo.end(); ++it)
    {
      lastElement = it;
    }

    //Swap
    swa[i]=proc;
    index = lastElement->first;
    temp3 = mp[index];
    mp[index]=swa[i];
    swa[i]=temp3;
    fifo.erase(index);
    fifo.insert(make_pair(index,proc));
    swaps+=2;
  }
}

//Funcion para mostrar la direccion real, dada la direccion virtual

void Insturctions::instA(int d , int p, int m){
    cout<<"A" << d << " " << p << " " << m << endl;
    if(m == 0){
        cout << "Obtener la direccion real correspondiente a la direccion virtual " << d << " del proceso " << p << endl;
    }

    if( m ==1 ){
        cout << "Obtener la direccion real correspondiente a la direccion virtual " << d << " del proceso " << p << " y cambiar dicha direccion" << endl;
        cout << "Se cambio la direccion " << d << " del proceso " << p << endl;
    }

    int res = 0;
    int contR = 0;
    int contP = 0;
    for(int i = 0; i< 128; i++){
        for(int j = 0; j < 16; j++){
            if(contP == d){
                res = contR;
            }
            contR++;
            if(mp[i] == p){
                contP++;
            }
        }
    }

    cout << "Direccion virtual: " << d << " Direccion real: " << res << endl;
    int num = timestamp[p];
    timestamp[p] = num+1;
}

//Funcion para colocar un proceso
void Insturctions::instP(int N, int p ){
    cout << "Asignar " << N << "bytes al proceso " << p << endl;
    //Casos invalidos
    if (N <=0){
        cout << "Error: el tamano del proceso debe ser mayor que cero " << "\n";
        cout << "Esta instruccion no podra ejecturase " << endl;
    }

    if (N > 2048){
        cout << "Error : el tamano del proceso excede los 2048 bytes" << "\n";
        cout << "Esta instruccion no podra ejecutarse" << endl;
    }

    if (p < 0){
        cout << "Error : los id's tienes que ser igual o mayor que cero" << "\n";
    }

    num_pages= ceil(N/16.0);
    timestamp.insert(make_pair(p,num_pages));
    int n= N;

    //Revisar si hay espacio libro en memoria real para poder colocar al proceso
    if (libre >= num_pages){

        libre-= num_pages;
        for (int i=0; i < 128 ; i ++){

            if (mp[i] == 0 && num_pages > 0){
                mp[i]= p;
                fifo.insert(make_pair(i,p));
                num_pages--;

            }
        }

        for (int j=0; j < 2048 ; j++){
            if (m[j] == 0 && n>0){
                m[j] = p;
                n--;
            }
        }

         int temp = -1, mayor = -1;
    int iC = 0;
    int iC2 = 0;
    int j = 0;
    for(j=0; j<128; j++)
    {
      if(mp[j] == p)
      {
        if(iC==0)
        {
          temp = j; //temp == 127 iC == 128
          iC++;
          cout<<"hola";
        }
        if(mp[j+1] != p)
        {
          if(iC2==0)
          {
            mayor = j;
            iC2++;
          }
        }
      }
    }
    cout << "Se asignaron los marcos de página " << temp << " - " << mayor << " al proceso " << p << endl;
  }





        else {
            cout << "fifo"<<endl;
            FIFO(N, p);
        }
}







void Insturctions::instL(int p){

}

void Insturctions::instF(){


}
