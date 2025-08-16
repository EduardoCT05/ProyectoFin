#pragma once

#include "HashTableChaining.h"
#include <iostream>
using namespace std;



template <typename T>
class HashSet : public HashTableChaining<T>
{
    ...
public:
    // Constructor que reusa el de la base (paso el tamaño de la tabla)
    HashSet(unsigned int size) : HashTableChaining<T>(size)
    {
        // aquí no necesito más lógica; la base ya reservó memoria
    }

    // Override del Add original para evitar duplicados.
    void Add(T element) override
    {
        // Sólo inserto si no existe (esto es lo que lo convierte en "set")
        if (!this->Contains(element))
        {
            // Llamo al Add de la clase base para no duplicar código
            HashTableChaining<T>::Add(element);
        }
        // else: si ya estaba, no hago nada (así no hay repetidos)
    }
};
