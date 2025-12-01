#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#define INI 50

using namespace std;

int main(void)
{
    string line;
    int posicion = INI;
    int contador = 0;
    ifstream file("input.txt");

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        int dir = (line[0] == 'R') ? 1 : -1;
        int pasos = stoi(line.substr(1));

        int distancia = ((dir == 1) ? ((100 - posicion) % 100) : (posicion % 100));
        int distcero = ((distancia == 0) ? 100 : distancia);

        if (pasos >= distcero)
        {
            contador += 1 + ((pasos - distcero) / 100);
        }

        posicion = ((posicion + dir * pasos) % 100 + 100) % 100;
    }
    file.close();
    cout << contador << endl;
    return 0;
}