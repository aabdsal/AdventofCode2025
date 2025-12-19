#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class TableEntry
{
private:
    string key;
    vector<string> vecindario;
    bool visitado;
public:
    TableEntry(string key, string vecino){
        this->key = key;
        this->vecindario.push_back(vecino);
        this->visitado = false;
    }
    // Getters de una entrada
    string getKey(){
        return this->key;
    }
    vector<string> getVecinos(){
        return this->vecindario;
    }
    bool getVisitado(){
        return this->visitado;
    }
    // Setters de una entrada
    void setVisitado(bool visitado){
        this->visitado = visitado;
    }
    void addVecino(string vecino) { 
        vecindario.push_back(vecino); 
    }
};

class HashTable
{
private:
    int n, max;
    vector<vector<TableEntry> > tabla;

    int hash(string key){ // Sacar la posición sumando los valores ASCII
        int res = 0;
        for(int i = 0; i < key.length(); i++){    
            res += key[i] - '0';
        }
        return res % max;
    }

public:
    HashTable(int size){ 
        tabla.resize(size);
        max = size;
        n = 0;
    }

    void insert(string key, string vecino){ 
        int pos = hash(key);
        int i = search(key, pos);
        if(i == -1){ // Si aún no esta creada la fila, se crea
            TableEntry aux = TableEntry(key, vecino);
            tabla[pos].push_back(aux);
            n++;           
        }
        else{ // Si ya esta creada la fila con la llave, solo queda añadir los nodos a los que puede ir
            tabla[pos][i].addVecino(vecino);
        }
    }

    int search(string key, int pos){
        for (int i = 0; i < tabla[pos].size(); i++)
        {
            if (tabla[pos][i].getKey() == key) {return i;}
        }
        return -1;
    }

    // Funciones lanzadera de la función getVecinos, setVisitado y getVisitado de TableEntry
    vector<string> getVecinos(string key){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            return tabla[pos][i].getVecinos();
        }
        return {};
    }

    void marcarVisitado(string key, bool estado){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            tabla[pos][i].setVisitado(estado);
        }
    }

    bool esVisitado(string key){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            return tabla[pos][i].getVisitado();
        }
        return false;
    }
};

class Grafo
{
private:
    HashTable h1;
public:

    Grafo(int size) : h1(size) {} // aso inicialisa de veritat el constructor, de la forma habitual soles asignaem

    void insert(string key, string vecino) { // Función lanzadera del metodo insert de HashTable
        h1.insert(key, vecino);
    }

    int contarCaminos(string desde, string hasta){ // DFS, marcar primero como visitado y cuando una recursion acaba el for, marca como no visitado
        if(desde == hasta) return 1;
        vector<string> vecinos = h1.getVecinos(desde);
        
        int total = 0;
        h1.marcarVisitado(desde, true);

        for (int i = 0; i < vecinos.size(); i++){
            if (!h1.esVisitado(vecinos[i])){
                total += contarCaminos(vecinos[i], hasta);
            }
        }

        h1.marcarVisitado(desde, false);
        return total;
    }
};

int main()
{
    ifstream fich("input.txt");
    if (!fich.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string l1;
    Grafo grafo(559); // numero del linies del input

    while (getline(fich, l1))
    {
        int pos = l1.find(':');
        string key = l1.substr(0, pos);

        string vecino = l1.substr(pos + 1);
        stringstream ss(vecino);

        while(ss >> vecino){
            grafo.insert(key, vecino);
        }
    }

    int count = grafo.contarCaminos("you", "out");

    cout << count << endl;
    fich.close();

    return 0;
}


