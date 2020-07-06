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
		
		//no comprobamos si la rama esta vacia porque necesitamos que la propia recursion nos lo diga
		//los boleanos los utilizamos para saber cuando hemos llegado al final de la rama
		bool izquierda = esEquilibrado(arbol.left(), hIzq);
		bool derecha = esEquilibrado(arbol.right(), hDcha);
		
		h = 1+max(hDcha, hIzq);
		
		//solo queremos saber la diferencia de las ramas una vez hayamos explorado todo el arbol
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
	std::ifstream in("casos10.txt");
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
