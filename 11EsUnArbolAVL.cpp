
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

		h = 1 + max(hDcha, hIzq);

		if (abs(hIzq - hDcha) <= 1 && izquierda && derecha){
			return true;
		}
		else{
			return false;
		}
	}
}

template <class T>
bool esAVL(const bintree<T> &arbol, bool &AVL, int &min, int &maxim){

	if (!arbol.empty() && AVL){
		if (arbol.right().empty() && arbol.left().empty()){
			min = arbol.root();
			maxim = arbol.root();
		}
		else{
			int aux = -1;

			if (!arbol.left().empty()){
				esAVL(arbol.left(), AVL, min, maxim);

				if (maxim >= arbol.root()){
					AVL = false;
				}
				else{
					maxim = arbol.root();
				}
				aux = min;
			}
			
			if (!arbol.right().empty()){
				esAVL(arbol.right(), AVL, min, maxim);

				if (min <= arbol.root()){
					AVL = false;
				}
				else if (aux != -1){
					min = aux;
				}
				else{
					min = arbol.root();
				}
			}
		}
	}

return AVL;
}

void resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	int h = 0, min = 1000000, max = 0;
	bool avl = true;

	if (esEquilibrado(arbol, h) && esAVL(arbol, avl,min,max)){
		cout << "SI" << endl;
	}
	else{
		cout << "NO" << endl;
	}

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos11.txt");
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