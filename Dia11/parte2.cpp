#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class TablaHash
{
private:
    struct Nodo
    {
        string key;
        int valor;
        Nodo(const string &c, const int &v) : key(c), valor(v) {}
    };

    vector<list<Nodo>> tabla;
    size_t max;
    size_t tam;
    double umbralFactorCarga; // Usado en rehashing para saber cuando aumentar el tamaño de la tabla (idea tomada de internet)

    // DJB2 Funcion Hash, muy utilizada en strings, y es mejor que la suma de caracteres en ascii y la multiplicacion simple y polinomial (internet)
    size_t funcionHash(const string &key) const
    {
        size_t hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + static_cast<size_t>(c);
        }
        return hash;
    }

    size_t h(const string &key) const
    {
        size_t hash = funcionHash(key);
        return hash % max;
    }

    void rehash()
    {
        size_t nuevamax = max * 2;
        vector<list<Nodo>> nuevaTabla(nuevamax);

        for (const auto &cubeta : tabla)
        {
            for (const auto &nodo : cubeta)
            {
                size_t nuevoIndice = funcionHash(nodo.key) % nuevamax;
                nuevaTabla[nuevoIndice].push_back(nodo);
            }
        }
        tabla = move(nuevaTabla);
        max = nuevamax;
    }

public:
    TablaHash(size_t maxInicial = 16)
        : max(maxInicial), tam(0), umbralFactorCarga(0.75)
    {
        tabla.resize(max);
    }

    void insert(const string &key, const int &valor)
    {
        if ((double)tam / max > umbralFactorCarga)
        {
            rehash();
        }

        size_t indice = h(key);

        for (auto &nodo : tabla[indice]) // Se utiliza el & en la variable nodo para modificar el valor directamente en la tabla, no guardarlo en otra variable
        {
            if (nodo.key == key)
            {
                nodo.valor = valor;
                return;
            }
        }

        tabla[indice].push_back(Nodo(key, valor));
        tam++;
    }

    int *search(const string &key) // Version no constante
    {
        size_t indice = h(key);

        for (auto &nodo : tabla[indice])
        {
            if (nodo.key == key)
            {
                return &nodo.valor;
            }
        }

        return nullptr;
    }

    const int *search(const string &key) const // Sobrecarga para version constante (variables constantes), son iguales, pero una acepta constantes y la otra no
    {
        size_t indice = h(key);

        for (const auto &nodo : tabla[indice])
        {
            if (nodo.key == key)
            {
                return &nodo.valor;
            }
        }

        return nullptr;
    }

    bool contains(const string &key) const
    {
        return search(key) != nullptr;
    }

    int &operator[](const string &key)
    {
        size_t indice = h(key);

        for (auto &nodo : tabla[indice])
        {
            if (nodo.key == key)
            {
                return nodo.valor;
            }
        }

        tabla[indice].push_back(Nodo(key, 0));
        tam++;
        return tabla[indice].back().valor;
    }

    bool remove(const string &key)
    {
        size_t indice = h(key);

        auto &cubeta = tabla[indice];
        for (auto it = cubeta.begin(); it != cubeta.end(); ++it)
        {
            if (it->key == key)
            {
                cubeta.erase(it);
                tam--;
                return true;
            }
        }

        return false;
    }

    size_t getSize() const { return tam; }
    size_t getMax() const { return max; }
    bool empty() const { return tam == 0; }
};

class Grafo
{
private:
    bool esDirigido;

    TablaHash texto_a_id;

    vector<string> id_a_texto;
    vector<vector<int>> adyacencia;

    int obtenerID(const string &vertice) const
    {
        const int *id = texto_a_id.search(vertice);
        if (id != nullptr)
            return *id;
        return -1;
    }

    long long contarCaminosDP(const string &inicio, const string &objetivo, vector<long long> &memo) const
    {
        if (inicio == objetivo)
            return 1;
        if (memo[obtenerID(inicio)] != -1)
            return memo[obtenerID(inicio)];

        long long total = 0;
        for (int vecino : adyacencia[obtenerID(inicio)])
        {
            total += contarCaminosDP(id_a_texto[vecino], objetivo, memo);
        }
        return (memo[obtenerID(inicio)] = total);
    }

public:
    Grafo(bool dirigido = false) : esDirigido(dirigido) {}
    ~Grafo() = default;

