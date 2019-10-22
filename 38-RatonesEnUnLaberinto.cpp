//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

const int INFINITO = 1000000000;

/*
int llegan(const GrafoDirigidoValorado<int> &g, int S, int T, vector<bool> &marked){
	int ratones = 0;

	for (int i = 0; i < g.ady(S).size() && T>0; i++){
		AristaDirigida<int> a = g.ady(S)[i];
		
		if (T - a.valor() >= 0 && !marked[a.to()]){
			ratones++;
			marked[a.to()] = true;
			ratones += llegan(g, a.to(), T - a.valor(), marked);
		}

	}

	return ratones;
}*/

void relajar(AristaDirigida<int>& a, vector<AristaDirigida<int>>& aristas, IndexPQ<int>& pq, vector<int>&dist) {
	int v = a.from(), w = a.to();

	if (dist[w] > dist[v] + a.valor()) {
		dist[w] = dist[v] + a.valor();
		aristas[w] = a;
		pq.update(w, dist[w]);
	}
}

int llegan(const GrafoDirigidoValorado<int> &g, int& S, int& T){
	vector<int> distancias(g.V(), INFINITO);
	vector<AristaDirigida<int>> aristas(g.V());
	IndexPQ<int> pq(g.V());
	int ratones = 0;
	
	distancias[S-1] = 0;
	pq.push(S-1, 0);
	
	 while(!pq.empty()){
		 int v = pq.top().elem;
		 pq.pop();
		 for (AristaDirigida<int> a : g.ady(v)){
			 relajar(a, aristas, pq, distancias);
		 }
	}

	 for (int i = 0; i < distancias.size(); i++){
		 if (i != S-1 && distancias[i] <= T)
			 ratones++;
	 }

	return ratones;
}

bool resuelveCaso() {
	int Nceldas, SnumCelda,Tseg,Pasadizos;

	cin >> Nceldas;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> SnumCelda >> Tseg >> Pasadizos;

	int o, d, v;
	GrafoDirigidoValorado<int> grafo(Nceldas);
	vector<bool> marked(Nceldas);
	

	for (int i = 0 ; i < Pasadizos; i++){
		cin >> o >> d >> v;
		AristaDirigida<int> arista(d-1,o-1,v);
		grafo.ponArista(arista);
	}

	//cout << llegan(grafo, SnumCelda-1, Tseg, marked) << endl;
	cout << llegan(grafo, SnumCelda, Tseg) << endl;;


	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos38.txt");
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
