//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct actividades{
	int ini;
	int fin;
};

bool operator < (actividades const &a1, actividades const &a2){
	return a1.ini < a2.ini;
}
/*necesitamos dos colas de prioridades, una que esté ordenada con los eventos que comienzan antes, y otra donde se vayan guardando 
los finales donde haya ayudantes asistiendo*/
int ayudantes(PriorityQueue<actividades> &act){
	int ayud = 0;
	int N = act.size();

	actividades a = act.top();
	act.pop();
	PriorityQueue<int> finales;
	finales.push(a.fin);

	for (int i = 1; i < N; i++){
		a = act.top();
		act.pop();

		if (finales.top() > a.ini){
			ayud++;
			finales.push(a.fin);
		}
		else{
			finales.pop();
			finales.push(a.fin);
		}
	}

	return ayud;
}

/*
//otra version
int amigos(PriorityQueue<actividad> &horario){
	int numAmigos = 0;
	PriorityQueue<int> finActividades;
	finActividades.push(horario.top().fin);
	int N = horario.size() - 1;
	horario.pop();

	for (int i = 0; i < N; i++){
		if (finActividades.top() > horario.top().ini){
			numAmigos++;
		}
		else{
			finActividades.pop();
		}
		finActividades.push(horario.top().fin);
		horario.pop();
	}

	return numAmigos;
}

*/

bool resuelveCaso() {
	int nActividades;

	cin >> nActividades;

	if (nActividades==0)
		return false;

	int ini, fin;
	PriorityQueue<actividades> semana;

	for (int i = 0; i < nActividades; i++){
		cin >> ini >> fin;
		semana.push({ ini, fin });
	}

	cout << ayudantes(semana) << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos56.txt");
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
