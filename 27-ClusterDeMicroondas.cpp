//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

struct Persona{
	int llega;
	int tarda;
};

using namespace std;

//coste O(cola.size()) donde este es el numero de personas esperando en la cola
//simulacion para ver si con numMicro microondas, todas las personas calientan su comida sin esperar más del tiempo máximo
bool prueba(const int &numMicro, const int &maxT, vector<Persona> cola){
	bool vale = true;
	PriorityQueue<int> micros;
	int m;
	Persona x;

	//rellenamos la cola con tantos 0 como microondas tenemos
	for (int i = 0; i < numMicro; i++){
		micros.push(0);
	}

	for (int i = 0; i < cola.size() && vale; i++){//la prueba la haremos con todas las personas o hasta que falle la prueba(vale=false)
		x = cola[i];//sacamos la primera persona que esta esperando en la cola
		micros.pop(m);//primer micro libre

		//momentos donde el microondas ha quedado libre(m) - cuando llega la persona
		if (m - x.llega > maxT){//si supera el tiempo maximo, no pasa la prueba
			vale = false;
		}
		else if(m < x.llega){//si el momento donde llega la persona es mayor que el primer microondas libre
			m = x.llega + x.tarda;//este microondas estará ocupado desde que la persona llega y lo que tarde en utilizarlo
		}
		else{//en otro caso
			m += x.tarda;//el microondas estará ocupado desde el mismo momento que está libre hasta el momento que tarde la persona x en utilizarlo
		}

		micros.push(m);//metemos este nuevo fin de tiempo del microondas en la cola de prioridad
	}

	return vale;
}

bool resuelveCaso() {
	int n, t;
	
	cin >> n >> t;

	if (n==0 && t==0)
		return false;
	
	int x, y;

	vector<Persona> cola(n);

	for (int i = 0; i < n; i++){
		cin >> x >> y;
		cola[i]={ x, y };
	}

	// búsqueda binaria
	int ini = 1, fin = 50001;
	while (ini < fin) {
		int med = (ini + fin) / 2;
		if (prueba(med,t,cola))
			fin = med;
		else
			ini = med + 1;
	}

	cout << fin << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos27.txt");
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
