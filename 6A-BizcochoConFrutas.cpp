//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INFINITO = 1000000000;

/*
	bizcocho(i,j)= maximo num de días que pueden comer la misma fruta en un bizcocho entre i y j
solucion: bizcocho(0,L)
caso base:
	bizcocho(i, i+1)=0 //solo quedan dos pedazos en el bizcocho, siempre es 0 porque nunca hay dos pedazos iguales de fruta juntos
caso recursivo:
				  | bizcocho(i+1, j-1)+1  si B[i]==B[j]=1 ó 2
	bizcocho(i,j)={ max(bizcocho(i+2,j), bizcocho(i, j-2), bizcocho(i+1,j-1))  e.o.c
	

coste O(n^2) en tiempo y en espacio	
*/
int bizcocho(vector<int> B){
	int n= B.size();
	Matriz<int> tabla(n, n, 0);

	for (int d = 2; d <= n-1; d++){
		for (int i = 1; i <= n-1-d; i++){
			int j = d + i;

			if (B[i]==B[j] && B[i]!=0){
				tabla[i][j] = tabla[i + 1][j - 1] + 1;
			}
			else{
				tabla[i][j] = max(tabla[i+2][j],max(tabla[i][j-2],tabla[i+1][j-1]));
			}
		}
	}

	return tabla[1][n-1];
}


bool resuelveCaso() {
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> v(N + 1,0);

	for (int i = 1; i <= N; i++){
		cin >> v[i];
	}

	cout << bizcocho(v) << "\n";
	
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos6A.txt");
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
