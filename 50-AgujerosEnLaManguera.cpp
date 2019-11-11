//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//coste lineal en el número de agujeros, O(n) donde n es el número de agujeros
int resolver(const vector<int> &v, const int &L){
	//estrategia: recorrer los agujeros de izqda a dcha colocando parches
	//colocamos un parche y nos movemos hasta el siguiente agujero no cubierto

	int inicio = v[0];//empieza en el primer agujero
	int nParches = 1;

	for (int i = 0; i < v.size(); i++){
		if (v[i] > inicio + L){
			nParches++;
			inicio = v[i];
		}
	}

	return nParches;
}

bool resuelveCaso() {
	int N;//numero de agujeros

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;
	int L;//longitud de los parches
	cin >> L;

	vector<int> v(N);//posiciones donde se encuentran los agujeros
	for (int i = 0; i < N; i++){
		cin >> v[i];
	}


	cout << resolver(v, L) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos50.txt");
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
