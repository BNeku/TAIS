//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct registro {
	int momento; // cuándo le toca
	int id; // identificador (se utiliza en caso de empate)
	int periodo; // tiempo entre consultas
};

bool operator<(registro const& a, registro const& b) {
	return a.momento < b.momento ||
		(a.momento == b.momento && a.id < b.id);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;

	cin >> N; // número de usuarios registrados

	if (N == 0) // no hay más casos
		return false;

	PriorityQueue<registro> cola;

	// leemos los registros
	for (int i = 0; i < N; ++i) {
		int id_usu, periodo;
		cin >> id_usu >> periodo;
		cola.push({ periodo, id_usu, periodo });
	}

	int envios; // número de envíos a mostrar

	cin >> envios;

	while (envios--) {
		registro e = cola.top(); cola.pop();
		cout << e.id << '\n';
		e.momento += e.periodo;
		cola.push(e);
	}

	cout << "---" << endl;

	return true;
}



int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos21.txt");
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
