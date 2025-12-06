#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void contar_candidatos(vector<vector<char>> &matriz, vector<vector<int>> &Mcandidatos, int *candidatos)
{
    int contador = 0;
    for (int i = 0; i < (int)matriz.size(); ++i)
    {
        for (int j = 0; j < (int)matriz[i].size(); ++j)
        {
            if (matriz[i][j] != '@')
                continue;
            for (int di = -1; di <= 1; ++di) // Aso busca en les 8 posiciones adyacents
            {
                for (int dj = -1; dj <= 1; ++dj)
                {
                    int fila = i + di;
                    int columna = j + dj;
                    if (fila < 0 || fila >= (int)matriz.size() || columna < 0 || columna >= (int)matriz[i].size()) // Mira els limits
                        continue;
                    if (di == 0 && dj == 0) // Esta es la mateixa posicio que la original, aixina que te la botes
                        continue;
                    if (matriz[fila][columna] != '@') // Si no hi ha un candidat en la posicio adyacente, continua
                        continue;
                    ++contador;
                }
            }
            if (contador < 4)
            {
                ++(*candidatos);
                Mcandidatos[i][j] = 1; // Marcar la posicion como candidato
            }
            contador = 0;
        }
    }
    for (int i = 0; i < (int)Mcandidatos.size(); ++i) // Aso se fa despues perque si no interferix en la primera pasada
    {
        for (int j = 0; j < (int)Mcandidatos[i].size(); ++j)
        {
            if (Mcandidatos[i][j] == 1)
            {
                matriz[i][j] = '.';    // Actualizar la matriz original para marcar los candidatos
                Mcandidatos[i][j] = 0; // Resetear la posicion en la matriz de candidatos
            }
        }
    }
}

int main(void)
{
    vector<vector<char>> matriz;
    vector<vector<int>> Mcandidatos; // Matriz para almacenar la posicion de los candidatos, inicializada al principio como vacia (0s)
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
            Mcandidatos.push_back(vector<int>(linea.size(), 0));
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
    while (true) // Repetir hasta que no haya mas candidatos
    {
        int x = candidatos;
        contar_candidatos(matriz, Mcandidatos, &candidatos); // Actaliza la variable candidatos si hay mas candidatos
        if (x == candidatos)
        {
            break;
        } // No se ha actualizado la variable candidatos
    }

    cout << candidatos << "\n";

    return 0;
}