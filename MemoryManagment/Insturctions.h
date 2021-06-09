#pragma once
#include <math.h>
#include <map>
#include <unordered_map>
#include <vector>
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
        unordered_map <int, double> timestamp; //mapa para guardar tiempo del proceso
        unordered_map<int, vector<int>> frames; // mapa que almacena los frames correctamente 
        //vector <int> globalframes; //Vector que ayuda  almacenar todos los frames 
        int swa[255] = {0}; //Variable para representar memoria de swapping
        int mp [127]= {0}; //Variable para representar marcos de pagina
        int m [2048]= {0}; ///Variable para representar bytes de memoria real
        int page_faults=0; //Variable para contar los page faults
        int time_stamp=0; //Variable para contar el tiempo
        int libre=128; //Variable para representar las paginas de la memoria
        int swaps=0; //Variable para contar los page swap in y swap outs
        int num_pages=0; //Variable para contar numeros de paginas de cada proceso
        int c = 0;
        int countA = 0;
        void FIFO(int n, int p);
        void LRU(int n, int p);
        void framesReal(int p, bool flag);
        void framesSwa(int p);
        void erase(int p);
        bool existeProceso(int p);
        void imprimirvector(vector<int> vec);
        vector <pair <int,int> > fifoq; //Para poder guardar las paginas conforme van llegando con su id 
        



};



//Default Constructor
Insturctions::Insturctions(){

}

//Metodo con el algoritmo FIFO recibiendo como parametro numero de bytes (N) y id del proceso (pId)
void Insturctions::FIFO(int N, int p){
  
  vector <int> swappedPages;
  int pages = ceil(N/16.0);
  //libre -= c;
//Vector de paginas para memoria real por si aun queda espacio antes de hacer los swappings correspondientes 
vector<int> procesPages;
  for (int i=0 ; i < 128; i ++){
    if (mp[i] == 0){
      m[i]=p;
      procesPages.push_back(i);
      pages --;

    }
  }
  //Revisar si en el vector existe algun elemento
  
   // frames.insert(make_pair(p,procesPages));
    //Aqui empezamos a liberar memoria y ha llenar la memoria Swap como sea necesario 

    /*
    unordered_map<int,int>::iterator iter;
    for(auto it = fifo.begin(); it != fifo.end(); ++it)
    {
      iter = it;
    }
    */
    //Copiar los marcos que se van a desocupar para el nuevo proceso en la memoria de swapping       
  for (int j=0; j < 256; j ++){
    //Aqui ocurre el swapping 
    if (swa[j] == 0 && pages > 0){
      int pos=0;
      swa[j]=fifoq[pos].second;
      swaps ++;
      pages--;
      mp[fifoq[pos].first]= p;
      procesPages.push_back(fifoq[pos].first);
      swaps ++;
      //Los mete de nuevo a la queue por si se llegan a requerir 
      swappedPages.push_back(fifoq[pos].first);
      frames.erase(fifoq[pos].second);
      fifoq.push_back(make_pair(fifoq[pos].first,fifoq[pos].second));
      fifoq.erase(fifoq.begin());
      
      pos++;
    }
    

  }

  //Mapear los nuevos frames con su process id 
  frames.insert(make_pair(p,procesPages));

  framesReal(p, true);

  //Mostrar los frames que fueron swapeados hacia la memoria swap 
  cout << "Los siguientes marcos de pagina fueron swappeados a memoria swap " << "[";
  imprimirvector(swappedPages);
  cout << "]";
  cout << endl;
  cout << endl;
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

    //Revisar si esta en memoria real o en la de swapping 
    for (int i=0; i < 256; i ++){
      if (swa[i] == p){
        page_faults++;
      }
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
    double num = timestamp[p];
    
    timestamp[p] = num + 0.1;
    //cout << "Tiempo en A: " << timestamp[p];
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
                
                //frames.insert(make_pair(p,globalframes.push_back(i)));
                
                //fifo.insert(make_pair(i,p));
                fifoq.push_back(make_pair(i,p));
                lru.insert(make_pair(i,make_pair(p, num_pages)));
                num_pages--;

            }
        }
        //Agregar frames de proceso en un mapa para futuras referencias
        vector<int> procesPages;
        for (int i=0; i < 128; i ++){
          if(mp[i] == p){
            procesPages.push_back(i);
            //frames.insert(make_pair(p,procesPages.push_back(i));
          }
        }
        frames.insert(make_pair(p,procesPages));

        for (int j=0; j < 2048 ; j++){
            if (m[j] == 0 && n>0){
                m[j] = p;
                n--;
            }
        }

         framesReal(p, true);
  }




