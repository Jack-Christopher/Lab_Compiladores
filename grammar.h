class Grammar
{
private:
    std::string initial;
    std::vector<Production> productions;
    std::vector<Nodo> NonTerminals;
    std::vector<Nodo> Terminals;

public:
    Grammar() = default;
    Grammar(std::vector<Production> productions);
    void readGrammarFromTXT(std::string fileName);
    void setElements(std::string init);
    
    std::string getInitial();
    std::vector<Production> getProductions();
    std::vector<Nodo> getNonTerminals();
    std::vector<Nodo> getTerminals();

    std::vector<Production> getProductions(std::string nt);
    
    void getPrimerosHelper(std::string name, std::vector<std::string> &firsts, std::vector<std::string> &visited);
    std::vector<std::string> getPrimeros2(std::string name, std::vector<std::string> &visited);
    std::vector<std::string> getPrimeros(std::string name);
    
    std::vector<std::string> getSiguientes(std::string name);
    std::vector<std::string> getSiguientes2(std::string name, std::vector<std::string> &visited);
    void getSiguientesHelper(std::string name, std::vector<std::string> &visited, std::vector<std::string> &nextList);

    void printPrimeros();
    void printSiguientes();

    void print();
    
    ~Grammar();
};

Grammar::Grammar(std::vector<Production> productions)
{
    this->productions = productions;
}

void Grammar::readGrammarFromTXT(std::string fileName)
{
    std::ifstream file(fileName);
    std::string tempText;
    Production prod;
    while (std::getline(file, tempText))
    {
        std::vector<Production> tempList = prod.readProduction(tempText);
        for (int k = 0; k < tempList.size(); k++)
        {
            productions.push_back(tempList[k]);
        }
    }
    std::string init;
    std::cout<< "Ingrese el simbolo inicial:\t";
    std::cin>> init;
    setElements(init);
}

void Grammar::setElements(std::string init)
{
    for (int k = 0; k < productions.size(); k++)
    {
        if(!extra::contains<Nodo>(productions[k].getLeftSide(), NonTerminals))
            NonTerminals.push_back(productions[k].getLeftSide());
        
        if (productions[k].getLeftSide().getValue() == init)
            this->initial = init;

        auto temp = productions[k].getRightSide();
        for (int p = 0; p < temp.size(); p++)
        {
            if ((temp[p].getType() == Terminal) && !extra::contains<Nodo>(temp[p], Terminals))
                Terminals.push_back(temp[p]);
        }
    }
}


std::string Grammar::getInitial()
{
    return this->initial;
}

std::vector<Nodo> Grammar::getNonTerminals()
{
    return NonTerminals;
}

std::vector<Nodo> Grammar::getTerminals()
{
    return Terminals;
}



std::vector<Production> Grammar::getProductions()
{
    return productions;
}

std::vector<Production> Grammar::getProductions(std::string nt)
{
    std::vector<Production> NTproductions;
    for (int k = 0; k < this->productions.size(); k++)
    {
        for (int p = 0; p < this->productions[k].getRightSide().size(); p++)
        {
            if (this->productions[k].getRightSide()[p].getValue() == nt)
                NTproductions.push_back(productions[k]);
        }
    }
    return NTproductions;
}



void Grammar::getPrimerosHelper(std::string name, std::vector<std::string> &firsts, std::vector<std::string> &visited)
{
    if ( extra::contains(name, visited))
        return;
    std::string temp = "";
    if ( extra::contains<Nodo>(Nodo{name, Terminal}, Terminals) && !extra::contains<std::string>(name, firsts))
    {
        temp += "\"";
        temp += name;
        temp += "\"";
        firsts.push_back(temp);
    }
    else  // X is not  Terminal
    {
        std::vector<std::string> subResultado; // primeros de cada Y_i
        std::string epsilon = "";
        for (int k = 0; k < productions.size(); k++)
        {
            if (productions[k].getLeftSide().getValue() == name) // determinada produccion
            {
                visited.push_back(productions[k].getLeftSide().getValue());
                int index = 0;
                int longitud = productions[k].getRightSide().size();
                do
                {
                    subResultado = getPrimeros2(productions[k].getRightSide()[index++].getValue(), visited); // Y_0
                    for (int t = 0; t < subResultado.size(); t++)
                    {
                        if (!extra::contains<std::string>(subResultado[t], firsts))
                            firsts.push_back(subResultado[t]);
                    }
                } 
                while (extra::contains<std::string>(epsilon, subResultado) && index < longitud);
            }
        }        
    }
}

