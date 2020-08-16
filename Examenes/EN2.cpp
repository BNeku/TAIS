//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoDirigido.h"

using namespace std;

class Tareas{
public:
	Tareas(GrafoDirigido const &G) : marked(G.V(), false), visitado(G.V(), false){
		_imposible = false;

		for (int i = 0; i < G.V() && !_imposible; i++){
			if (!marked[i])
				dfs(G, i);
		}
	}


	void order(){
		for (int i = orden.size()-1; i >= 0; i--){
			cout << orden[i] + 1 << " ";
		}
		cout << "\n";
	}

	bool imposible(){
		return _imposible;
	}
private:
	vector<bool> marked;
	vector<bool> visitado;
	vector<int> orden;
	bool _imposible;
	bool ok;

	void dfs (GrafoDirigido const &g, int v){
		marked[v] = true;
		visitado[v] = true;

		_imposible = checkCycles(g, v);


		for (int w : g.ady(v)){
		
			if (visitado[w])
				_imposible = true;

			if (!_imposible && !marked[w]){
				dfs(g, w);
			}
				
		}
		visitado[v] = false;
		orden.push_back(v);
	}

	bool checkCycles(GrafoDirigido const&g, int v){

		for (int w : g.ady(v)){
			if (visitado[w])
				return true;
		}

		return false;
	}
	
};

bool resuelveCaso() {
	int N, M;
	
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoDirigido G(N);
	int a, b;

	for (int i = 0; i < M; i++){
		cin >> a >> b;
		G.ponArista(a - 1, b - 1);
	}

	Tareas grafo(G);
	if (grafo.imposible()){
		cout << "Imposible\n";
	}
	else{
		grafo.order();
	}
	
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casosEN2.txt");
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
