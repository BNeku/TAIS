//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <queue>

using namespace std;

class GrafoCalle{
public:
	GrafoCalle(GrafoValorado<int> g, int origen, int destino, int anchuraMax):marked(g.V(), false){
		_anchuraMax = anchuraMax;
		bfs(g, origen);
		cabe = marked[destino];
	}

	bool consulta(){
		return cabe;
	}

private:
	bool cabe;
	vector<bool> marked;
	int _anchuraMax;

	//coste funcion O(V+E) donde V es el número de vértices y E el número de aristas
	void bfs(GrafoValorado<int> const &G, int s){
		queue<int> q;
		q.push(s);
		marked[s] = true;

		while (!q.empty()){
			int v = q.front(); q.pop();

			for (Arista<int> w : G.ady(v)){
				if (!marked[w.otro(v)] && w.valor() >= _anchuraMax){
					marked[w.otro(v)] = true;
					q.push(w.otro(v));
				}
			}
		}
	}
}; 

bool resuelveCaso() {
	int V, E;

	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> E;
	int origen, destino, anchura;
	GrafoValorado<int> g(V);

	for (int i = 0; i < E; i++){
		cin >> origen >> destino >> anchura;
		origen--;
		destino--;
		g.ponArista({ origen, destino, anchura});
	}

	//consultas
	int K;
	cin >> K;
	

	for (int j = 0; j < K; j++){
		cin >> origen >> destino >> anchura;
		origen--;
		destino--;
		GrafoCalle grafo(g, origen, destino, anchura);
		bool cabe = grafo.consulta();

		if (cabe){
			cout << "SI" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos35.txt");
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
