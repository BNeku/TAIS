//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 100000000;

using namespace std;

class paginas{
public:
	paginas(GrafoDirigidoValorado<int> const &G, vector<int> tiempoCarga): edgeTo(G.V()), distTo(G.V(), INFINITO), pq(G.V()){
		_llega = true;
		_tiempo = 0;
		_tiempoCarga = tiempoCarga;
		Dijkstra(G);
		llegaATodos(G.V() - 1);
	}

	bool consulta(){
		return _llega;
	}

	int tiempoTotal(){
		return _tiempo;
	}


private:
	vector<AristaDirigida<int>> edgeTo;
	vector<int> distTo;
	IndexPQ<int> pq;
	vector<int> _tiempoCarga;
	int _tiempo;
	bool _llega;

	void Dijkstra(GrafoDirigidoValorado<int> const &G){
		distTo[0] = 0;
		pq.push(0, 0);

		while (!pq.empty()){
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int> e : G.ady(v)){
				relax(e);

			}
		}
	}

	void relax(AristaDirigida<int> e){
		int v = e.from(), w = e.to();

		if (distTo[w] > distTo[v] + e.valor()){
			distTo[w] = distTo[v] + e.valor();
			edgeTo[w] = e;
			pq.update(w, distTo[w]);
		}
	}

	void llegaATodos(int ultimo){

		if (distTo[ultimo] == INFINITO){
			_llega = false;
		}
		else{
			_tiempo = distTo[ultimo] + _tiempoCarga[0];
		}
	}


};

bool resuelveCaso() {
	int N;//numero de paginas manejadas

	cin >> N;

	if (N==0)
		return false;

	vector<int> tiempoCarga(N);
	int t;

	for (int i = 0; i < N; i++){
		cin >> tiempoCarga[i];
	}

	int M;//numero de enlaces entre paginas
	int pOrigen, pDestino, tCarga;
	GrafoDirigidoValorado<int> g(N);

	cin >> M;

	for (int j = 0; j < M; j++){
		cin >> pOrigen >> pDestino >> tCarga;
		g.ponArista({ pOrigen-1, pDestino-1, tCarga+tiempoCarga[pDestino-1]});
	}

	paginas web(g, tiempoCarga);

	if (web.consulta()){
		cout << web.tiempoTotal() << "\n";
	}
	else{
		cout << "IMPOSIBLE\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos3C.txt");
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
