#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Parser.h>
#include <string>


using namespace std;

int main()
{
vector <vector <string>> instructions;


Parser parser ("ArchivoTrabajo.txt");

instructions= parser.getParseInstructions();



for (int i=0; i < instructions.size(); i++){

    if (instructions[i][0] == "A"{
        // Metodo para instuccion
        })

        else if (instructions[i][0] == "P"{
        // Metodo para instuccion
        })

        else if (instructions[i][0] == "L"{
        // Metodo para instuccion
        })


        else if (instructions[i][0] == "F"{
        // Metodo para instuccion
        })

        else if (instructions[i][0] == "E"{
        // Metodo para instuccion
        })

        else if (instructions[i][0] == "C"{
        // No hacer nada
        })

        else {

            cout << "Error" << endl;
        }
}

    return 0;
}
