//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "IndexPQ.h"

const int INFINITO = 1000000000;

using namespace std;

class GrafoIslas{
public:
	GrafoIslas(GrafoValorado<int> g, int nPuentes) :marked(g.V(), false), pq(g.V()), edgeTo(g.V()), distTo(g.V(), INFINITO){
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
	void visit(GrafoValorado<int> G, int v){
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
			_coste += edgeTo[i].valor();
		}
	}
};

bool resuelveCaso() {
	int I,P;

	cin >> I;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> P;
	int origen, destino, coste;
	GrafoValorado<int> g(I);

	for (int i = 0; i < P; i++){
		cin >> origen >> destino >> coste;
		origen--;
		destino--;
		g.ponArista({ origen, destino, coste});
	}

	//consultas


	GrafoIslas grafo(g, P);

	if (grafo.consulta()){
		cout << grafo.coste() << endl;
	}
	else{
		cout << "No hay puentes suficientes\n";
	}
	

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos36.txt");
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
