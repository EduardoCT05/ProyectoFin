// main.cpp
#include <iostream>
#include "BinarySearchTree.h"
#include "HashTableChaining.h"   


using namespace std;

static void EjecutarPruebaBST() {
    cout << "\nPRUEBA: BinarySearchTree\n";

    BinarySearchTree<int> tree;

    tree.Add(10);
    tree.Add(5);
    tree.Add(15);
    tree.Add(5);   // duplicado a la izquierda
    tree.Add(12);
    tree.Add(18);
    tree.Add(3);
    tree.Add(7);

    cout << "\nInOrder (recursivo, ordenado):\n";
    tree.InOrderWithRecursive();

    cout << "\nBúsquedas:\n";
    cout << "Search(7): " << (tree.Search(7) ? "Encontrado" : "No está") << '\n';
    cout << "Search(100): " << (tree.Search(100) ? "Encontrado" : "No está") << '\n';

    cout << "\nPostOrderIterative (dos pilas):\n";
    tree.PostOrderIterative();

    cout << "\nPostOrderIterativeOneStack (una pila):\n";
    tree.PostOrderIterativeOneStack();

    cout << "\nDelete hoja (3):\n";
    tree.Delete(3);
    tree.InOrderWithRecursive();

    cout << "\nDelete un hijo (12):\n";
    tree.Delete(12);
    tree.InOrderWithRecursive();

    cout << "\nDelete dos hijos (10):\n";
    tree.Delete(10);
    tree.InOrderWithRecursive();

    cout << "\nClearPostOrderRecursive:\n";
    tree.ClearPostOrderRecursive();
    tree.InOrderWithRecursive();

    cout << "==== FIN PRUEBA: BinarySearchTree ====\n";
}

int main() {
    EjecutarPruebaBST();
    return 0;
}
