enum Type
{
    Terminal,
    NonTerminal,
    NullType
};

class Nodo
{
private:
    std::string value;
    Type type;

public:
    Nodo();
    Nodo(std::string value, Type type);
    Type getType();
    std::string getValue();
    void setValues(std::string value, Type type);
    std::vector<Nodo> readNodo(std::string &text, int start, int end);
    std::string toString();
    bool operator ==(const Nodo &t) const;
    friend std::ostream &operator<<( std::ostream &output, Nodo &n );

    ~Nodo();
};
Nodo::Nodo()
{
    this->value = "--void--";
    this->type = NullType;
}

Nodo::Nodo(std::string value, Type type) 
{
    this->value = value;
    this->type = type;
}

Type Nodo::getType()
{
    return type;
}

std::string Nodo::getValue()
{
    return value;
}

void Nodo::setValues(std::string value, Type type)
{
    this->value = value;
    this->type = type;
}

std::vector<Nodo> Nodo::readNodo(std::string &text, int start, int end)
{
    bool opened = false;
    bool nonTerminal;
    std::string tempText = "";
    Nodo nodo;
    std::vector<Nodo> NodoList;
    for (int k = start; k <= end; k++)
    {
        if (text[k] != ' ')
        {
            if (text[k] == '<')
            {
                opened = true;
                nonTerminal = true;
            }
            else if (text[k] == '\"' && !opened)
            {
                opened = true;
                nonTerminal = false;
            }
            else if (opened && (text[k] == '>' || text[k] == '\"'))
            {
                opened = false;
                if (nonTerminal)
                    nodo.setValues(tempText, NonTerminal);
                else
                    nodo.setValues(tempText, Terminal);
                NodoList.push_back(nodo);
                tempText = "";
            }
            else if (opened)
                tempText += text[k];
        }
    }
    return NodoList;
}

std::string Nodo::toString()
{
    std::string temp = "";
    temp += "Valor: ";
    temp += this->value;
    temp += "\t";
    temp += "Tipo: ";
    switch (this->type)
    {
    case NonTerminal:
        temp += "NonTerminal";
        break;
    case Terminal:
        temp += "Terminal";
        break;
    case NullType:
        temp += "NullType";
        break;
    }
    temp += "\n";

    return temp;
}


bool Nodo::operator ==(const Nodo &t) const
{
    if ((this->type == t.type) && (this->value == t.value))
        return true;
    return false;
}

std::ostream &operator<<( std::ostream &output, Nodo &n )
{
    output<< "Valor: ";
    output<< n.getValue()<< "\t";
    output<< "Tipo: ";
    switch (n.getType())
    {
    case NonTerminal:
        output<< "NonTerminal";
        break;
    case Terminal:
        output<< "Terminal";
        break;
    case NullType:
        output<< "NullType";
        break;
    }
    output<< "\n";
}


Nodo::~Nodo()
{
}
