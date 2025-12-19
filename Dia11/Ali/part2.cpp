#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
#define ull unsigned long long

// He de crear una tabla hash que a la posicio aaa me duga a bbb i you
// Al final lo dificil del grafo es el algoritme de busqueda, pero la estrucutra es una hash table

class TableEntry
{
private:
    string key;
    vector<string> vecindario;
    bool visitado;
public:
	TableEntry(string key, string vecinos){
		this->key = key;
		this->vecindario.push_back(vecinos);
        this->visitado = false;
	}
    string getKey(){
        return this->key;
    }
    vector<string> getVecinos(){
        return this->vecindario;
    }
    bool getVisitado(){
        return this->visitado;
    }
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
    vector<vector<TableEntry>> tabla;
	int hash(string key){
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

	void insert(string key, string vecinos){
        int pos = hash(key);
        int i = search(key, pos);
		if(i != -1){
			tabla[pos][i].addVecino(vecinos);
		}else{
		    TableEntry aux = TableEntry(key, vecinos);
		    tabla[pos].push_back(aux);
		    n++;
        }
	}
	int search(string key, int pos){
        for (int i = 0; i < tabla[pos].size(); i++)
        {
            if (tabla[pos][i].getKey() == key) {return i;}
        }
        return -1;
	}
    vector<string> getVecinos(string key){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            return tabla[pos][i].getVecinos();
        }
        return {};
    }
    int getPos(string key){
        return hash(key);
    }
    int getSize(){ 
        return max; 
    }
    int getBucketSize(int i){ 
        return tabla[i].size(); 
    }
};

class Grafo
{
private:
    HashTable h1;

public:

    Grafo(int size) : h1(size) {} // aso inicialisa de veritat el constructor, de la forma habitual soles asignaem

    void insert(string key, string vecino) {
        h1.insert(key, vecino);
    }

    ull contarCaminos(string desde, string hasta, vector<vector<ull>> &memo){ // recursivitat es una pila
        if (desde == hasta) return 1;

        int pos = h1.getPos(desde);
        int i = h1.search(desde, pos);

        if (i == -1) return 0;

        if (memo[pos][i] != -1) return memo[pos][i];

        vector <string> vecinos = h1.getVecinos(desde);
        ull total = 0;
        
        for (int i = 0; i < vecinos.size(); i++){
            total += contarCaminos(vecinos[i], hasta, memo);
        }

        memo[pos][i] = total;
        return total;
    }
    // Gemini
    vector<vector<ull>> initMemo(){
        int size = h1.getSize();
        vector<vector<ull>> memo(size);
        for(int i = 0; i < size; i++){
            memo[i].resize(h1.getBucketSize(i), -1);
        }
        return memo;
    }
};

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    
    Grafo grafo(559); // numero de linies del input
    while (getline(fich, l1))
    {
        int pos = l1.find(':');
        string key = l1.substr(0, pos);

        string vecino = l1.substr(pos + 1);
        stringstream ss (vecino);

        while(ss >> vecino){
            grafo.insert(key, vecino);
        }
    }

    // Gemini
    vector<vector<ull>> memo1 = grafo.initMemo();
    ull tramo1 = grafo.contarCaminos("svr", "dac", memo1);
    
    vector<vector<ull>> memo2 = grafo.initMemo();
    ull tramo2 = grafo.contarCaminos("dac", "fft", memo2);
    
    vector<vector<ull>> memo3 = grafo.initMemo();
    ull tramo3 = grafo.contarCaminos("fft", "out", memo3);
    
    ull ruta1 = tramo1 * tramo2 * tramo3;

    vector<vector<ull>> memo4 = grafo.initMemo();
    ull tramo4 = grafo.contarCaminos("svr", "fft", memo4);
    
    vector<vector<ull>> memo5 = grafo.initMemo();
    ull tramo5 = grafo.contarCaminos("fft", "dac", memo5);
    
    vector<vector<ull>> memo6 = grafo.initMemo();
    ull tramo6 = grafo.contarCaminos("dac", "out", memo6);
    
    ull ruta2 = tramo4 * tramo5 * tramo6;

    cout << ruta1 + ruta2 << endl;
    fich.close();

    return 0;
}


