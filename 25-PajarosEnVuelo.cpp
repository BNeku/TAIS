// NEREA JIMENEZ GONZALEZ

#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;

//Coste O(log numerosDePajarosTotal) (pajarosIzq.size() + pajarosDcha.size())
void enVuelo(PriorityQueue<int, greater<int>> &pajarosIzq, PriorityQueue<int> &pajarosDcha, int p1, int p2){
	int lider = pajarosDcha.top();
	int aux;

	if (p1 > lider && p2 > lider){
		pajarosDcha.push(p1);
		pajarosDcha.push(p2);

		pajarosDcha.pop(aux);
		pajarosIzq.push(aux);
	}
	else if (p1 < lider && p2 < lider){
		pajarosIzq.push(p1);
		pajarosIzq.push(p2);

		pajarosIzq.pop(aux);
		pajarosDcha.push(aux);
	}
	else if (p1<lider && p2>lider){
		pajarosIzq.push(p1);
		pajarosDcha.push(p2);
	}
	else{
		pajarosIzq.push(p2);
		pajarosDcha.push(p1);
	}
}

bool resuelveCaso() {
	int primer, parejas;

	cin >> primer >> parejas;

	if (primer == 0 && parejas == 0){
		return false;
	}

	PriorityQueue<int, greater<int>> pajarosIzq;
	PriorityQueue<int> pajarosDcha;
	pajarosDcha.push(primer);
	int p1, p2;
	vector<int> sol;

	for (int i = 0; i < parejas; i++){
		cin >> p1 >> p2;
		enVuelo(pajarosIzq, pajarosDcha, p1, p2);
		cout << pajarosDcha.top() << " ";
	}
	cout << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos25.txt");
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
