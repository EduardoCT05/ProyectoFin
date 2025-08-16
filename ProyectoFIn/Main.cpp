#include <iostream>
#include "BinarySearchTree.h"
#include "HashTableChaining.h"  
#include "HashSet.h"            

using namespace std;

// Ejemplo de pruebas con BinarySearchTree
static void EjecutarPruebaBST() {
    cout << "\n PRUEBA: BinarySearchTree \n";

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

    cout << " FIN PRUEBA: BinarySearchTree \n";
}

// Ejemplo de pruebas con HashSet
static void EjecutarPruebaHashSet() {
    cout << "\n PRUEBA: HashSet \n";

    // tamaño pequeño para ver colisiones fácilmente
    HashSet<int> set(5);

    // Inserciones (10 duplicado)
    set.Add(10);
    set.Add(15);
    set.Add(20);
    set.Add(10); // duplicado: no debe agregarse

    cout << "\nContenido del HashSet (sin duplicados):\n";
    set.Print();

    cout << "\nContains(15): " << (set.Contains(15) ? "Si" : "No") << '\n';
    cout << "Contains(99): " << (set.Contains(99) ? "Si" : "No") << '\n';

    cout << "\nRemove(15):\n";
    set.Remove(15);
    set.Print();

    cout << "\nIntentando Remove(99):\n";
    try {
        set.Remove(99); // no existe -> lanza excepción
    }
    catch (const exception& e) {
        cerr << "Excepción capturada: " << e.what() << '\n';
    }

    cout << " FIN PRUEBA: HashSet \n";
}

int main() {
    EjecutarPruebaBST();
    EjecutarPruebaHashSet();
    return 0;
}
