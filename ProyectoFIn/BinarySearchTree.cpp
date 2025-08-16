#pragma once

#include <iostream>
#include <stack>   // para usar pilas en recorridos y borrados iterativos
#include <utility> // para std::pair, por si lo usamos
using namespace std;
#include <cmath>   // para funciones de logaritmos en altura mínima

// Calcular logaritmo en cualquier base
static inline double log_base_n(double x, double base)
{
    // Si los datos no son válidos, regresamos 0
    if (x <= 0 || base <= 0 || base == 1.0) return 0.0;
    return std::log(x) / std::log(base);
}

// Calcular la altura mínima posible de un árbol con n nodos y máximo de hijos
static inline int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    if (numeroDeNodos <= 0 || maximoDeHijosPorNodo < 2) return 0;
    double numerador = static_cast<double>(numeroDeNodos) * (maximoDeHijosPorNodo - 1) + 1.0;
    double altura = std::log(numerador) / std::log(static_cast<double>(maximoDeHijosPorNodo));
    return static_cast<int>(std::ceil(altura)) - 1;
}

// Clase BinarySearchTree
template <typename T>
class BinarySearchTree
{
    // Clase interna para representar un nodo del árbol
    class TreeNode
    {
    public:
        TreeNode()
        {
            parent = leftChild = rightChild = nullptr;
            data = {};
        }

        TreeNode(T data)
        {
            parent = leftChild = rightChild = nullptr;
            this->data = data;
        }

        T data;               // El dato que guarda el nodo
        TreeNode* parent;     // Apuntador al nodo padre
        TreeNode* leftChild;  // Apuntador al hijo izquierdo
        TreeNode* rightChild; // Apuntador al hijo derecho
    };

public:
    BinarySearchTree()
    {
        root = nullptr; // al inicio no hay nada
        count = 0;      // contador de nodos en 0
    }

    ~BinarySearchTree()
    {
        // borra el árbol completo de forma segura (iterativa)
        DestroyIterative();
    }

