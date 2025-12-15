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

    std::vector<std::list<Nodo>> tabla;
    size_t capacidad;
    size_t tamanio;
    double umbralFactorCarga;

    // DJB2 Funcion Hash, muy utilizada en strings, y es mejor que la suma de caracteres en ascii y la multiplicacion simple y polinomial
    size_t funcionHash(const string &key) const
    {
        size_t hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + static_cast<size_t>(c); // hash * 33 + c
        }
        return hash;
    }

    size_t h(const string &key) const
    {
        size_t hash = funcionHash(key);
        return hash % capacidad;
    }

    void rehash()
    {
        size_t nuevaCapacidad = capacidad * 2;
        std::vector<std::list<Nodo>> nuevaTabla(nuevaCapacidad);

        for (const auto &cubeta : tabla)
        {
            for (const auto &nodo : cubeta)
            {
                size_t nuevoIndice = funcionHash(nodo.key) % nuevaCapacidad;
                nuevaTabla[nuevoIndice].push_back(nodo);
            }
        }
        tabla = std::move(nuevaTabla);
        capacidad = nuevaCapacidad;
    }

public:
    TablaHash(size_t capacidadInicial = 16)
        : capacidad(capacidadInicial), tamanio(0), umbralFactorCarga(0.75)
    {
        tabla.resize(capacidad);
    }

    void insertar(const string &key, const int &valor)
    {
        if ((double)tamanio / capacidad > umbralFactorCarga)
        {
            rehash();
        }

        size_t indice = h(key);

        for (auto &nodo : tabla[indice])
        {
            if (nodo.key == key)
            {
                nodo.valor = valor;
                return;
            }
        }

        tabla[indice].push_back(Nodo(key, valor));
        tamanio++;
    }

    int *buscar(const string &key)
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

    const int *buscar(const string &key) const
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

    bool contiene(const string &key) const
    {
        return buscar(key) != nullptr;
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
        tamanio++;
        return tabla[indice].back().valor;
    }

    bool eliminar(const string &key)
    {
        size_t indice = h(key);

        auto &cubeta = tabla[indice];
        for (auto it = cubeta.begin(); it != cubeta.end(); ++it)
        {
            if (it->key == key)
            {
                cubeta.erase(it);
                tamanio--;
                return true;
            }
        }

        return false;
    }

    size_t obtenerTamanio() const { return tamanio; }
    size_t obtenerCapacidad() const { return capacidad; }
    bool vacia() const { return tamanio == 0; }
};

class Grafo
{
private:
    bool esDirigido;

    TablaHash texto_a_id;

    std::vector<string> id_a_texto;
    std::vector<std::vector<int>> adyacencia;

    int obtenerID(const string &vertice) const
    {
        const int *id = texto_a_id.buscar(vertice); // Metodos de la clase TablaHash implementada arriba
        if (id != nullptr)
            return *id;
        return -1;
    }

    long long contarCaminosDP(const string &inicio, const string &objetivo, std::vector<long long> &memo) const
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
    int numeroVertices() const { return static_cast<int>(id_a_texto.size()); }
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
        if (!texto_a_id.contiene(vertice))
        {
            int id = static_cast<int>(id_a_texto.size());
            texto_a_id.insertar(vertice, id);
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
        return texto_a_id.contiene(vertice);
    }

    long long contarCaminos(const string &origen, const string &destino) const
    {
        int u = obtenerID(origen);
        int v = obtenerID(destino);
        if (u == -1 || v == -1)
            return 0;

        if (esDirigido)
        {
            std::vector<long long> memo(id_a_texto.size(), -1);
            return contarCaminosDP(origen, destino, memo);
        }
        return 0;
    }
};

int main(void)
{
    string linea;
    Grafo grafo(true);
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
            grafo.agregarArista(origen, dest);
        }
    }
    archivo.close();
    int totalCaminos = grafo.contarCaminos("you", "out");
    cout << totalCaminos << endl;
    return 0;
}
