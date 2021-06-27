#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include "nodo.h"
#include "production.h"
#include "extra.h"
#include "grammar.h"
#include "tas.h"
#include "LL1.h"

int main()
{
    LL1 parser;
    parser.setGrammar("sample.txt");
    parser.tas.readFromText("TAS.txt", 6, 5); // Se llena el TAS de 6x5 desde un archivo
    parser.tas.print();
    std::string tempText ;
    std::cout<< "Ingresa la cadena a analizar:\t";
    std::cin.ignore();
    std::getline(std::cin, tempText);
    if (parser.analyze(tempText))
        std::cout<< "Cadena Aceptada\n";
    else
        std::cout<< "Cadena NO Aceptada\n";

    return 0;
}