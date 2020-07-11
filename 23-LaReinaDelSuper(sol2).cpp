//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

struct caja{
	int numero;
	int tiempoOcupada;
};

bool operator < (caja const&a, caja const&b){
	if (a.tiempoOcupada < b.tiempoOcupada){
		return true;
	}
	else if (a.tiempoOcupada == b.tiempoOcupada){
		return a.numero < b.numero;
	}
	else{
		return false;
	}
}

int cajaIsmael(PriorityQueue<caja> &cola, int C){
	caja aux;
	int cajasLibres = cola.size();
	int t = 0;

	
	for (int i = 0; i < C;i++){
		if (cajasLibres > 0){
			aux = cola.top(); cola.pop();
			cin >> aux.tiempoOcupada;
			cola.push(aux);
			cajasLibres--;
		}
		else{
			//cuando ya no tenemos cajas libres, tenemos que tener en cuenta el tiempo que ha pasado en la otra caja
			//para ello lo que hacemos es ir acumulando el tiempo en las cajas
			aux = cola.top(); cola.pop();
			cin >> t;
			aux.tiempoOcupada += t;
			cola.push(aux);
		}
		t++;
	}

	return cola.top().numero;

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, C;
	//N numero de cajas abiertas, C numero de clientes esperando
	cin >> N >> C;

	if (N==0 && C==0)
		return false;

	PriorityQueue<caja> cola;
	caja aux;

	for (int i = 0; i < N; i++){
		aux.numero = i + 1;
		aux.tiempoOcupada = 0;
		cola.push(aux);
	}

	cout << cajaIsmael(cola, C) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos23.txt");
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
