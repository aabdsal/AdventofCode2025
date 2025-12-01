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

    while (getline(file, line)) // while(file >> ch >> cantidad) {} ni idea de que aso existia y que el operator>> funcionava aixina
    {
        if (line.empty())
            continue;
        int dir = (line[0] == 'R') ? 1 : -1;
        int cantidad = stoi(line.substr(1));
        posicion += dir * cantidad;

        posicion = ((posicion % 100) + 100) % 100;
        if (posicion == 0)
        {
            contador++;
        }
    }
    file.close();
    cout << contador << endl;
    return 0;
}