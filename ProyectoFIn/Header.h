#include <iostream>
#include "HashTableChaining.h"
#include "HashSet.h"

using namespace std;

int main()
{
    cout << "=== HashTableChaining<int> ===" << endl;
    HashTableChaining<int> table(5);
    table.Add(10);
    table.Add(15);
    table.Add(20);
    table.Print();

    cout << "Contains 15? " << (table.Contains(15) ? "Yes" : "No") << endl;
    table.Remove(15);
    table.Print();

    cout << "\n=== HashSet<int> (sin repetidos) ===" << endl;
    HashSet<int> set(5);
    set.Add(10);
    set.Add(15);
    set.Add(10); // repetido, no se inserta
    set.Add(20);
    set.Print();

    cout << "\n=== HashSet<string> ===" << endl;
    HashSet<string> setStr(5);
    setStr.Add("Hola");
    setStr.Add("Mundo");
    setStr.Add("Hola"); // repetido
    setStr.Print();

    return 0;
}
#pragma once
