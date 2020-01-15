//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"
#include <algorithm>

using namespace std;

struct trabajos{
	int c;
	int f;
};



bool operator <(const trabajos &t1, const trabajos &t2){
	return t1.c < t2.c;
}

int cubre(vector<trabajos> &cola, int C, int F){
	int numTrabajos = 0;
	int izq = C, dcha = C;
	bool hay = false, imposible=false;

	sort(cola.begin(), cola.end());

	for (int i = 0; i < cola.size() && dcha < F && !imposible; i++){
		if (cola[i].c <= izq){
			if (cola[i].f > dcha){
				dcha = cola[i].f;
				hay = true;
				//no sumamos hasta que encontremos el trabajo que cubre más
			}
		}
		else{
			if (hay){
				numTrabajos++;
				hay = false;
				izq = dcha;//buscamos el siguiente
				i--;
			}
			else{
				//si no hay, es imposible
				imposible = true;
				numTrabajos = -1;
			}
		}
	}
	if (hay)
		numTrabajos++;
	if (dcha < F)
		numTrabajos = -1;

	return numTrabajos;
}

bool resuelveCaso() {
	int C, F, N;

	cin >> C >> F >> N;

	if (C == 0 && F == 0 && N == 0)
		return false;
	//lectura
	vector<trabajos> cola(N);
	for (int i = 0; i < N; i++){
		cin >> cola[i].c >> cola[i].f;
	}
	int sol = cubre(cola, C, F);
	if (sol == -1){
		cout << "Imposible\n";
	}
	else{
		cout << sol << "\n";
	}
	

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos57.txt");
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
