#pragma once

#include "HashTableChaining.h"
#include <iostream>
using namespace std;



template <typename T>
class HashSet : public HashTableChaining<T>
{
    ...
public:
    // Constructor que reusa el de la base (paso el tama�o de la tabla)
    HashSet(unsigned int size) : HashTableChaining<T>(size)
    {
        // aqu� no necesito m�s l�gica; la base ya reserv� memoria
    }

    // Override del Add original para evitar duplicados.
    void Add(T element) override
    {
        // S�lo inserto si no existe (esto es lo que lo convierte en "set")
        if (!this->Contains(element))
        {
            // Llamo al Add de la clase base para no duplicar c�digo
            HashTableChaining<T>::Add(element);
        }
        // else: si ya estaba, no hago nada (as� no hay repetidos)
    }
};
