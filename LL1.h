class LL1
{
public:
    Grammar grammar;
    TAS tas;
    void setTAS();
    void setGrammar(std::string fileName, std::string simboloInicial);
    std::queue<std::string> getQueueFromString(std::string cadena);
    bool verifyAlgorithm(std::string cadena);
    bool verify(std::string tempText);
    LL1() = default;
    LL1(Grammar g );
};


LL1::LL1(Grammar g)
{
    this->grammar = g;
}

void LL1::setTAS()
{
    tas.setFilas(grammar.getNonTerminals());
    tas.setColumnas(grammar.getTerminals());
    
    for ( int k = 0; k < this->tas.filas.size(); k++)
    {
        this->tas.primeros.push_back(grammar.getPrimeros(this->tas.filas[k]));
        this->tas.siguientes.push_back(grammar.getSiguientes(this->tas.filas[k]));
    }
    tas.setUpContent();
}


void LL1::setGrammar(std::string fileName, std::string simboloInicial)
{
    this->grammar.readGrammarFromTXT(fileName, simboloInicial);
    setTAS();
}

std::queue<std::string> LL1::getQueueFromString(std::string cadena)
{
    std::queue<std::string> tempQueue; 
    std::string temp = "";
    for (int k = 0; k < cadena.size(); k++)
    {
        if (cadena[k] != ' ')
            temp += cadena[k];
        else
        {
            if (temp != "")
            {
                tempQueue.push(temp);
                temp = "";
            }
        }
    }
    if (temp != "")
    {
        tempQueue.push(temp);
    }
    return tempQueue;
}


bool LL1::verifyAlgorithm(std::string cadena)
{
    std::stack<std::string> pila;
    pila.push( "$" );
    pila.push( this->grammar.getInitial() );

    std::queue<std::string> entrada = getQueueFromString(cadena);
    entrada.push( "$" );

    while( ! entrada.empty() && !pila.empty() ) 
    {
        if ( entrada.front() == pila.top() ) 
        {
            entrada.pop();
            pila.pop();
        }
        else 
        {
            std::string temp = pila.top();
            pila.pop();
            Production prod = this->tas.getValue(temp, entrada.front());
            if (prod.getLeftSide().getType() == NullType)
            {
                std::cout<< "El nodo \""<< entrada.front() <<"\" en su ubicacion no concuerda con la gramatica\n";
                return false;
            }
            
            std::vector<Nodo> tempNodos = prod.getRightSide();

            for (int k = tempNodos.size() -1; k >= 0; k--)
            {
                if (tempNodos[k].getValue() != "")
                    pila.push(tempNodos[k].getValue());
            }
        }
    }

    return (entrada.empty() && pila.empty());
}


bool LL1::verify(std::string tempText)
{
    if (verifyAlgorithm(tempText))
        std::cout<< tempText<<" :Cadena Aceptada\n\n";
    else
        std::cout<< tempText<<" :Cadena NO Aceptada\n\n";
}
