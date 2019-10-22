
//Nerea Jiménez González

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

class Noticias{
public:
	Noticias(Grafo const &g) :marked(g.V(), false), componentes(g.V(), nComp=0){

		for (int i = 0; i < g.V(); i++){
			if (!marked[i]){
				marked[i] = true;
				tamanio.push_back(conectados(g, i));
				nComp++;
			}
		}
	}

	int numConectados(int n){
		return tamanio[componentes[n]];
	}

private:
	vector<bool> marked;
	vector<int> componentes;
	vector<int> tamanio;
	int nComp;

	int conectados(Grafo const &g, int num){
		int f = 1;

		if (g.ady(num).size() != 0){
			componentes[num] = nComp;
			for (int i = 0; i < g.ady(num).size(); i++){
				if (!marked[g.ady(num)[i]]){
					marked[g.ady(num)[i]] = true;
					componentes[g.ady(num)[i]] = nComp;
					f += conectados(g, g.ady(num)[i]);
				}
			}
		}
		else{
			componentes[num] = nComp;
		}
		

		return f;
	}

};



bool resuelveCaso() {
	int V, M;

	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;
	
	Grafo g(V);
	int nUser, a1, a2;

	cin >> M;

	for (int i = 0; i < M; i++){
		cin >> nUser;
		if (nUser > 0){
			cin >> a1;
			for (int j = 1; j < nUser; j++){
				cin >> a2;
				g.ponArista(a1-1,a2-1);
				a1 = a2;
			}
		}	
	}

	Noticias grafo(g);

	for (int i = 0; i < V; i++){
		cout << grafo.numConectados(i)<< " ";
	}

	cout << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos32.txt");
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
