//Nerea Jiménez González
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"

using namespace std;


class NodoLejano{
public:
	NodoLejano(Grafo &g, int origen, int TTL) :marked(g.V(), false), distTo(g.V()){

		bfs(g, origen);//busqueda en anchura
		/*si se realiza la búsqueda en profundidad, el coste sería O(E*V), cuando se puede hacer más eficiente*/
		_inalcanzables = g.V();

		for (int i = 0; i < g.V(); i++){
			if (marked[i] && distTo[i] <= TTL)
				--_inalcanzables;
		}
	}
		
		
		int inalcanzables(){
			return _inalcanzables;
		}

private:
	vector<bool> marked;
	vector<int> distTo;
	int _inalcanzables;
	
	void bfs(Grafo const& G, int s){
		queue<int> q;
		distTo[s]=0;
		marked[s]=true;
		q.push(s);
		while(!q.empty()){
			int v=q.front(); q.pop();

			for(int w: G.ady(v)){
				if(!marked[w]){
					distTo[w] = distTo[v]+1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}
	
	
};

bool resuelveCaso() {
	int N, C, K;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> C;

	Grafo g(N);
	int a1, a2;
	for (int i = 0; i < C; i++){
		cin >> a1 >> a2;
		g.ponArista(a1-1, a2-1);
	}

	cin >> K;
	int origen, TTL;

	for (int i = 0; i < K; i++){
		cin >> origen >> TTL;

		NodoLejano grafo(g, origen-1, TTL);

		cout << grafo.inalcanzables() << endl;
	}

	cout << "---" << endl;
	
	
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos3A.txt");
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
