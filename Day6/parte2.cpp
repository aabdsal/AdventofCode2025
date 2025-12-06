#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

typedef long long ll;
using namespace std;

bool es_bacia(vector<string> &lineas, int columna, int num_filas)
{
    for (int fila = 0; fila < num_filas; fila++)
    {
        if (lineas[fila][columna] != ' ')
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    ll suma = 0;

    ifstream file("input.txt");
    string linea;
    vector<string> lineas;

    int max_tamaño = -1;
    while (getline(file, linea))
    {
        lineas.push_back(linea);
        max_tamaño = max(max_tamaño, (int)linea.size());
    }
    file.close();

    for (int i = 0; i < lineas.size(); i++)
    {
        lineas[i].resize(max_tamaño, ' ');
    }
    int num_filas = lineas.size();
    int num_columnas = max_tamaño;

    for (int col = 0; col < num_columnas; col++)
    {
        if (es_bacia(lineas, col, num_filas))
        {
            continue;
        }

        int ibloque = col;
        int fbloque = col;
        while ((fbloque < num_columnas) && (!(es_bacia(lineas, fbloque, num_filas))))
        {
            ++fbloque;
        }

        vector<ll> numeros;
        char signo = ' ';
        for (int c = (fbloque - 1); c >= ibloque; c--)
        {
            string num = "";
            for (int fila = 0; fila < (num_filas - 1); fila++)
            {
                char digito = lineas[fila][c];
                if (isdigit(digito))
                {
                    num += digito;
                }
            }
            if (!(num.empty()))
            {
                numeros.push_back(stoll(num));
            }
            if (c == ibloque)
            {
                signo = lineas[(num_filas - 1)][c];
            }
        }
        if (!(numeros.empty()) && (signo != ' '))
        {
            ll resultado = numeros[0];
            for (int i = 1; i < numeros.size(); i++)
            {
                switch (signo)
                {
                case '+':
                    resultado += numeros[i];
                    break;
                case '*':
                    resultado *= numeros[i];
                    break;

                default:
                    throw runtime_error("Operador desconegut");
                }
            }
            suma += resultado;
        }
        col = fbloque - 1;
    }
    cout << suma << endl;
    return 0;
}