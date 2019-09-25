//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

struct paciente{
	string nombre;
	long long int estado;
	int espera;
};

bool operator<(paciente const& a, paciente const& b) {
	if (a.estado > b.estado){
		return true;
	}
	else if (a.estado == b.estado){
		if (a.espera < b.espera){
			return true;
		}
	}

	return false;
}

bool resuelveCaso() {

	int eventos = 0;

	cin >> eventos;

	if (eventos==0)
		return false;

	char tipo;
	PriorityQueue<paciente> consulta;
	paciente atendido;
	string nomb;
	long long int est;

	for (int i = 0; i < eventos; i++){
		cin >> tipo;

		if (tipo == 'I'){
			cin >> nomb >> est;
			consulta.push({nomb,est,i});
		}
		else{
			atendido = consulta.top();
			consulta.pop();
			cout << atendido.nombre << endl;
		}
	}

	cout << "---" << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos22.txt");
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
