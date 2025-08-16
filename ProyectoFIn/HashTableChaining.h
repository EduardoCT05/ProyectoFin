#pragma once

#include <iostream>
#include <forward_list> // uso listas enlazadas para el encadenamiento (chaining)
#include <string>
#include <stdexcept>    // runtime_error
using namespace std;

// Tabla hash gen�rica con encadenamiento.
// Idea: tengo un arreglo de listas, y cada lista guarda los elementos que caen
// en el mismo �ndice (colisiones) seg�n la funci�n hash.
template <typename T>
class HashTableChaining
{
    // Aqu� guardo los datos: es un arreglo de listas (forward_list) de tama�o N.
    // Cada posici�n del arreglo es un "bucket" y adentro hay una lista de elementos.
    forward_list<T>* data;
    unsigned int arraySize; // tama�o del arreglo (n�mero de buckets)
    // Nota: "unsigned" = sin signo, o sea no admite valores negativos.

public:
    // Constructor: recibe el tama�o y reserva memoria para N listas.
    HashTableChaining(unsigned int size)
    {
        // pido memoria para N forward_list<T>
        if (size == 0) size = 1;           // evita divisi�n entre 0
        data = new forward_list<T>[size];
        arraySize = size;
    }

    // Destructor: libero la memoria pedida para evitar fugas (memory leak).
    virtual ~HashTableChaining()
    {
        delete[] data;
    }

    // Funci�n hash: mapea la llave (key) a un �ndice v�lido [0, arraySize).
    // Ojo: aqu� asumo que T se puede usar con %, por ejemplo enteros.
    // Si T fuera string, tocar�a hacer otra funci�n hash.
    // "la convierte en un entero".
    int HashFunction(T key)
    {
        return static_cast<unsigned int>(key) % arraySize;
    }

    // M�todos b�sicos: insertar, quitar, buscar e imprimir.
    // Los marco virtual para poder hacer una clase hija (HashSet) que haga override.
    virtual void Add(T element)
    {
        // Calculo a qu� bucket cae este elemento
        int index = HashFunction(element);
        // Inserto al inicio de la lista del bucket (push_front es O(1))
        data[index].push_front(element);
    }

    // Eliminar un elemento (si existe). Si no est�, lanzo excepci�n.
    virtual void Remove(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];

        // Recorro la lista del bucket buscando el elemento y lo elimino
        auto before = listAtIndex.before_begin();
        bool found = false;
        for (auto it = listAtIndex.begin(); it != listAtIndex.end(); )
        {
            if (*it == element)
            {
                it = listAtIndex.erase_after(before); // borra el nodo actual
                found = true;
                break;
            }
            else
            {
                ++it;
                ++before;
            }
        }

        // Si llegu� aqu� sin encontrarlo, lanzo la excepci�n
        if (!found)
            throw runtime_error("no element " + to_string(element) + " in this hash table.");
    }

    // contains: funci�n de b�squeda. Regresa true si s� est�, false si no.
    bool Contains(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];

        for (auto i : listAtIndex)
        {
            if (i == element)
            {
                // Si lo encuentro, ya no hay que seguir
                return true;
            }
        }
        return false;
    }

    // Print: recorre todos los buckets e imprime lo que haya en cada uno.
    void Print()
    {
        for (unsigned int i = 0; i < arraySize; ++i)
        {
            cout << "[" << i << "]: ";
            // Recorro la lista de este bucket y voy imprimiendo
            for (auto j : data[i])
                cout << j << ", ";

            cout << endl;
        }
    }
};

// Si en alg�n lado qued� la declaraci�n, dejo una definici�n vac�a
// para evitar error de enlazado (linker) por s�mbolo no definido.
inline void HashTableChainingExample() {}
