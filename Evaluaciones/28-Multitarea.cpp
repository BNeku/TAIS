//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct Tarea{
	int ini;
	int fin;
	int repet;
};

bool operator <(Tarea const &a, Tarea const &b){
	return a.ini < b.ini;
}

bool resolver(PriorityQueue<Tarea> tareas, int T){
	bool solapa = false;
	int ocupado = 0;

	while (!solapa && !tareas.empty() && tareas.top().ini < T ){
		Tarea auxT = tareas.top();
		tareas.pop();

		if (auxT.ini< ocupado){
			solapa = true;
		}
		ocupado = auxT.fin; 
		if (auxT.repet > 0){
			tareas.push({auxT.ini+auxT.repet, auxT.fin+ auxT.repet, auxT.repet});
		}
	}

	return solapa;
}

bool resuelveCaso() {
	int N, M, T;

	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	cin >> M >> T;
	int ini, f, r;
	PriorityQueue<Tarea> tareas;

	for (int i = 0; i < N; i++){
		cin >> ini >> f;
		tareas.push({ ini, f, 0 });
	}

	for (int j = 0; j < M; j++){
		cin >> ini >> f >> r;
		tareas.push({ ini, f, r });
	}

	if (T!=0 && resolver(tareas, T)){
		cout << "SI" << endl;
	}
	else{
		cout << "NO" << endl;
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos28.txt");
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
