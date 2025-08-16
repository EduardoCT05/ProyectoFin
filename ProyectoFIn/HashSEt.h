#pragma once

#include "HashTableChaining.h"
#include <iostream>
using namespace std;

// Conjunto basado en HashTableChaining: no admite duplicados.
template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    // Constructor que reusa el de la base (paso el tama�o de la tabla)
    explicit HashSet(unsigned int size)
        : HashTableChaining<T>(size) {}

    // Override del Add original para evitar duplicados.
    // Firma id�ntica a la base: Add(T element)
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