    bool dirigido() const { return esDirigido; }
    int numeroVertices() const { return (int)(id_a_texto.size()); }
    int numeroAristas() const
    {
        int total = 0;
        for (const auto &lista : adyacencia)
        {
            total += lista.size();
        }
        return esDirigido ? total : total / 2;
    }

    void agregarVertice(string &vertice)
    {
        if (!texto_a_id.contains(vertice))
        {
            int id = (int)(id_a_texto.size());
            texto_a_id.insert(vertice, id);
            id_a_texto.push_back(vertice);
            adyacencia.resize(id + 1);
        }
    }

    void agregarArista(string &origen, string &destino)
    {
        if (!existeVertice(origen))
        {
            cerr << "Error: Vertice origen no existe en el grafo." << endl;
            return;
        }
        if (!existeVertice(destino))
        {
            cerr << "Error: Vertice destino no existe en el grafo." << endl;
            return;
        }

        int u = obtenerID(origen);
        int v = obtenerID(destino);

        // Los checks de arriba garantizan que u y v != -1

        for (int vecino : adyacencia[u])
            if (vecino == v)
                return;

        adyacencia[u].push_back(v);
        if (!esDirigido && u != v)
        {
            adyacencia[v].push_back(u);
        }
    }

    bool existeVertice(const string &vertice) const
    {
        return texto_a_id.contains(vertice);
    }

    long long contarCaminos(const string &origen, const string &destino) const
    {
        int u = obtenerID(origen);
        int v = obtenerID(destino);
        if (u == -1 || v == -1)
            return 0;

        if (esDirigido)
        {
            vector<long long> memo(id_a_texto.size(), -1);
            return contarCaminosDP(origen, destino, memo);
        }
        return 0;
    }

    long long contarCaminosObl(const string &origen, const string &destino, const vector<string> &nodosObligatorios) const
    {
        if (nodosObligatorios.empty())
            return contarCaminos(origen, destino);

        long long totalCaminos = 1;
        string inicioActual = origen;

        for (const string &nodoObligatorio : nodosObligatorios)
        {
            long long caminosParciales = contarCaminos(inicioActual, nodoObligatorio);
            if (caminosParciales == 0)
                return 0;

            totalCaminos *= caminosParciales;
            inicioActual = nodoObligatorio;
        }

        long long caminosFinales = contarCaminos(inicioActual, destino);
        if (caminosFinales == 0)
            return 0;

        totalCaminos *= caminosFinales;
        return totalCaminos;
    }
};

int main(void)
{
    string linea;
    Grafo grafo(true); // Grafo dirigido
    ifstream archivo("input.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    while (getline(archivo, linea))
    {
        vector<string> destinos;
        size_t pos = linea.find(':');
        string origen = linea.substr(0, pos);
        string destino = linea.substr(pos + 1);
        istringstream ss(destino);
        while (ss >> destino)
        {
            destinos.push_back(destino);
        }
        grafo.agregarVertice(origen);
        for (string &dest : destinos)
        {
            grafo.agregarVertice(dest);
            grafo.agregarArista(origen, dest); // Esta funcion de por si ya agrega los vertices/nodos (aunque no creo que esto deberis ser asi, asi lo implementé)
        }
    }
    archivo.close();
    //     // Ahora necesito contar todos los caminos (no nodos) que me pueden llevar desde "you" hasta "out"
    // -- Alternativa que funciona --

    // long long totalCaminos = ((grafo.contarCaminos("svr", "fft") * grafo.contarCaminos("fft", "dac") * grafo.contarCaminos("dac", "out")) +
    //                                (grafo.contarCaminos("svr", "dac") * grafo.contarCaminos("dac", "fft") * grafo.contarCaminos("fft", "out")));

    vector<string> nodosObligatorios = {"fft", "dac"};
    long long totalCaminos = grafo.contarCaminosObl("svr", "out", nodosObligatorios);
    cout << totalCaminos << endl;
    return 0;
}