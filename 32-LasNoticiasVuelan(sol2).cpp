//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

class Amigos{
public:
	Amigos(Grafo const& G):marked(G.V(),false), amigos(G.V(),1), contados(G.V(), false){

		for (int i = 0; i < G.V(); i++){
			if (!marked[i]){
				_amigos = 1;
				dfs(G, i);
				marcar();
			}
		}
	}

	vector<int> numAmigos(){
		return amigos;
	}

private:
	vector<bool> marked;
	vector<bool> contados;
	vector<int> amigos;
	int _amigos;

	void dfs(Grafo const& G, int v){
		marked[v] = true;

		for (int w : G.ady(v)){
			if (!marked[w]){
				_amigos++;
				dfs(G, w);
			}	
		}
	}

	void marcar(){
		for (int i = 0; i < marked.size(); i++){
			if (marked[i] && !contados[i]){
				amigos[i] = _amigos;
				contados[i] = true;
			}
		}
	}
};

bool resuelveCaso() {
	int N, M;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> M;
	int nUsuarios;
	Grafo g(N);
	int a,b;

	for (int i = 0; i < M; i++){
		cin >> nUsuarios;

		if (nUsuarios > 0){
			cin >> a;

			for (int j = 1; j < nUsuarios; j++){
				cin >> b;
				g.ponArista(a - 1, b - 1);
				a = b;
			}
		}
		
	}

	Amigos grafo(g);

	for (int w : grafo.numAmigos()){
		cout << w << " ";
	}
	cout << "\n";

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
