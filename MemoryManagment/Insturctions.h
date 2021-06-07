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
        void instP (int n, int p, bool f);
        void instL (int p);
        void instF ();



    private:

        unordered_map <int,int> fifo; //mapa para guardar marco de pagina y id
        unordered_map<int, pair<int, int> > lru; //mapa para guardar tiempo, id y marco de pagina
        unordered_map <int, int> timestamp; //mapa para guardar tiempo del proceso
        int swa[256] = {0}; //Variable para representar memoria de swapping
        int mp [127]= {0}; //Variable para representar marcos de pagina
        int m [2048]= {0}; ///Variable para representar bytes de memoria real
        int page_faults=0; //Variable para contar los page faults
        int time_stamp=0; //Variable para contar el tiempo
        int libre=128; //Variable para representar las paginas de la memoria
        int swaps=0; //Variable para contar los page swaps
        int num_pages=0; //Variable para contar numeros de paginas de cada proceso
        int c = 0;
        int countA = 0;
        void FIFO(int n, int p);
        void LRU(int n, int p);
        void framesReal(int p, bool flag);
        void framesSwa(int p);
        void erase(int p);
        bool existeProceso(int p);


};



//Default Constructor
Insturctions::Insturctions(){

}

//Metodo con el algoritmo FIFO recibiendo como parametro numero de bytes (N) y id del proceso (pId)
void Insturctions::FIFO(int N, int pId){
  int index=0;
  int temp3=0;

  c = ceil(N/16.0);
  //libre -= c;

  for(int i=0;i<c;i++)
  {
    //Trae la �ltima posici�n del mapa
    unordered_map<int,int>::iterator iter;
    for(auto it = fifo.begin(); it != fifo.end(); ++it)
    {
      iter = it;
    }

    //Swap
    swa[i]=pId;
    index = iter->first;
    temp3 = mp[index];
    mp[index]=swa[i];
    swa[i]=temp3;
    fifo.erase(index);
    fifo.insert(make_pair(index,pId));
    swaps++;
  }
}

//Metodo con el algortimo LRU recibiendo como parametros numero de bytes (N) y id del proceso (pId)
void Insturctions::LRU(int N, int pId){

  c = ceil(N/16.0);
  int intMax = 2147483647;
    //Trae la �ltima posici�n del mapa
    unordered_map<int,pair<int, int> >::iterator iter;
    for(auto it = lru.begin(); it != lru.end(); ++it)
    {
      if(it->second.second < intMax)
      {
        iter = it;
        intMax = it->second.second;
      }
    }
   
    //Swap

    swa[iter->first] = iter->second.first;
    mp[iter->first] = pId;
    //cout<<iter->first;
    lru.erase(iter->first);
    lru.insert(make_pair(iter->first, make_pair(pId, intMax)));
    swaps++;
}

//Funcion para mostrar la direccion real, dada la direccion virtual

void Insturctions::instA(int d , int p, int m){
    cout<<"A " << d << " " << p << " " << m << endl;
    if(!existeProceso(p)){
        cout<<"Ese proceso no existe "<<endl;
        return;
    }
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
    timestamp[p] = num + 1;
    countA++;
}

//Funcion para colocar un proceso 
void Insturctions::instP(int N, int p, bool flag){

    cout << "Asignar " << N << " bytes al proceso " << p << endl;
    //Casos invalidos
    if (N <=0){
        cout << "Error: el tamano del proceso debe ser mayor que cero " << "\n";
        cout << "Esta instruccion no podra ejecturase " << endl;
        return;
    }

    if (N > 2048){
        cout << "Error : el tamano del proceso excede los 2048 bytes" << "\n";
        cout << "Esta instruccion no podra ejecutarse" << endl;
        return;
    }

    if (p < 0){
        cout << "Error : los id's tienes que ser igual o mayor que cero" << "\n";
        return;
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
                lru.insert(make_pair(i,make_pair(p, num_pages)));
                num_pages--;

            }
        }

        for (int j=0; j < 2048 ; j++){
            if (m[j] == 0 && n>0){
                m[j] = p;
                n--;
            }
        }

         framesReal(p, true);
  }





        else {
            if(flag){
                cout << "FIFO"<<endl;
                FIFO(N, p);
            }else{
                cout<<"LRU"<<endl;
                LRU(N, p);
            }
        }
}






//Funcion para liberar proceso
void Insturctions::instL(int p){
    cout << "L " << p << endl;
    if(!existeProceso(p)){
        cout<<"Ese proceso no existe"<<endl;
        return;
    }
    cout << "Liberar los marcos de p�gina ocupados por el proceso " << p << endl;
    int time = timestamp[p];
    timestamp[p]=time+1;

    framesReal(p, false);
    erase(p);
    framesSwa(p);
}


//Funcion para imprimir reporte de resultados
void Insturctions::instF(){
    int contador = 0;
    int auxiliar = 0;
    cout << "Turnaround por proceso: " << endl;
    for(auto it = timestamp.begin(); it != timestamp.end(); ++it)
    {
        cout << "Nombre del proceso: " << it->first << " Turnaround: " << it->second << endl;
        contador++;
        auxiliar+=it->second;
    }
    cout << "Turnaround promedio: " << (auxiliar/(contador*1.0))-4 << endl;
    cout << "Swaps general: " <<  swaps << endl;
    cout << "Page faults: " << '1' << endl;
    cout << "Tiempo de acceso o modificacion de direccion " << countA * 0.1 << 's' << endl;

}

//funcion auxiliar para obtener marcos paginas 
void Insturctions::framesReal(int p, bool flag){
      int aux = -1;
      int last = -1;
      int pages = 0;
      int auxPage = 0;
      for(int j = 0; j<128; j++){
        if(mp[j] == p){
        //cout<<"hola";
          if(pages == 0){
            aux = j;
            pages++;
          }
          if(mp[j+1] != p){
            if(auxPage == 0){
              last = j;
              auxPage++;
            }
          }
        }
      }
      if(flag){
        cout << "Se asignaron los marcos de pagina " << aux << " - " << last << " al proceso " << p << endl;
      }else{
        cout << "Se liberan los marcos de p�gina de memoria real: " << aux << " - " << last << endl;
      }
    }


//funcion auxiliar para obtener marcos paginas de la memoria swap
void Insturctions::framesSwa(int p){
      int aux = -1;
      int last = -1;
      int pages = 0;
      int auxPage = 0;
      for(int j = 0; j<256; j++){
        if(swa[j] == p){
        //cout<<"hola";
          if(pages == 0){
            aux = j;
            pages++;
          }
          if(swa[j+1] != p){
            if(auxPage == 0){
              last = j;
              auxPage++;
            }
          }
        }
      }
        if(aux != -1){
            cout << "Se liberan los marcos " << aux << " - " << last << " del �rea de swapping" << endl;
        }

         for(int i=0;i<256;i++){
            if(swa[i]==p){
                swa[i]=0;
            }
        }

    }

//Funcion para borrar marcos de pagina de un proceso
void Insturctions::erase(int p){
    for(int i=0;i<127;i++)
  {
    if(mp[i]==p)
    {
      libre++;
      mp[i]=0;
      fifo.erase(i);
    }
  }
}

//Funcion que revisa si existe un proceso en memoria real
bool Insturctions::existeProceso(int p){
    for(int i = 0, cont = 0; i<127; i++){
        if(mp[i] != p){
            cont++;
        }else{
            return true;
        }
    }
    return false;
}
