#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

#define nBateries 12

using namespace std;
/* 
He de implementar programació dinamica, 
una funcio que agafe tota la string, 
i que vaja comprobant cada parella de números
pa vore quin es més gran
*/

const vector <long> potencies = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000};  
long inf = numeric_limits<long>::min();

long maxBat(string &l1, int i, int j, vector <vector<long> > &memo){
	// casos base
    if (j == nBateries) {return 0;}
	else if(i >= l1.size()) {return -inf;}
    else if (memo[i][j] != -1) {return memo[i][j];}
    
	// casos general + memoria
    // Agafar el numero o no
    long nDigitos = potencies[11 - j];
    memo[i][j] = max(maxBat(l1, i + 1, j, memo), ((l1[i] - '0') * nDigitos)+ maxBat(l1, i + 1, j + 1, memo));
    return memo[i][j];
}

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    long count = 0;  
    while (getline(fich, l1))
    {
        if (l1.back() == '\r') l1.pop_back(); // caracter perillos que esta al final
        int estadoBusqueda = 0;
        vector <vector<long> > memo(l1.size(),vector<long>(nBateries + 1,-1));
        count += maxBat(l1, 0, estadoBusqueda, memo);
    }
    cout << count << endl;
    fich.close();

    return 0;
}
