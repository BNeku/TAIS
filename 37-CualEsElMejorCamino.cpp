//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;

using namespace std;

class GrafoCiudad{
public:
	GrafoCiudad(GrafoDirigidoValorado<int> g, int origen, int destino) :marked(g.V(), false), distTo(g.V(), INFINITO), edgeTo(g.V()), distToDij(g.V(), make_pair(INFINITO, 0)), pq(g.V()) {
		_dest = destino;
		bfs(g, origen);
		Dijkstra(g, origen);
		if (marked[_dest])
			aristasDij();		
	}

	bool hayCamino()const{
		return marked[_dest];
	}
	
	bool iguales()const{
		//le sumo úno para que sea el numero de vertices (v=1+E)
		return distTo[_dest]==aristas;
	}

	int longitud(){
		return distToDij[_dest].first;
	}

private:
	//bfs
	vector<bool> marked;
	vector<int> distTo;
	int _dest;
	//Dijkstra
	vector<AristaDirigida<int>> edgeTo;
	int aristas;
	vector<pair<int,int>> distToDij;
	IndexPQ<pair<int, int>> pq;

	//coste O(E+V) donde E es el número de aristas del grafo g y v el número de vértices
	void bfs(GrafoDirigidoValorado<int> const&g, int s){
		queue<int> q;
		distTo[s] = 0;
		marked[s] = true;
		q.push(s);

		while (!q.empty()){
			int v = q.front(); q.pop();
			for (AristaDirigida<int> e : g.ady(v)){
				int w = e.to();
				if (!marked[w]){
					distTo[w] = distTo[v] + 1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}

	//Coste O(E * log V), O(N * log C) donde N es el número de intersecciones(vertices), y C el número de calles(aristas)
	void Dijkstra(GrafoDirigidoValorado<int> g, int s){
		distToDij[s] = { 0, 0 };
		pq.push(s, {0,0});

		while (!pq.empty()){
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int> e : g.ady(v)){
				relax(e);
			}
		}
	}

	void relax(AristaDirigida<int> e){
		int v = e.from(), w = e.to();
		if (distToDij[w].first > distToDij[v].first + e.valor()){
			distToDij[w].first = distToDij[v].first + e.valor();
			distToDij[w].second = distToDij[v].second + 1;
			edgeTo[w] = e;
			pq.update(w, distToDij[w]);
		}
		else if (distToDij[w].first == distToDij[v].first + e.valor() && distToDij[w].second > distToDij[v].second + 1){
			distToDij[w].second = distToDij[v].second+ 1;
			edgeTo[w] = e;
			pq.update(w, distToDij[w]);
		}
	}

	void aristasDij(){
		aristas=distToDij[_dest].second;
	}
};

bool resuelveCaso() {
	int N, C;

	cin >> N >> C;

	if (!std::cin)  // fin de la entrada
		return false;

	int c1, c2, longitud;
	GrafoDirigidoValorado<int> grafo(N);

	for (int i = 0; i < C; i++){
		cin >> c1 >> c2 >> longitud;
		c1--; c2--;
		grafo.ponArista({ c1, c2, longitud });
		grafo.ponArista({ c2, c1, longitud });
	}

	
	int consultas;
	cin >> consultas;

	for (int i = 0; i < consultas; i++){
		cin >> c1 >> c2;
		c1--; c2--;
		GrafoCiudad g(grafo, c1, c2);

		if (g.hayCamino()){
			if (g.iguales()){
			cout << g.longitud() << " SI\n";
			}else{
			cout << g.longitud() << " NO\n";
			}
			
		}
		else{
			cout << "SIN CAMINO\n";
		}
	}

	cout << "---\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos37.txt");
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
