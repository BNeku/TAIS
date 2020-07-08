//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

//SI CAMBIAMOS LOS INT POR LONG LONG INT, NO OLVIDAR CAMBIAR TAMBIEN EL TIPO DE LA FUNCION A LONG LONG
long long int minEsfuerzo(PriorityQueue<long long int> &suma){
	long long int esfuerzo=0;

	long long int num1, num2;

	if (suma.size() == 1){
		return 0;
	}

	while (suma.size() > 1){
		suma.pop(num1);
		suma.pop(num2);

		num1 += num2;
		esfuerzo += num1;
		suma.push(num1);
	}

	return esfuerzo;
}

bool resuelveCaso() {
	int N = 0;

	cin >> N;

	if (N==0)
		return false;

	long long int aux;
	PriorityQueue<long long int> suma;

	for (int i = 0; i < N; i++){
		cin >> aux;
		suma.push(aux);
	}

	cout << minEsfuerzo(suma) << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos20.txt");
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