    // Agrega un nodo usando recursividad
    void AddWithAddRecursive(T value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            count++;
            return;
        }
        TreeNode* currentNode = root;
        AddRecursive(value, currentNode);
    }

    // Crea un nuevo nodo y lo inserta como hijo izq o der
    void InsertarNode(TreeNode* currentNode, bool isLeftChild, T value)
    {
        TreeNode* newNode = new TreeNode(value);
        newNode->parent = currentNode;
        if (isLeftChild)
            currentNode->leftChild = newNode;
        else
            currentNode->rightChild = newNode;
        count++;
    }

    // Inserta recursivamente dependiendo si el valor es mayor o menor
    void AddRecursive(T value, TreeNode* currentNode)
    {
        if (value > currentNode->data)
        {
            if (currentNode->rightChild == nullptr)
            {
                InsertarNode(currentNode, false, value);
                return;
            }
            else
            {
                return AddRecursive(value, currentNode->rightChild);
            }
        }
        else // los valores iguales los mando a la izquierda
        {
            if (currentNode->leftChild == nullptr)
            {
                InsertarNode(currentNode, true, value);
                return;
            }
            else
            {
                return AddRecursive(value, currentNode->leftChild);
            }
        }
    }

    // Inserción de forma iterativa (sin recursividad)
    void Add(T value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            count++;
            return;
        }
        TreeNode* currentNode = root;
        while (currentNode != nullptr)
        {
            if (value > currentNode->data)
            {
                if (currentNode->rightChild == nullptr)
                {
                    InsertarNode(currentNode, false, value);
                    return;
                }
                else currentNode = currentNode->rightChild;
            }
            else
            {
                if (currentNode->leftChild == nullptr)
                {
                    InsertarNode(currentNode, true, value);
                    return;
                }
                else currentNode = currentNode->leftChild;
            }
        }
    }

    // Recorre el árbol en orden usando recursividad
    void InOrderWithRecursive()
    {
        InOrderRecursive(root);
    }

    // Calcula la altura mínima con la fórmula de arriba
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2);
    }

    // Busca de forma recursiva (devuelve true si existe)
    bool SearchWithRecursive(T value)
    {
        TreeNode* resultNode = SearchRecursive(root, value);
        return resultNode != nullptr;
    }

    // Búsqueda iterativa (me muevo por el árbol sin recursión)
    TreeNode* SearchIterative(T value)
    {
        TreeNode* current = root;
        while (current != nullptr)
        {
            if (value == current->data) return current;
            else if (value < current->data) current = current->leftChild;
            else current = current->rightChild;
        }
        return nullptr;
    }

    // Forma corta para buscar (iterativa)
    bool Search(T value)
    {
        return SearchIterative(value) != nullptr;
    }

    // Elimina un nodo según los 3 casos clásicos
    void Delete(T value)
    {
        TreeNode* nodeToDelete = SearchRecursive(root, value);
        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor value en este árbol." << endl;
            return;
        }

        // caso 1: es hoja (no tiene hijos)
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nullptr;
                else
                    nodeToDelete->parent->rightChild = nullptr;
            }
            else
            {
                root = nullptr;
            }
            count--;
            delete nodeToDelete;
            return;
        }

        // caso 2: solo hijo derecho
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
            }
            else
            {
                root = nodeToDelete->rightChild;
            }

            nodeToDelete->rightChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // caso 2: solo hijo izquierdo
        if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
            }
            else
            {
                root = nodeToDelete->leftChild;
            }

            nodeToDelete->leftChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // caso 3: tiene dos hijos
        TreeNode* successorNode = Successor(nodeToDelete);

        successorNode->leftChild = nodeToDelete->leftChild;
        if (nodeToDelete->leftChild)
            nodeToDelete->leftChild->parent = successorNode;

        if (successorNode->parent)
        {
            if (successorNode->parent->leftChild == successorNode)
                successorNode->parent->leftChild = successorNode->rightChild;
            else
                successorNode->parent->rightChild = successorNode->rightChild;
        }
        if (successorNode->rightChild)
            successorNode->rightChild->parent = successorNode->parent;

        successorNode->rightChild = nodeToDelete->rightChild;
        if (nodeToDelete->rightChild)
            nodeToDelete->rightChild->parent = successorNode;

        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = successorNode;
            else
                nodeToDelete->parent->rightChild = successorNode;
        }
        else
        {
            root = successorNode;
        }

        count--;
        delete nodeToDelete;
    }

    // Recorrido post-order usando dos pilas
    void PostOrderIterative()
    {
        if (root == nullptr) return;

        std::stack<TreeNode*> stack1;
        std::stack<TreeNode*> stack2;

        stack1.push(root);
        while (!stack1.empty())
        {
            TreeNode* node = stack1.top();
            stack1.pop();
            stack2.push(node);

            if (node->leftChild)  stack1.push(node->leftChild);
            if (node->rightChild) stack1.push(node->rightChild);
        }

        while (!stack2.empty())
        {
            TreeNode* node = stack2.top();
            stack2.pop();
            cout << node->data << endl;
        }
    }

    // Versión diferente de post-order, pero con una sola pila
    void PostOrderIterativeOneStack()
    {
        std::stack<TreeNode*> st;
        TreeNode* current = root;
        TreeNode* lastVisited = nullptr;

        while (current || !st.empty())
        {
            if (current)
            {
                st.push(current);
                current = current->leftChild;
            }
            else
            {
                TreeNode* peek = st.top();
                if (peek->rightChild && lastVisited != peek->rightChild)
                {
                    current = peek->rightChild;
                }
                else
                {
                    cout << peek->data << endl;
                    lastVisited = peek;
                    st.pop();
                }
            }
        }
    }

    // Borra todo el árbol en orden post-order recursivo
    void ClearPostOrderRecursive()
    {
        ClearPostOrderRecursiveImpl(root);
        root = nullptr;
        count = 0;
    }

private:
    TreeNode* Maximum(TreeNode* node)
    {
        if (node == nullptr) return nullptr;
        TreeNode* maximum = node;
        while (maximum->rightChild != nullptr)
            maximum = maximum->rightChild;
        return maximum;
    }

    TreeNode* Minimum(TreeNode* node)
    {
        if (node == nullptr) return nullptr;
        TreeNode* minimum = node;
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;
        return minimum;
    }

    TreeNode* Successor(TreeNode* node)
    {
        if (node->rightChild != nullptr)
            return Minimum(node->rightChild);

        TreeNode* ancestor = node->parent;
        while (ancestor != nullptr && node == ancestor->rightChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    TreeNode* SearchRecursive(TreeNode* currentNode, T value)
    {
        if (currentNode == nullptr) return nullptr;
        if (currentNode->data == value) return currentNode;
        if (value < currentNode->data)
            return SearchRecursive(currentNode->leftChild, value);
        return SearchRecursive(currentNode->rightChild, value);
    }

    void InOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    void DestroyIterative()
    {
        if (root == nullptr) return;

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty())
        {
            TreeNode* node = st.top();

            if (node->leftChild == nullptr && node->rightChild == nullptr)
            {
                st.pop();
                delete node;
            }
            else
            {
                if (node->rightChild)
                {
                    st.push(node->rightChild);
                    node->rightChild = nullptr;
                }
                if (node->leftChild)
                {
                    st.push(node->leftChild);
                    node->leftChild = nullptr;
                }
            }
        }

        root = nullptr;
        count = 0;
    }

    void ClearPostOrderRecursiveImpl(TreeNode* node)
    {
        if (!node) return;
        ClearPostOrderRecursiveImpl(node->leftChild);
        ClearPostOrderRecursiveImpl(node->rightChild);
        delete node;
    }

public:
    TreeNode* root;
    int count;
};
