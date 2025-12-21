#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#define nBateries 2
using namespace std;
/* 
He de implementar programació dinamica, 
una funcio que agafe tota la string, 
i que vaja comprobant cada parella de números
pa vore quin es més gran
*/
int inf = numeric_limits<int>::min();

int maxBat(string &l1, int i, int j, vector <vector<int> > &memo){
	// casos base
    if (j == nBateries) {return 0;}
	else if(i >= l1.size()) {return -inf;}
    else if (memo[i][j] != -1) {return memo[i][j];}
    
	// casos general + memoria
    if (j == 0) // Decenes
    {
        // Agafar el numero o no
        memo[i][j] = max(maxBat(l1, i + 1, j, memo), ((l1[i] - '0') * 10) + maxBat(l1, i + 1, j + 1, memo));
        return memo[i][j];
    }
    else if (j == 1) // Unitats
    {
        // Agafar el numero o no
        memo[i][j] = max(maxBat(l1, i + 1, j, memo), (l1[i] - '0')+ maxBat(l1, i + 1, j + 1, memo));
        return memo[i][j];
    }
    
	return 0;
}

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    int count = 0;

    while (getline(fich, l1))
    {
        if (l1.back() == '\r') l1.pop_back(); // caracter perillos que esta al final
        int estadoBusqueda = 0;
        vector <vector<int> > memo(l1.size(),vector<int>(nBateries + 1,-1));
        count += maxBat(l1, 0, estadoBusqueda, memo);
    }
    cout << count << endl;
    fich.close();

    return 0;
}
