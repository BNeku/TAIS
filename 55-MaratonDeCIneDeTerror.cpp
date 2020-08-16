//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct horas{
	int hora;
	int min;
};

struct pelicula{
	horas comienzo;
	horas fin;
};

bool operator < (horas const& a, horas const& b){
	if (a.hora == b.hora){
		return a.min < b.min;
	}
	else{
		return a.hora < b.hora;
	}
}

bool operator <= (horas const& a, horas const& b){
	if (a.hora == b.hora){
		if (a.min == b.min){
			return true;
		}
		else{
			return a.min < b.min;
		}
	}
	else{
		return a.hora < b.hora;
	}
}

//ORDENAMOS POR EL FIN PORQUE SI QUEREMOS EMPEZAR POR LA PELICULA QUE ACABE ANTES
bool operator < (pelicula const& a, pelicula const&b){
	return a.fin < b.fin;
}

int numMax(PriorityQueue<pelicula> &maraton){
	int nM = 1, n=maraton.size()-1;
	horas fin = maraton.top().fin;
	maraton.pop();

	for (int i = 0; i < n; i++){
		if (fin <= maraton.top().comienzo){
			nM++;
			fin = maraton.top().fin;
		}

		maraton.pop();
	}
	
	return nM;
}

void sumaHoras(horas &h, int min){
	h.min +=  min;

	while (h.min>= 60){
		h.hora++;
		h.min -= 60;
	}

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int nPeliculas;

	cin >> nPeliculas;

	if (nPeliculas == 0)
		return false;

	horas h;
	pelicula aux;
	char basura;
	int tiempo;
	PriorityQueue<pelicula> maraton;

	for (int i = 0; i < nPeliculas; i++){
		cin >> h.hora >> basura >> h.min >> tiempo;
		aux.comienzo = h;
		sumaHoras(h, tiempo + 10);
		aux.fin = h;
		maraton.push(aux);
	}

	cout << numMax(maraton) << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos55.txt");
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
