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


Parser parser ("Test.txt");

instructions= parser.getParseInstructions();






for (int i=0; i < instructions.size();i++){
    for (int j=0; j <instructions[i].size();j++){
        cout << instructions[i][j] <<" ";
    }
    cout << "\n";
}






    return 0;
}