//Si ya no paginas disponibles tendra que aplicar uno de los siguientes algoritmos, segun lo que haya ingresado el 
//usuario
        else {
            if(flag){
                cout << "No hay suficiente memoria se utilizara el algoritmo de FIFO"<<endl;
                FIFO(N, p);
            }else{
                cout<<"No hay suficiente memoria se utilizara el algoritmo de LRU"<<endl;
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
    cout << "Liberar los marcos de pagina ocupados por el proceso " << p << endl;
    double time = timestamp[p];
    //cout << "Time " << time ;
    double factor= 0.1 * timestamp[p];
    
    timestamp[p]=time+ factor;

    framesReal(p, false);
    erase(p);
    framesSwa(p);
}


//Funcion para imprimir reporte de resultados
void Insturctions::instF(){
    int contador = 0;
    double auxiliar = 0;
    cout << "F " << endl;
    

    if ( timestamp.size()> 0){
      cout << "Turnaround por proceso: " << endl;
    for(auto it = timestamp.begin(); it != timestamp.end(); ++it)
    {
        cout << "Nombre del proceso: " << it->first << " Turnaround: " << it->second << endl;
        timestamp.erase(it->first);
        contador++;
        auxiliar+=it->second;
    }
    cout << "Turnaround promedio: " << (auxiliar/(contador*1.0)) << endl;
    cout << "Swap In's y Swap Out's: " <<  swaps << endl;
    swaps=0; // Resetea los swaps
    cout << "Page faults: " << page_faults << endl;
    page_faults=0; //Resetea las page faults
    
    }

    else {
      cout << "No existen procesos en el programa para poder realizar los calculos " << endl;
    }

}

//funcion auxiliar para obtener marcos paginas 
void Insturctions::framesReal(int p, bool flag){
  
  /*
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

      /*
      cout << "Ojo aqui compa " << endl;
      for (int i=0; i < 127; i++){
        cout << mp[i] << " ";
      }

      cout << "--MAPA--" << endl;
  for(auto it = frames.begin(); it != frames.end(); ++it)
  {
    cout << " " << "ID" << it->first << endl;
    imprimirvector(it->second);
  }
  */
      if(flag){
        for(auto it = frames.begin(); it != frames.end(); ++it)
  {
    if (it->first == p){

    cout << "Se asignaron los siguientes marcos de pagina " << "[ ";
    imprimirvector(it->second);
    cout << "]";
    cout << endl;
    
    }
  }
        //cout << se asignaron los marcos de pagina << 
       // cout << "Se asignaron los marcos de pagina " << aux << " - " << last << " al proceso " << p << endl;
      }else{
        for(auto it = frames.begin(); it != frames.end(); ++it)
  {
    if (it->first == p){

    cout << "Se liberaron los siguientes marcos de pagina" << "[ ";
    imprimirvector(it->second);
    cout << "]";
    cout << endl;
    frames.erase(it->first);

    
    }
  }
        //cout << "Se liberaron los siguientes marcos de pagina" <<"[ ";
        //cout << "Se liberan los marcos de p�gina de memoria real: " << aux << " - " << last << endl;
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
            cout << "Se liberaron los marcos " << aux << " - " << last << " del area de swapping" << endl;
        }

         for(int i=0;i<256;i++){
            if(swa[i]==p){
                swa[i]=0;
            }
        }

    }

//Funcion para borrar marcos de pagina de un proceso
void Insturctions::erase(int p){
    for(int i=0;i<128;i++)
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

  int contReal=0;
  int contSwap=0;


    for(int i = 0; i<128; i++){
        if(mp[i] != p){
            contReal++;
        }
    }
    for (int i=0; i < 256; i ++){
      if (swa[i] != p){
        contSwap++;
      }

    }

    if (contReal == 128 && contSwap == 256){
      return false;
    }

    else {
      return true; 
    }


}

void Insturctions::imprimirvector (vector<int> vec)  {
  for (int i=0; i < vec.size(); i ++){
    cout << vec[i] << " ";
  }
  
}
