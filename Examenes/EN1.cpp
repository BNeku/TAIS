
//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

using namespace std;

struct bateria{
	int id;
	int duracion;
	int tiempo;
};

bool operator < (bateria const&a, bateria const&b){
	if (a.tiempo < b.tiempo){
		return true;
	}
	else if (a.tiempo == b.tiempo){
		return a.id < b.id;
	}
	else{
		return false;
	}
}

void funcionamiento(PriorityQueue<bateria> &cola, vector<bateria> &repuesto, const int Z, const int T){
	bateria aux = cola.top();
	int nRepuesto = 0;

	for (int i = 1; i <= T && !cola.empty(); i++){
		
		while (aux.tiempo == i && !cola.empty()){
			cola.pop();
			aux.duracion -= Z;
			if (aux.duracion > 0){
				aux.tiempo = aux.duracion + i;
				cola.push(aux);
			}
			else{
				if (repuesto.size() > 0){
					aux = repuesto[nRepuesto];
					repuesto.pop_back();
					nRepuesto++;
					aux.tiempo = aux.duracion + i;
					cola.push(aux);
				}
			}

			if (cola.size()>0)
				aux = cola.top();
		}
	}

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int nBaterias, nRepuesto, Z, T;
	
	cin >> nBaterias;

	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<bateria> cola;
	bateria aux;

	for (int i = 0; i < nBaterias; i++){
		cin >> aux.duracion;
		aux.tiempo = aux.duracion;
		aux.id = i + 1;
		cola.push(aux);
	}

	cin >> nRepuesto;

	vector<bateria> repuesto;
	for (int i = 0; i < nRepuesto; i++){
		cin >> aux.duracion;
		aux.tiempo = aux.duracion;
		aux.id = nBaterias + i + 1;
		repuesto.push_back(aux);
	}
	cin >> Z >> T;

	funcionamiento(cola, repuesto, Z, T);

	int nCola = cola.size();

	if (nCola == 0){
		cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
	}
	else{
		if (nCola != nBaterias){
			cout << "FALLO EN EL SISTEMA\n";
		}
		else{
			cout << "CORRECTO\n";
		}

		for (int i = 0; i < nCola; i++){
			aux = cola.top(); cola.pop();
			cout << aux.id << " " << aux.tiempo << "\n";
		}	
	}

	cout << "---\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casosEN1.txt");
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
