#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef long long ll;

int main(void)
{

    vector<pair<ll, ll>> rangos;
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
            rangos.push_back({minimo, maximo});
            continue;
        }
        ss.clear();
        ss.str(linea);
        if (ss >> numero)
        {
            for (auto &rango : rangos)
            {
                if (numero >= rango.first && numero <= rango.second)
                {
                    ++frescos;
                    break; // Per a no comprobar mes rangos que si no peta tot
                }
            }
        }
    }
    archivo.close();
    cout << frescos << endl;
    return 0;
}