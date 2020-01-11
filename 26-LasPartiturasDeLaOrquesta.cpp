//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

struct Atril{
	int numMusicos;
	int partituras;
};

bool operator >(Atril const &a1, Atril const &a2){
	int grupos1 = a1.numMusicos / a1.partituras;
	int grupos2 = a2.numMusicos / a2.partituras;

	if (a1.numMusicos % a1.partituras != 0)
		grupos1++;
	if (a2.numMusicos % a2.partituras != 0)
		grupos2++;

	return grupos1 > grupos2;
}

//queremos minimizar el atril con más musicos
//repartimos partituras a los musicos, no agrupamos a los musicos según partituras!
//Coste O(p * log n) donde p es el numero de partituras a repartir y n el número de grupos de musicos
bool resuelveCaso() {
	int n, p;

	cin >> p >> n;

	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<Atril, greater<Atril>> musicos;
	int m;

	for (int i = 0; i < n; i++){
		cin >> m;
		//todos los grupos empiezan con una partitura
		musicos.push({m,1});
	}
	p-= n;

	//mientras queden partituras
	Atril a;
	while (p > 0){
		musicos.pop(a);
		a.partituras++;
		p--;
		musicos.push(a);
	}

	a = musicos.top();
	int sol = a.numMusicos / a.partituras;
	if (a.numMusicos%a.partituras != 0)
		sol++;

	cout << sol << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos26.txt");
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
