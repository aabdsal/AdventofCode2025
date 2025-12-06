#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void contar_candidatos(const vector<vector<char>> &matriz, int *candidatos)
{
    int contador = 0;
    for (int i = 0; i < (int)matriz.size(); ++i)
    {
        for (int j = 0; j < (int)matriz[i].size(); ++j)
        {
            if (matriz[i][j] != '@')
                continue;
            for (int di = -1; di <= 1; ++di)
            {
                for (int dj = -1; dj <= 1; ++dj)
                {
                    int fila = i + di;
                    int columna = j + dj;
                    if (fila < 0 || fila >= (int)matriz.size() || columna < 0 || columna >= (int)matriz[i].size())
                        continue;
                    if (di == 0 && dj == 0)
                        continue;
                    if (matriz[fila][columna] != '@')
                    {
                        continue;
                    }
                    ++contador;
                }
            }
            if (contador < 4)
            {
                ++(*candidatos);
            }
            contador = 0;
        }
    }
}

int main(void)
{
    vector<vector<char>> matriz;
    int n = 0;
    int m = 0;
    int contador = 0;
    int candidatos = 0;
    ifstream archivo("input.txt");
    string linea;
    while (getline(archivo, linea))
    {
        if ((int)matriz.size() <= m)
        {
            matriz.push_back(vector<char>(linea.size(), '.'));
        }
        for (n = 0; n < (int)linea.size(); ++n)
        {
            if (linea[n] != '@')
                continue;
            matriz[m][n] = linea[n];
        }
        ++m;
    }
    archivo.close();

    contar_candidatos(matriz, &candidatos);

    cout << candidatos << "\n";

    return 0;
}