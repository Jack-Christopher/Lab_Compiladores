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
    parser.setGrammar("sample.txt", "E");
    parser.tas.readFromText("TAS.txt", 6, 5); // Se llena el TAS de 6x5 desde un archivo
    parser.tas.print();
    std::cout<<"\n";
    parser.verify("id + id");
    parser.verify("id - id");
    parser.verify("id +");

    return 0;
}
