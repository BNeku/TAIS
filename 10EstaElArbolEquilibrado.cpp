// NEREA JIMENEZ GONZALEZ

#include <iostream>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"

using namespace std;

template <class T>
bool esEquilibrado(const bintree<T> &arbol, int &h){

	if (arbol.empty()){
		h = 0;
		return true;
	}
	else{
		int hDcha, hIzq;

		bool izquierda = esEquilibrado(arbol.left(), hIzq);
		bool derecha = esEquilibrado(arbol.right(), hDcha);
		
		h = 1+max(hDcha, hIzq);
		
		if (abs(hIzq - hDcha) <= 1 && izquierda && derecha){
			return true;
		}
		else{
			return false;
		}
	}
}


void resuelveCaso() {
	bintree<char> arbol = leerArbol('.');
	int h = 0;

	if (esEquilibrado(arbol, h)){
		cout << "SI" << endl;
	}else{
		cout << "NO" << endl;
	}

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos01.txt");
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
