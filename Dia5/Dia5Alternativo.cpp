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
typedef long T;

struct Intervalo
{
    T inf;
    T sup;

    Intervalo(T l, T h) : inf(l), sup(h) {}
};

struct ItvTreeNode
{
    Intervalo itv;
    T max;
    ItvTreeNode *izq;
    ItvTreeNode *der;

    ItvTreeNode(const Intervalo &i) : itv(i), max(i.sup), izq(nullptr), der(nullptr) {}
};

class ItvTree
{
private:
    ItvTreeNode *root;

    void deleteTree(ItvTreeNode *node) // Para gestionar la memoria del árbol, se usa en el destructor
    {
        if (node)
        {
            deleteTree(node->izq);
            deleteTree(node->der);
            delete node;
        }
    }

    void collectIntervals(ItvTreeNode *node, std::vector<Intervalo> &intervals) // Recorre el árbol en orden y recoge y guarda los intervalos en un vector
    {
        if (node)
        {
            collectIntervals(node->izq, intervals);
            intervals.push_back(node->itv);
            collectIntervals(node->der, intervals);
        }
    }

    ItvTreeNode *insert(ItvTreeNode *node, const Intervalo &i) // Inserta un nuevo intervalo en el árbol
    {
        if (!node)
        {
            return new ItvTreeNode(i);
        }
        if (i.inf < node->itv.inf)
        {
            node->izq = insert(node->izq, i);
        }
        else
        {
            node->der = insert(node->der, i);
        }
        if (node->max < i.sup)
        {
            node->max = i.sup;
        }
        return node;
    }

public:
    ItvTree() : root(nullptr) {}

    ~ItvTree() // Destructor para liberar memoria
    {
        clear();
    }

    void insert(const Intervalo &i) // Funcion publica para insertar un intervalo, llama a la funcion privada
    {
        root = insert(root, i);
    }

    void Merge() // Fusiona los intervalos que se solapen en el árbol
    {
        std::vector<Intervalo> intervals;
        collectIntervals(root, intervals);

        // Funció lambda per a ordenar els intervals per el seu extrem inferior
        std::sort(intervals.begin(), intervals.end(),
                  [](const Intervalo &a, const Intervalo &b)
                  { return a.inf < b.inf; });

        std::vector<Intervalo> merged; // Vector per a guardar els intervals fusionats
        for (const auto &interval : intervals)
        {
            if (merged.empty() || merged.back().sup < interval.inf - 1)
            {
                merged.push_back(interval);
            }
            else
            {
                merged.back().sup = std::max(merged.back().sup, interval.sup);
            }
        }

        clear();
        for (const auto &interval : merged)
        {
            insert(interval);
        }
    }

    bool inInterval(const T &point) // Comprueba si un punto está dentro de algún intervalo del árbol
    {
        ItvTreeNode *current = root;
        while (current)
        {
            if (point >= current->itv.inf && point <= current->itv.sup)
            {
                return true;
            }
            if (current->izq && current->izq->max >= point)
            {
                current = current->izq;
            }
            else
            {
                current = current->der;
            }
        }
        return false;
    }

    ll sumaInternasItv() // Calcula la suma de las longitudes de todos los intervalos en el árbol
    {
        std::vector<Intervalo> intervals;
        collectIntervals(root, intervals);
        long long suma = 0;
        for (const auto &interval : intervals)
        {
            suma += (interval.sup - interval.inf + 1);
        }
        return suma;
    }

    void clear() // Limpia el árbol
    {
        deleteTree(root);
        root = nullptr;
    }
};

int main(void)
{
    ItvTree tree;
    ll minimo, maximo, numero;
    int frescos = 0;

    char guion;

    ifstream archivo("input.txt");
    string linea;
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    while (getline(archivo, linea))
    {
        if (linea.empty() || linea[0] == '\n')
        {
            continue;
        }
        istringstream ss(linea);
        if (ss >> minimo >> guion >> maximo)
        {
            tree.insert(Intervalo(minimo, maximo));
            continue;
        }
        tree.Merge(); // Fusiona los intervalos que se solapen
        ss.clear();
        ss.str(linea);
        if (ss >> numero)
        {
            if (tree.inInterval(numero))
            {
                ++frescos;
            }
        }
    }
    archivo.close();
    ll count = tree.sumaInternasItv();

    cout << "Cantidad de alimentos aun frescos (parte1): " << frescos << endl;
    cout << "Suma de longitud de intervalos (parte 2): " << count << endl;
    return 0;
}