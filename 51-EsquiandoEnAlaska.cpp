//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

//coste n log n debido al sort para ordenar el vector, O(nlogn) donde n es el número de esquiadores y esquis
int sumaDiferencias(vector<int> &esquiadores, vector<int> &esquis){
	int suma = 0;

	sort(esquiadores.begin(), esquiadores.end());
	sort(esquis.begin(), esquis.end());

	for (int i = 0; i < esquiadores.size(); i++){
		suma += abs(esquiadores[i] - esquis[i]);
	}

	return suma;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;//numero de esquiadores y esquis a emparejar
	cin >> N;

	if (N==0)
		return false;

	vector<int> esquiadores(N);
	vector<int> esquis(N);
	int x;

	for (int i = 0; i < N; i++){
		cin >> esquiadores[i];
	}

	for (int j = 0; j < N; j++){
		cin >> esquis[j];
	}
	
	cout << sumaDiferencias(esquiadores, esquis) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos51.txt");
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
