// para la primer parte del desafio que no es muy dificil, quiero emepezar a porbar las variables tipo size_t, para no tener que hacer siempre casts con el
// return de ciertas funciones de STL.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

int BFSCola(int patron, const vector<int> &botones, size_t tamañoP)
{
    int total = 0;
    vector<int> distancias(1 << tamañoP, -1);
    queue<int> q;
    distancias[0] = 0;
    q.push(0);

    while (!q.empty())
    {
        int estadoActual = q.front(); // Traguem el primer element
        q.pop();                      // L'eliminem per a no tornar-lo a llegir

        if (estadoActual == patron) // Si amb ixe estat ja hem aconseguit el patro que volem, pues ahi acabem
        {
            break;
        }

        for (int boton : botones) // Mentres que no, provem tots els botons
        {
            int nuevoEstado = estadoActual ^ boton; // El nou estat es el resultat de fer XOR entre l'estat actual i el botó que elegim
            if (distancias[nuevoEstado] == -1)      // Si no hem visitat encara este estat, afegim la distancia que hi ha.
            {
                distancias[nuevoEstado] = distancias[estadoActual] + 1;
                q.push(nuevoEstado);
            }
        }
    }
    return (distancias[patron]); // Retornem la distancia al patro que volem, si no s'ha pogut aconseguir, sera -1
}

int main(void) // les variables size_t estan molt xetes, pareixen unsigned int normals i no cal fer casts per a comparar-les amb returns de alguns funcions, que loco
{
    string line;
    int total = 0;
    ifstream file("input.txt");
    while (getline(file, line))
    {
        size_t posIni = line.find('[');
        size_t posFin = line.find(']');
        string patron = line.substr(posIni + 1, posFin - posIni - 1);
        size_t tamañoP = patron.size();

        int patronBinario = 0;
        for (size_t i = 0; i < tamañoP; ++i) // Asi es transforma el patro que ens donen en un numero binari
        {
            if (patron[i] == '#')
            {
                patronBinario |= (1 << i); // Cortesia de IIS
            }
        } // Patro parsejat i convertit a binari

        vector<int> botones;
        size_t pos = (posFin + 1); // saltar espacio despues de ']'
        while (pos < line.size() && line[pos] != '{')
        {
            if (line[pos] == '(')
            {
                size_t posCierre = line.find(')', pos);
                string botonStr = line.substr(pos + 1, posCierre - pos - 1);

                int botonNum = 0;
                stringstream ss(botonStr);
                string segmento;
                while (getline(ss, segmento, ','))
                {
                    int num = stoi(segmento);
                    botonNum |= (1 << num);
                }
                botones.push_back(botonNum);
                pos = posCierre + 1;
            }
            else
            {
                ++pos;
            }
        } // Fins asi, tot es per a llegir i parsejar l'input, me ha costat mes fer tot aso que el BFS generic en coles.
        total += BFSCola(patronBinario, botones, tamañoP);
    }
    cout << total << endl;
    return 0;
}