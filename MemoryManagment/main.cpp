#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Parser.h"
#include "Insturctions.h"
#include <string>



using namespace std;
Insturctions instructionsObj;
//Funcion que convierte de String a Int
int strtoInt (string instruction){
    stringstream stringconverter (instruction);
    int x;
    stringconverter >> x;
    return x;

}

int main()
{




vector <vector <string>> instructions;


Parser parser ("test.txt");

instructions = parser.getParseInstructions();






/*
Opciones posibles
            A - 3 args, all numbers
            P - 2 args, all numbers
            L - 1 arg, number
            F - 0 args
            E - 0 args
            C - all comments
            */

/*for(int i = 0; i<instructions.size(); i++){
    for(int j = 0; j<instructions[i].size(); j++){
        cout<<instructions[i][j];
    }
}
*/
for (int i=0; i < instructions.size(); i++){

    if (instructions[i][0] == "A"){

        // functionA (strtoInt (instuctions [i][1], instuctions [i][2], instuctions [i][3])

        instructionsObj.instA(strtoInt(instructions[i][1]), strtoInt(instructions[i][2]), strtoInt(instructions[i][3]));
        }

        else if (instructions[i][0] == "P"){

        instructionsObj.instP(strtoInt(instructions[i][1]), strtoInt(instructions[i][2]));
        // Metodo para instuccion
        }

        else if (instructions[i][0] == "L"){
        // Metodo para instuccion
        }


        else if (instructions[i][0] == "F"){
        // Metodo para instuccion
        }

        else if (instructions[i][0] == "E"){
        // Metodo para instuccion
        }

        else if (instructions[i][0] == "C"){
        // No hacer nada
        }

        else {

            cout << "Error" << endl;
        }
}

    return 0;
}
