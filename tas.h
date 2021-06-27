class TAS
{
public:
    std::vector<std::string> filas;     // NonTerminals
    std::vector<std::string> columnas;  // Terminals + $
    std::vector<std::vector<Production>> content;
    std::vector<std::vector<std::string>> siguientes;
    std::vector<std::vector<std::string>> primeros;

    void setFilas(std::vector<Nodo> noTerminales);
    void setColumnas(std::vector<Nodo> terminales);
    void setPrimeros(std::vector<std::string> firsts);
    void setSiguientes(std::vector<std::string> nexts);

    Production getValue(std::string f, std::string c);
    void setValue(Production prod, std::string f, std::string c);
    void setValue(Production prod, int f, int c);
    void setUpContent();

    void readFromText(std::string fileName, int n, int m);

    void print();

    TAS() = default;
    ~TAS();
};



void TAS::setFilas(std::vector<Nodo> noTerminales)
{
    for (int k = 0; k < noTerminales.size(); k++)
    {
        this->filas.push_back(noTerminales[k].getValue());
    }
}
void TAS::setColumnas(std::vector<Nodo> terminales)
{
    for (int k = 0; k < terminales.size(); k++)
    {
        if (terminales[k].getValue() != "")
            this->columnas.push_back(terminales[k].getValue());
    }
    this->columnas.push_back("$");
}


Production TAS::getValue(std::string f, std::string c)
{
    std::vector<Nodo> tempVector;
    Nodo tempNodo{"", NullType };
    tempVector.push_back(tempNodo);
    Production prod{tempNodo, tempVector};

    for (int k = 0; k < filas.size(); k++)
    {
        if (filas[k] == f)
        {
            for (int p = 0; p < columnas.size(); p++)
            {
                if (columnas[p] == c)
                    return content[k][p];
            }
        }
    }
    return prod;
}

void TAS::setValue(Production prod, std::string f, std::string c)
{
    for (int k = 0; k < filas.size(); k++)
    {
        if (filas[k] == f)
        {
            for (int p = 0; p < columnas.size(); p++)
            {
                if (columnas[p] == c)
                    content[k][p] = prod;
            }
        }
    }
}

void TAS::setValue(Production prod, int f, int c)
{
    content[f][c] = prod;
}



void TAS::setUpContent()
{
    std::vector<Production> tempVector;
    Nodo tempNodo{"NULL", NullType};
    std::vector<Nodo> tempRS;
    tempRS.push_back(tempNodo);
    Production tempProd{tempNodo, tempRS};

    for (int k = 0; k < this->columnas.size(); k++)
    {
        tempVector.push_back(tempProd);
    }
    for (int k = 0; k < this->filas.size(); k++)
    {
        content.push_back(tempVector);
    }
}

void TAS::print()
{
    std::cout<< "Columnas:\n";
    extra::print<std::string> (this->columnas);
    std::cout<< "Filas:\n";
    extra::print<std::string> (this->filas);
    std::cout<< "Primeros:\n";
    for (int k = 0; k < this->primeros.size(); k++)
    {
        std::cout<< this->filas[k]<<":\n";
        extra::print<std::string> (this->primeros[k]);
    }
    std::cout<< "Siguiente:\n";
    for (int k = 0; k < this->primeros.size(); k++)
    {
        std::cout<< this->filas[k]<<":\n";
        extra::print<std::string> (this->siguientes[k]);
    }

    for (int k = 0; k < content.size(); k++)
    {
        for (int p = 0; p < content[0].size(); p++)
        {
            std::cout<< content[k][p].toString();
        }
        std::cout<<"\n";
    }

}


void TAS::readFromText(std::string fileName, int n, int m)
{
    std::ifstream file(fileName);
    std::string tempText;

    Production prod;
    int f = 0, c = 0; 
    while (std::getline(file, tempText))
    {
        if ( tempText != "[]" )
        {
            std::vector<Production> tempList = prod.readProduction(tempText);
            if (tempList.size() == 1)
                setValue(tempList[0], f, c);
        }
        c++;
        if (c >= n)
        {
            c = 0;
            f++;
        }
    }
}


TAS::~TAS()
{
}