std::vector<std::string> Grammar::getPrimeros2(std::string name, std::vector<std::string> &visited)
{
    std::vector<std::string> firstList;
    getPrimerosHelper(name, firstList, visited);
    return firstList;
}

std::vector<std::string> Grammar::getPrimeros(std::string name)
{
    std::vector<std::string> firstList;
    std::vector<std::string> visistedNodesList;
    getPrimerosHelper(name, firstList, visistedNodesList);
    return firstList;
}



void Grammar::getSiguientesHelper(std::string name, std::vector<std::string> &visited, std::vector<std::string> &nextList)
{
    if (extra::contains<std::string>(name, visited))
        return;
    else
        visited.push_back(name);

    std::vector<Nodo> prod_RS;
    int index;
    std::string epsilon = "\"\"";
    std::vector<std::string> temp;
    bool needRule3 = false;

    if (name == this->initial)
        nextList.push_back("$");
    
    for (int k = 0; k < productions.size(); k++)    // Iterar por cada produccion
    {
        index = 0;
        prod_RS = productions[k].getRightSide(); // prod.RS
        while (index < prod_RS.size() && prod_RS[index].getValue()!= name)
            index++;    // ubicacion del elemento del cual se obtiene sus SIGUIENTES

        if (index < prod_RS.size())
        {
            if (index == prod_RS.size() -1)
                extra::join<std::string>(nextList, getSiguientes2(productions[k].getLeftSide().getValue(), visited));
            else
            {
                index++;
                do
                {
                    temp = getPrimeros(prod_RS[index].getValue());
                    extra::join<std::string>(nextList, temp);
                    
                    if (extra::contains<std::string>(epsilon, temp))
                        needRule3 = true;
                    else
                        needRule3 = false;
                    index++;
                }
                while ( index < prod_RS.size() && needRule3);
            }
            if (needRule3)
                extra::join<std::string>(nextList, getSiguientes2(productions[k].getLeftSide().getValue(), visited));
        }
    }
}


std::vector<std::string> Grammar::getSiguientes(std::string name)
{
    std::vector<std::string> visitedNodes;
    std::vector<std::string> nextList; // listas de siguientes

    getSiguientesHelper(name, visitedNodes, nextList);
    extra::deleteFrom<std::string>("\"\"", nextList);
    return nextList;
}

std::vector<std::string> Grammar::getSiguientes2(std::string name, std::vector<std::string> &visited)
{
    std::vector<std::string> nextList; // listas de siguientes
    getSiguientesHelper(name, visited, nextList);

    return nextList;
}

void Grammar::printPrimeros()
{
    std::vector<std::string>  temp;
    for (int k = 0; k < this->NonTerminals.size(); k++)
    {
        std::cout<< "Nodo:"<<NonTerminals[k].getValue()<<"\n Primeros:\t";
        temp = getPrimeros(this->NonTerminals[k].getValue());
        extra::printVector<std::string>(temp);
        std::cout<< "\n";
    }
    std::cout<< "\n";
}

void Grammar::printSiguientes()
{
    std::vector<std::string>  temp;
    for (int k = 0; k < this->NonTerminals.size(); k++)
    {
        std::cout<< "Nodo:"<<NonTerminals[k].getValue()<<"\n Siguientes:\t";
        temp = getSiguientes(this->NonTerminals[k].getValue());
        extra::printVector<std::string>(temp);
        std::cout<< "\n";
    }
    std::cout<< "\n";
}


void Grammar::print()
{
    std::cout << "\n-------------- Grammar --------------\n";

    for (int k = 0; k < productions.size(); k++)
    {
        std::cout << productions[k].toString() << "\n";
    }
    std::cout << "\n-------------------------------------\n";
}

Grammar::~Grammar()
{
}
