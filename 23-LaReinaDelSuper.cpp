//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct cliente{
	int numCaja;
	int segundos;
};

bool operator <(cliente const&a, cliente const&b){

	if (a.segundos < b.segundos){
		return true;
	}
	else if (a.segundos == b.segundos){
		if (a.numCaja < b.numCaja)
			return true;
	}

	return false;
}

//Coste: (cajasAbiertas log(clientesEsperando))
bool resuelveCaso() {

	long long int cajasAbiertas=0, clientesEsperando=0;

	cin >> cajasAbiertas >> clientesEsperando;

	if (cajasAbiertas==0 && clientesEsperando==0)
		return false;

	PriorityQueue<cliente> fila;
	cliente c;
	int t, cajaLibre=1, tiempo=0;

	while (clientesEsperando > 0){
		cin >> t;
		c.segundos = t+tiempo;

		if (cajasAbiertas > 0){
			c.numCaja = cajaLibre;
			fila.push(c);
			cajaLibre++;
			cajasAbiertas--;
		}

		if (cajasAbiertas == 0){
			cajaLibre = fila.top().numCaja;
			tiempo = fila.top().segundos;
			fila.pop();
			cajasAbiertas++;
		}

		clientesEsperando--;
	}

	cout << cajaLibre << endl;

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
