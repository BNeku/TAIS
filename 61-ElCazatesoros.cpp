//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"

using namespace std;

struct cofre{
	int profundidad;
	int monedas;
};

/*
	eligeCofres(i, T) = número máximo de oro que se puede coger en T tiempo escogiendo algunos cofres del 1 al i

	profundidad[i] = profundidad a la que esta el cofre i (cofre[i].profundidad)
		eligeCofres(i,T) = eligeCofres(i-1, T) si profundidad[i] + 2*profundidad[i] > T
	es decir, si el tiempo de buceo hasta el cofre y de vuelta la superficie, es mayor que el tiempo que tenemos en la botella, 
	ese cofre no lo elegimos
		eligeCofres(i,T) = max(eligeCofres(i-1, T-profundidad[i] + 2*profundidad[i])+ monedas[i], eligeCofres(i-1, T))  si profundidad[i] + 2*profundidad[i]<=T
	 casos base:
	 eligeCofres(i, 0) = 0
	 eligeCofres(0, T) = 0
	*/
void eligeCofres(const vector<cofre> &v, const int &T, vector<bool> &elegidos, int &nCofres, int &totalMonedas){
	int n = v.size() - 1;
	Matriz<int> cofre(n + 1, T + 1);

	cofre[0][0] = 0;
	for (int i = 1; i <= n; i++){
		cofre[i][0] = 0;
		for (int j = 1; j <= T; j++){
			cofre[0][j] = 0;

			if (v[i].profundidad + (2 * v[i].profundidad) > j){
				cofre[i][j] = cofre[i - 1][j];
			}
			else{
				cofre[i][j] = max(cofre[i - 1][j], cofre[i - 1][j - (v[i].profundidad + (2 * v[i].profundidad))]+v[i].monedas);
			}
		}
	}

	totalMonedas = cofre[n][T];

	//recorremos la matriz para saber qué cofres hemos seleccionado
	int tiempo = T;

	for (int i = n; i >= 1; i--){
		if (cofre[i][tiempo] == cofre[i - 1][tiempo]){
			elegidos[i] = false;
		}
		else{
			elegidos[i] = true;
			tiempo -= v[i].profundidad + (2 * v[i].profundidad);
			nCofres++;
		}
	}
}

bool resuelveCaso() {
	int T, N;

	cin >> T;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> N;
	int p, m;
	vector<cofre> v(N+1);
	vector<bool> elegidos(N + 1);
	int nCofres = 0;
	int totalOro = 0;

	for (int i = 1; i <= N; i++){
		cin >> p >> m;
		v[i] = { p, m };
	}
	
	eligeCofres(v, T, elegidos, nCofres, totalOro);

	cout << totalOro << "\n" << nCofres << "\n";

	if (nCofres > 0){
		for (int i = 1; i <= N; i++){
			if (elegidos[i]){
				cout << v[i].profundidad << " " << v[i].monedas << "\n";
			}
		}
	}
	

	cout << "---\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos61.txt");
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
