//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

using namespace std;


void tiempoVuelo(PriorityQueue<int, greater<int>> &caja9, PriorityQueue<int, greater<int>> &caja15, const int N){

	int pila9, pila15, t=0;

	while (!caja9.empty() && !caja15.empty()){
		vector<int> pilasUsadas9, pilasUsadas15;//necesitamos usar otras cajas para guardar las pilas usadas, ya que si no podriamos elegir una pila que esta en otro dron
		
		for (int i = 0; i < N && !caja9.empty() && !caja15.empty(); i++){
			pila9 = caja9.top(); caja9.pop();
			pila15 = caja15.top(); caja15.pop();

			if (pila9 < pila15){
				t += pila9;
				pila15 -= pila9;
				pilasUsadas15.push_back(pila15);
				
			}
			else{
				t += pila15;
				pila9 -= pila15;
				if (pila9 != 0)
					pilasUsadas9.push_back(pila9);
					
			}

		}
		
		for (int i = 0; i < pilasUsadas15.size(); i++){
			caja15.push(pilasUsadas15[i]);
		}
		for (int i = 0; i < pilasUsadas9.size(); i++){
			caja9.push(pilasUsadas9[i]);
		}

		cout << t << " ";
		t = 0;

	}
	cout << "\n";
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, A, B;
	//N es el numero de drones, A numero de pilas de 9V y B numero de pilas de 1,5V

	cin >> N >> A >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<int, greater<int>> caja9, caja15;
	int pila;

	for (int i = 0; i < A; i++){
		cin >> pila;
		caja9.push(pila);
	}
	for (int j= 0; j < B; j++){
		cin >> pila;
		caja15.push(pila);
	}

	tiempoVuelo(caja9, caja15, N);

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