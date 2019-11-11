
//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

const int INFINITO = 1000000000;

class GrafoPavimentar{
public:
	GrafoPavimentar(GrafoValorado<int> g) :marked(g.V(), false), pq(g.V()), edgeTo(g.V()), distTo(g.V(), INFINITO){
		llega = true;
		_coste = 0;
		Prim(g);
		llegaATodas();

		if (llega)
			costeTotal();
	}

	bool consulta(){
		return llega;
	}

	int coste(){
		return _coste;
	}

private:
	vector<bool> marked;
	vector<Arista<int>> edgeTo;
	vector<int> distTo;
	IndexPQ<int> pq;
	bool llega;
	int _coste;

	//coste O(P* log I) donde P es el número de puentes e I el número de islas
	void Prim(GrafoValorado<int> const & G){
		pq.push(0, 0);

		while (!pq.empty()){
			int min = pq.top().elem; pq.pop();
			visit(G, min);
		}
	}

	//coste O(log I)
	void visit(const GrafoValorado<int> &G, int v){
		marked[v] = true;

		for (Arista<int> e : G.ady(v)){

			int w = e.otro(v);

			if (marked[w])continue;
			if (e.valor() < distTo[w]){
				edgeTo[w] = e;
				distTo[w] = e.valor();
				pq.update(w, distTo[w]);
			}
		}
	}

	void llegaATodas(){
		for (int i = 0; i < marked.size() && llega; i++){
			if (!marked[i])
				llega = false;
		}
	}

	void costeTotal(){

		for (int i = 1; i < edgeTo.size(); i++){
			_coste += distTo[i];
		}
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int V, E;

	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;
	cin >> E;
	GrafoValorado<int> G(V);
	int a1, a2, v;

	for (int i = 0; i < E; i++){
		cin >> a1 >> a2 >> v;
		G.ponArista({a1-1,a2-1,v});
	}

	GrafoPavimentar grafo(G);

	if (grafo.consulta()){
		cout << grafo.coste() << "\n";
	}
	else{
		cout << "Imposible\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos3D.txt");
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
