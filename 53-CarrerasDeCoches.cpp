// NEREA JIMENEZ GONZALEZ

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

//coste del algoritmo es el coste de sort, que es nlogn donde n es el número de pilas disponibles
int numCochesFuncionando(vector<int> &pilas, const int &V){
	int nCoches = 0;
	int j = pilas.size() - 1;
	int i = 0;
	sort(pilas.begin(), pilas.end(), greater<int>());

	while ( i < j){
		if (pilas[i] + pilas[j] >= V){
			i++;
			j--;
			nCoches++;
		}
		else{
			j--;
		}
	}

	return nCoches;
}


void resuelveCaso() {
	int N;//numero de pilas
	int V;//voltaje minimo para que funcionen los coches

	cin >> N >> V;

	vector<int> pilas;
	int p;

	for (int i = 0; i < N; i++){
		cin >> p;
		pilas.push_back(p);
	}

	cout << numCochesFuncionando(pilas, V) << "\n";

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos53.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
