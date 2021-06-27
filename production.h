
class Production
{
private:
    Nodo leftSide;
    std::vector<Nodo> rightSide;
    float probability;

public:
    Production() = default;
    Production(Nodo leftSide, std::vector<Nodo> rightSide);
    Production(Nodo leftSide, std::vector<Nodo> rightSide, float probability);
    Nodo getLeftSide();
    std::vector<Nodo> getRightSide();
    void setLeftSide(Nodo LeftSide);
    void setRightSide(std::vector<Nodo> RightSide);
    std::vector<Production> readProduction(std::string production);
    void readLeftSide(std::string &production, int &index);
    std::vector<Nodo> readRightSide(std::string &production, int &index, int end);    
    std::vector<std::vector<Nodo>> readRightSideHelper(std::string &production, int &index);
    std::string toString();
    ~Production();
};

Production::Production(Nodo leftSide, std::vector<Nodo> rightSide)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

Production::Production(Nodo leftSide, std::vector<Nodo> rightSide, float probability)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    this->probability = probability;
}

Nodo Production::getLeftSide()
{
    return leftSide;
}

std::vector<Nodo> Production::getRightSide()
{
    return rightSide;
}

void Production::setLeftSide(Nodo LeftSide)
{
    this->leftSide = LeftSide;
}

void Production::setRightSide(std::vector<Nodo> RightSide)
{
    this->rightSide = RightSide;
}

void Production::readLeftSide(std::string &production, int &index)
{
    while (index < production.size() && production[index] != ':')
        index++;
    Nodo Nodo;
    if (Nodo.readNodo(production, 0, index - 1)[0].getType() == NonTerminal)
    {
        leftSide = Nodo.readNodo(production, 0, index)[0];
    }
    else
        std::cout << "Produccion incorrecta\n";  
        
    index += 3; 
}

std::vector<Nodo> Production::readRightSide(std::string &production, int &index, int end)
{
    Nodo nodo;
    std::vector<Nodo> NodoList = nodo.readNodo(production, index, end);
    return NodoList;
}

std::vector<std::vector<Nodo>> Production::readRightSideHelper(std::string &production, int &index)
{
    std::vector<std::vector<Nodo>> RightSideList;
    int prevIndex = index;

    while (index < production.size())
    {
        if (production[index] == '|')
        {
            RightSideList.push_back(readRightSide(production, prevIndex, index - 1));
            prevIndex = index + 1;
        }
        index++;
    }
    RightSideList.push_back(readRightSide(production, prevIndex, index));

    return RightSideList;
}

std::vector<Production> Production::readProduction(std::string production)
{
    int index = 0;
    std::vector<Production> productions;

    readLeftSide(production, index);
    std::vector<std::vector<Nodo>> tempList = readRightSideHelper(production, index);

    Production prod;
    prod.setLeftSide(leftSide);

    for (int k = 0; k < tempList.size(); k++)
    {
        prod.setRightSide(tempList[k]);        
        productions.push_back(prod);
    }

    return productions;
}

std::string Production::toString()
{
    std::string temp = "";
    temp += "[";
    temp += leftSide.getValue();
    temp += "] --> [  ";
    for (int k = 0; k < rightSide.size(); k++)
    {
        if (rightSide[k].getType() == Terminal)
        {
            temp += "\"";
            temp += rightSide[k].getValue();
            temp += "\"";
        }
        else if (rightSide[k].getType() != NullType)
            temp += rightSide[k].getValue();
        temp += "  ";
    }
    temp += "]   ";
    return temp;
}

Production::~Production()
{
}
