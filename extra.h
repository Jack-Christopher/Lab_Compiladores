namespace extra
{

template<class Tipo>
bool contains(Tipo t, std::vector<Tipo> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        if (container[k] == t)
            return true;
    }
    return false;
}


template <class Tipo>
void print(std::vector<Tipo> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        std::cout<< container[k]<< "\n";
    }
    std::cout<< "\n";
}

template <class Tipo>
void printVector(std::vector<Tipo> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        std::cout<< container[k]<< " ";
    }
    std::cout<< "\n";
}


template <class Tipo> // Copia los elementos de Origen que no estan en Destino
void join (std::vector<Tipo> &destino, std::vector<Tipo> origen )
{
    bool existe;
    if ( destino.size() == 0)
        destino = origen;
    
    for (int k = 0; k < origen.size(); k++)
    {
        existe = false;
        for (int p = 0; p < destino.size(); p++)
        {
            if (origen[k] == destino[p])
                existe = true;
        }
        if (!existe)
            destino.push_back(origen[k]);
    }
}


template <class Tipo>
void deleteFrom(Tipo elemento, std::vector<Tipo> &container)
{
    for (int k = 0; k < container.size(); k++)
    {
        if (container[k] == elemento)
            container.erase(container.begin()+k);
    }
}


}