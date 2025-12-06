#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

typedef long long ll;

using namespace std;

int main(void)
{
    ifstream file("input.txt");
    vector<vector<int>> matriz;
    vector<char> filaSignos;
    string linea;
    ll suma = 0;

    while (getline(file, linea))
    {
        vector<int> fila;
        stringstream ss(linea);
        int num;
        char signo;

        while (ss >> num)
        {
            fila.push_back(num);
        }
        ss.clear();    // Per a que ss puga ser reutilitzat per a llegir els signes.
        ss.str(linea); // Per a que funciones en chars despres de llegir els nums, sino fa coses rares en el segon while.
        while (ss >> signo)
        {
            if (!isdigit(signo))
            {
                filaSignos.push_back(signo);
            }
        }
        if (!(fila.empty()))
        {
            matriz.push_back(fila);
        }
    }
    file.close();
    for (int i = 0; i < matriz[0].size(); i++) // Depenenent del signe de cada posicion del vector filaSignos, es realitza ixa operacion entre els elements de la ica columna en la matriu
    {
        ll resultadoColumna = matriz[0][i];
        for (int j = 1; j < matriz.size(); j++)
            switch (filaSignos[i])
            {
            case '+':
                resultadoColumna += matriz[j][i];
                break;
            case '*':
                resultadoColumna *= matriz[j][i];
                break;
            default:
                break;
            }
        suma += resultadoColumna;
    }
    cout << suma << endl;
    return 0;
}