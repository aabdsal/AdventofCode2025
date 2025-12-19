// Haciendo uso de un árbol de intervalos para gestionar los intervelos y de memoria inteligente para menejar los nodos del árbol, podemos "optimizar" y resolver
// el problema.
// Esta es la implementacion parcial del árbol de intervalos, adaptada a este problema concretamente.
// Esta implementacion ha sido extraida y adaptada de mi fichero de cabecera para arboles de intervalos hecha en el pasado para practicar y entender mejor
// este tipo de arboles.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long T; // Tipo de datos para los extremos de los intervalos, le puse T para asemejarlo a un template

struct Intervalo
{
    T inf;          // Limite inferior del intervalo
    T sup;          // Limite superior del intervalo
    T rango() const // Devuelve la longitud del intervalo
    {
        return ((sup - inf) + 1);
    }

    Intervalo(T l, T h) : inf(l), sup(h) {} // Constructor del intervalo
};

struct ItvTreeNode
{
    Intervalo itv;    // Intervalo almacenado en el nodo
    T max;            // Valor máximo en el subárbol con raíz en este nodo
    ItvTreeNode *izq; // Hijo izquierdo
    ItvTreeNode *der; // Hijo derecho

    ItvTreeNode(const Intervalo &i) : itv(i), max(i.sup), izq(nullptr), der(nullptr) {} // Constructor del nodo
};

class ItvTree
{
private:
    ItvTreeNode *root; // Nodo raíz del árbol

    void deleteTree(ItvTreeNode *node) // Para gestionar la memoria del árbol, se usa en el destructor, se llama recursivamente liberando cada nodo.
    {
        if (node)
        {
            deleteTree(node->izq);
            deleteTree(node->der);
            delete (node);
        }
    }

    ItvTreeNode *insert(ItvTreeNode *node, const Intervalo &i) // Inserta un nuevo intervalo en el árbol
    {
        if (!node)
        {
            return new ItvTreeNode(i); // Crear un nuevo nodo si el nodo actual es nulo
        }
        if (i.inf < node->itv.inf) // Insertar en el subárbol izquierdo o derecho según el límite inferior
        {
            node->izq = insert(node->izq, i);
        }
        else
        {
            node->der = insert(node->der, i);
        }
        if (node->max < i.sup) // Actualizar el valor máximo del nodo
        {
            node->max = i.sup;
        }
        return (node);
    }
    ItvTreeNode *MergeUtil(ItvTreeNode *node) // Función recursiva para fusionar intervalos que se solapan
    {
        if (!node) // Caso base
        {
            return (nullptr); // Nodo nulo
        }

        // Fusionar en subárbol izquierdo y derecho (postorden)
        node->izq = MergeUtil(node->izq);
        node->der = MergeUtil(node->der);

        // Comprobar si el intervalo actual se solapa con el izquierdo
        if (node->izq && node->izq->itv.sup >= node->itv.inf - 1)
        {
            node->itv.inf = min(node->izq->itv.inf, node->itv.inf);
            node->itv.sup = max(node->izq->itv.sup, node->itv.sup);
            ItvTreeNode *temp = node->izq;
            node->izq = temp->izq;
            delete (temp);
        }

        // Comprobar si el intervalo actual se solapa con el derecho
        if (node->der && node->der->itv.inf <= node->itv.sup + 1)
        {
            node->itv.inf = min(node->der->itv.inf, node->itv.inf);
            node->itv.sup = max(node->der->itv.sup, node->itv.sup);
            ItvTreeNode *temp = node->der;
            node->der = temp->der;
            delete (temp);
        }

        return (node);
    }

    ll sumaRec(ItvTreeNode *node) // Función recursiva para calcular la suma de las longitudes de los intervalos
    {
        if (!node)
        {
            return (0);
        }
        return (node->itv.rango() + sumaRec(node->izq) + sumaRec(node->der)); // Suma la longitud del intervalo actual y las longitudes de los subárboles izquierdo y derecho
    }

public:
    ItvTree() : root(nullptr) {}

    ~ItvTree() // Destructor para liberar memoria, llama a la función clear, que a su vez llama a deleteTree
    {
        clear();
    }

    void insert(const Intervalo &i) // Funcion publica para insertar un intervalo, llama a la funcion privada
    {
        root = insert(root, i);
    }

    ItvTreeNode *Merge() // Fusiona los intervalos que se solapen en el árbol, llama a la función privada MergeUtil
    {
        return (MergeUtil(root));
    }

    bool inInterval(const T &point) // Comprueba si un punto está dentro de algún intervalo del árbol
    {
        ItvTreeNode *current = root; // Empezar desde la raíz
        while (current)
        {
            if (point >= current->itv.inf && point <= current->itv.sup) // Si el punto está dentro del intervalo actual
            {
                return (true); // Decimos que si
            }
            if (current->izq && current->izq->max >= point) // Sino, decidimos si ir al hijo izquierdo o derecho
            {
                current = current->izq;
            }
            else
            {
                current = current->der;
            }
        }
        return (false);
    }

    ll sumaInternasItv() // Calcula la suma de las longitudes de todos los intervalos en el árbol, llama a la función privada sumaRec
    {
        return (sumaRec(root));
    }

    void clear() // Limpia el árbol llamando a deleteTree y establece la raíz a nulo
    {
        deleteTree(root);
        root = nullptr;
    }
};

int main(void)
{
    ItvTree tree;              // Instancia del árbol de intervalos
    ll minimo, maximo, numero; // Variables para los límites de los intervalos y el número a comprobar
    int frescos = 0;

    char guion;

    ifstream archivo("input.txt");
    string linea;
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    while (getline(archivo, linea) && !linea.empty()) // Leer intervalos hasta una línea vacía
    {
        istringstream ss(linea);
        if (ss >> minimo >> guion >> maximo)
        {
            tree.insert(Intervalo(minimo, maximo));
        }
    }

    tree.Merge(); // Fusiono los intervalos que se solapan

    while (getline(archivo, linea)) // Sigo a partir de los numeros
    {
        istringstream ss(linea);
        if (ss >> numero)
        {
            if (tree.inInterval(numero)) // Compruebo si el número está en algún intervalo
            {
                ++frescos; // Si estan, se consideran frescos
            }
        }
    }
    archivo.close();
    ll count = tree.sumaInternasItv(); // Suma de las longitudes de los intervalos

    cout << "Cantidad de alimentos aun frescos (parte1): " << frescos << endl;
    cout << "Suma de longitud de intervalos (parte 2): " << count << endl;
    return 0;
}