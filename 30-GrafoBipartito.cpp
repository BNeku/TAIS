//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;


class Bipartito{
public:
	Bipartito(Grafo const & g):marked(g.V(), false), color(g.V()), bipartito(true){
		for (int i = 0; i < g.V() && bipartito; i++){
			if (!marked[i]){
				color[i] = true;//lo pintamos de color true para no tener que 
				//acordarnos en la llamada de qué color era el padre
				bipartito = dfs(g, i);
			}
		}
	}

	bool esBipartito(){
		return bipartito;
	}
private:
	vector<bool> marked;//para marcar en profundidad
	vector<bool> color;
	bool bipartito;

	//función recursiva
	bool dfs(Grafo const & g, int v){
		marked[v] = true;
		//g.ady da los adyacentes
		for (int w : g.ady(v)){
			if (!marked[w]){//si está marcado
				color[w] = !color[v];
				if (!dfs(g, w))//si la llamada recursiva da false
					return false;//no hay que devolver lo que devuelva la llamada
			}
			else if(color[w]==color[v]){//si no está marcado y las dos aristas estan pintadas del mismo color
				return false;
			}
		}

		return true;//si se acaba el bucle es que todo ha ido bien
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int V, A;

	cin >> V;//numero de vertices

	if (!std::cin)  // fin de la entrada
		return false;

	cin >> A; //numero de aristas

	Grafo g(V);
	int a1, a2;

	for (int i = 0; i < A; i++){
		cin >> a1 >> a2;
		g.ponArista(a1, a2);
	}
	
	Bipartito grafo(g);

	if (grafo.esBipartito()){
		cout << "SI" << endl;
	}
	else{
		cout << "NO" << endl;
	}
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos30.txt");
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
