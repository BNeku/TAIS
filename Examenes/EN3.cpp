//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

struct festival{
	int numGrupos;
	int precio;
};

/*
maxGrupos(i,j) = maximizar el numero de grupos que puede ver con un presupuesto de P

pi= precio entrada festival i
ni= numero de grupos del festival i

				 maxGrupos(i-1,j)  si pi>P
maxGrupos(i,j) = max(maxGrupos(i-1,j), maxGrupos(i-1,j-pi)+ni)

Casos Base:
maxGrupos(0,j) = 0 si no hay grupos a los que ver, da igual el dinero
maxGrupos(0,j) = 0 si no tenemos dinero, no podemos ver ningún grupo

Coste en tiempo y espacio: O(N*P)
*/
int maxGrupos(vector<festival> &v, const int &P){
	int N = v.size();
	Matriz<int> tabla(N, P+1, 0);

	for (int i = 1; i < N; i++){
		for (int j = 1; j <= P; j++){
			if (v[i].precio > j){
				tabla[i][j] = tabla[i - 1][j];
			}else{
				tabla[i][j] = max(tabla[i - 1][j], tabla[i - 1][j - v[i].precio] + v[i].numGrupos);
			}
		}
	}
	
	return tabla[N-1][P];
}

bool resuelveCaso() {
	int P, N;

	cin >> P >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<festival> v(N + 1);
	festival aux;

	for (int i = 1; i <= N; i++){
		cin >> aux.numGrupos >> aux.precio;
		v[i] = aux;
	}

	cout << maxGrupos(v, P) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casosEN3.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
