//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct edificio{
	int ini;
	int fin;
};

bool operator < (edificio const &a1, edificio const &a2){
	return a1.fin < a2.fin;
}

//coste O(nlogn) donde n es el numero de edificios
int tuneles(PriorityQueue<edificio> &edificios){
	int tuneles = 1;
	int fin = edificios.top().fin;
	int n = edificios.size();
	edificios.pop();

	for (int i = 1; i < n; i++){
		if (edificios.top().ini >= fin){
			tuneles++;
			fin = edificios.top().fin;
		}
		edificios.pop();
	}


	return tuneles;
}


bool resuelveCaso() {
	int N;//numero edificios

	cin >> N;

	if (N==0)
		return false;
	int W, E;//extremo mas occidental(W) y el mas oriental(E)
	PriorityQueue<edificio> edificios;
	

	for (int i = 0; i < N; i++){
		cin >> W >> E;
		edificios.push({ W,E });
	}

	cout << tuneles(edificios) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos54.txt");
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

