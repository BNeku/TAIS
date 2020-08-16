
//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Grafo.h"

using namespace std;

class Bipartito{
public:
	Bipartito(Grafo const& G):_marked(G.V(),false), _color(G.V()), _bipartito(true){
		
		for (int i = 0; i < G.V() && _bipartito; i++){
			
			if (!_marked[i]){
				_color[i] = true;
				_colorT++;
				_bipartito = dfs(G, i);
				//no nos vale con contar los T o F al final del dfs, ya que no tiene porque ser el minimo de cada componente conexa
				//por ello vamos sumando los minimos de cada componente
				_total += min(_colorF, _colorT);
				_colorF = 0, _colorT = 0;

			}
		}
	}

	bool esBipartito(){
		return _bipartito;
	}

	int numGuardias(){
		return _total;
	}

private:
	vector<bool> _marked;
	vector<bool> _color;
	int _colorT=0, _colorF=0, _total=0;//no olvidar inicializar a 0
	bool _bipartito;

	bool dfs(Grafo const& G, int v){
		_marked[v] = true;

		for (int w : G.ady(v)){

			if (!_marked[w]){
				_color[w] = !_color[v];
				//vamos contando los colores, que será donde irian los guardias
				if (_color[w]){
					_colorT++;
				}
				else{
					_colorF++;
				}
				if (!dfs(G, w)){
					return false;
				}
			}
			else if (_color[w] == _color[v]){
				return false;
			}
		}

		return true;
	}

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int V, A;

	cin >> V;
	
	if (!std::cin)  // fin de la entrada
		return false;

	cin >> A;
	int a, b;

	Grafo g(V);

	for (int i = 0; i < A; i++){
		cin >> a >> b;
		g.ponArista(a-1, b-1);
	}

	Bipartito gBi(g);

	if (gBi.esBipartito()){
		cout << gBi.numGuardias() <<"\n";
	}
	else{
		cout << "IMPOSIBLE\n";
	}


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
