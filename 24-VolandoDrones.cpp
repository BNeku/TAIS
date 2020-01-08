//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include <vector>
#include <algorithm>

using namespace std;



vector<int> volar(int nDrones, PriorityQueue<int, greater<int>> &caja15, PriorityQueue<int, greater<int>> &caja9){
	vector<int> drones;

	//hasta que una de las cajas este vacia
	while (!caja15.empty() && !caja9.empty()){
		//cada sabado
		int i = 0;
		vector<int> pilas9Restantes;
		vector<int> pilas15Restantes;
		int horas = 0;

		while (!caja15.empty() && !caja9.empty() && i < nDrones){
			//ponemos las pilas en los drones si hay pilas en ambas cajas
			int p15 = caja15.top();
			caja15.pop();
			int p9 = caja9.top();
			caja9.pop();

			if (p9 > p15){
				pilas9Restantes.push_back(p9 - p15);
			}
			else if (p15>p9){
				pilas15Restantes.push_back(p15 - p9);
			}

			horas += min(p9, p15);
			i++;
		}

		drones.push_back(horas);

		for (int i = 0; i < pilas15Restantes.size(); i++){
			caja15.push(pilas15Restantes[i]);
		}

		for (int i = 0; i < pilas9Restantes.size(); i++){
			caja9.push(pilas9Restantes[i]);
		}
	}

	return drones;
}

bool resuelveCaso() {

	int dronesDisponibles;

	cin >> dronesDisponibles;

	if (!std::cin)  // fin de la entrada
		return false;

	int pilas9, pilas15;

	cin >> pilas9 >> pilas15;

	PriorityQueue<int, greater<int>> caja9;
	PriorityQueue<int, greater<int>> caja15; //colas de prioridad de las cajas de las pilas
	int duracion;

	for (int i = 0; i < pilas9; i++){
		cin >> duracion;
		caja9.push(duracion);
	}
	for (int j = 0; j < pilas15; j++){
		cin >> duracion;
		caja15.push(duracion);
	}

	vector<int> drones = volar(dronesDisponibles, caja15, caja9);

	for (int i = 0; i < drones.size(); i++){
		cout << drones[i] << " ";
	}
	cout << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos24.txt");
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