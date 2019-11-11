//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

//coste nlog n, ya que es el coste del sort y es el coste más alto, O(nlogn) donde n es el número de partidos adivinados
int maximizar(vector<int> &rivales, vector<int> &boston){
	int exito = 0;
	bool pierden = false;

	sort(rivales.begin(), rivales.end());
	sort(boston.begin(), boston.end(), greater<int>());

	for (int i = 0; i < rivales.size() && !pierden; i++){
		if (boston[i] > rivales[i]){
			exito += boston[i] - rivales[i];
		}
		else{
			pierden = true;
		}
	}

	return exito;
}

bool resuelveCaso() {
	int n;//numero de puntos

	cin >> n;

	if (n==0)
		return false;

	vector<int> boston, rivales;
	int x;

	for (int i = 0; i < n; i++){
		cin >> x;
		rivales.push_back(x);
	}

	for (int j = 0; j < n; j++){
		cin >> x;
		boston.push_back(x);
	}

	cout << maximizar(rivales, boston) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos52.txt");
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
