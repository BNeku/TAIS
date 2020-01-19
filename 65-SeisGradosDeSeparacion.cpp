//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;


const int INFINITO = 1000000000;

//algoritmo de Floyd
//coste O(n^3) en tiempo y O(n*n) en espacio, siendo n el numero de personas
void grados(Matriz<int> &G){
	int n = G.numfils() - 1;

	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				int temp = G[i][k] + G[k][j];
				if (temp < G[i][j]) { // es mejor pasar por k
					G[i][j] = temp;
				}
			}
}

int indiceNombre(vector<string> &nombres, string n){
	bool found = false;
	int i = 1;

	while (!found){
		if (nombres[i] == n)
			found = true;

		if (nombres[i] == "VACIO"){
			nombres[i] = n;
			found = true;
		}

		i++;
	}

	i--;
	return i;
}

bool resuelveCaso() {
	int P, R;

	cin >> P >> R;

	if (!std::cin)  // fin de la entrada
		return false;

	Matriz<int> tabla(P+1, P+1, INFINITO);

	for (int d = 1; d <= P; d++){
		tabla[d][d] = 0;
	}

	vector<string> nombres(P+1, "VACIO");
	string p1,p2;
	int indice1, indice2;

	for (int i = 0; i < R; i++){
		cin >> p1 >> p2;

		indice1 = indiceNombre(nombres, p1);
		indice2 = indiceNombre(nombres, p2);

		tabla[indice1][indice2] = 1;
		tabla[indice2][indice1] = 1;
	}

	grados(tabla);
	int minGrado = 0;

	for (int i = 1; i <= P; i++){
		for (int j = i + 1; j <= P; j++){
			if (tabla[i][j]>minGrado)
				minGrado = tabla[i][j];
		}
	}

	if (minGrado == INFINITO){
		cout << "DESCONECTADA";
	}
	else{
		cout << minGrado;
	}

	cout << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos65.txt");
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
