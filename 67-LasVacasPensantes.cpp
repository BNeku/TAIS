//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Matriz.h"

using namespace std;

/*
maxComida(i,j) = maximo de comida a comer del cubo i al cubo j

				
maxComida(i,j) = max(elegirDcha, elegirIzqda) //vemos las dos opciones para saber cual es mejor

elegirIzqda = maxComida(i+1,j-1)+comida[i] si comida[j] > comida[i+1]
			 maxComida(i+2,j)+comida[i] e.o.c

elegirDcha = maxComida(i+1,j-1)+comida[j] si comida[j-1] > comida[i]
			  maxComida(i,j-2)+comida[j] e.o.c

Casos Base:
maxComida(i,i) = comida[i] //si solo queda un cubo, elegimos ese si o si
maxComida(i, i+1) = max(comida[i],comida[i+1]) //si quedan dos cubos, elegimos el que más comida tenga

Coste O(N*N) tanto en espacio como en tiempo, siendo N el numero de cubos a elegir
*/
int maxComida(vector<int> &comida){
	int N = comida.size();
	Matriz<int> vacas(N, N, 0);

	//Casos Base
	for (int i = 1; i < N-1; i++) {
		vacas[i][i + 1] = max(comida[i], comida[i + 1]);
	}
	for (int i = 1; i < N; i++) {
		vacas[i][i] = comida[i];
	}

	//Recursion
	for (int d = 2; d < N - 1; d++){
		for (int i = 1; i < N - d; i++) {
			int j = i + d;

			int izq, dcha;

			//elegirDcha
			if (comida[j - 1] > comida[i])
				dcha = vacas[i][j - 2] + comida[j];
			else
				dcha = vacas[i + 1][j - 1] + comida[j];

			//elegirIzda

			if (comida[j] > comida[i + 1])
				izq = vacas[i + 1][j - 1] + comida[i];
			else
				izq = vacas[i + 2][j] + comida[i];

			vacas[i][j] = max(izq, dcha);
		}
	}
	return vacas[1][N-1];
}

bool resuelveCaso() {
	int N;

	cin >> N;

	if (N==0)  // fin de la entrada
		return false;

	vector<int> v(N+1,0);
	for (int i = 1; i <= N; i++){
		cin >> v[i];
	}

	cout << maxComida(v) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos67.txt");
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
