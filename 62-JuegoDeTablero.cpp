//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INFINITO = 1000000000;

/*
		  
 f(i,j) = { T[i][j] + max(f(i-1, j-1), f(i-1,j), f(i-1, j+1)) //ojo con los laterales    i>j

 casos base:
 f(1, j) = T[1][j]

 sol = max(f(n, j))	 1<=j<=n
*/

//coste: O(N^2) en espacio y O(N ^ 2 + N) en tiempo donde N es el numero de filas/columnas del tablero
void maxValor(Matriz<int> &tablero, int &start, int &suma, const int &N){

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			//escogemos el valor máximo entre las tres casillas permitidas, diagonales y vertical
			//a este le sumamos el valor de la propia casilla, obteniendo un nuevo valor para la casilla
			tablero[i][j] = max(tablero[i - 1][j - 1], max(tablero[i - 1][j], tablero[i-1][j+1]))+tablero[i][j];
		}
	}
	//recorremos la primera fila, donde estás sumas máximas en cada casilla
	//la casilla con la suma más alta es la respuesta que buscamos
	for (int i = 1; i <= N; i++){
		if (suma < tablero[N][i]){
			start = i;
			suma = tablero[N][i];
		}
	}

}

bool resuelveCaso() {
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	Matriz<int> tablero(N+1,N+2,0);

	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			cin >> tablero[i][j];
		}
	}

	int inicio = 0, suma = 0;

	maxValor(tablero, inicio, suma, N);
	
	cout << suma << " " << inicio << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos62.txt");
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