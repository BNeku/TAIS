//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

using namespace std;

const int INFINITO = 1000000000;

class Laberinto{
public:
	int _ratones;

	Laberinto(GrafoDirigidoValorado<int> G, int S, int T):edgeTo(G.V()),distTo(G.V(),INFINITO), pq(G.V()){
		t = T; s = S;
		distTo[s] = 0;
		pq.push(s, 0);
		numRat = 0;

		Dijkstra(G);
		llegan();
	}

	int ratones(){
		return numRat;
	}

private:
	int t, s;
	vector<AristaDirigida<int>> edgeTo;
	vector<int> distTo;
	IndexPQ<int> pq;
	int numRat;
	

	void Dijkstra(GrafoDirigidoValorado<int> &G){

		while (!pq.empty()){
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int> e : G.ady(v)){
				relax(e);
			}
		}
	}

	void relax(AristaDirigida<int> &e){
		int v = e.from(), w = e.to();

		if (distTo[w] > distTo[v] + e.valor()){
			distTo[w] = distTo[v] + e.valor();
			edgeTo[w] = e;
			pq.update(w, distTo[w]);
		}
	}

	void llegan(){

		for (int i = 0; i < distTo.size(); i++){
			if (i != s && distTo[i] <= t){
				numRat++;
			}
		}
	}
};

bool resuelveCaso() {
	int N, S, T, P;

	cin >> N >> S >> T >> P;

	if (!std::cin)  // fin de la entrada
		return false;
	GrafoDirigidoValorado<int> G(N);
	int A, B, V;

	for (int i = 0; i < P; i++){
		cin >> A >> B >> V;
		G.ponArista({ B-1, A-1, V });
	}

	Laberinto L(G,S-1,T);

	cout << L.ratones() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
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