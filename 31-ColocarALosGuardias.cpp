//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include "Grafo.h"
using namespace std;

/*el grafo debe ser bipartito para poder colocar guardias
si es bipartito, se pueden colocar y entonces quedarnos con el menor conjunto
no podemos depender de por donde empezamos a empezar
coger el menor de los componentes en CADA componente conexa
cada componente conexa solo se puede pintar de dos formas, dependiendo por qué color comenzamos a pintar
la suma de los menores es la respuesta
*/


class Bipartito{
public:
	Bipartito(Grafo const & g) :marked(g.V(), false), color(g.V()), bipartito(true){
		for (int i = 0; i < g.V() && bipartito; i++){
			if (!marked[i]){
				color[i] = true;//lo pintamos de color true para no tener que 
				t++;
				//acordarnos en la llamada de qué color era el padre
				bipartito = dfs(g, i);
				pintar();
				f = t = 0;
			}
		}
	}

	bool esBipartito(){
		return bipartito;
	}


	int minGuardias(){
		int suma = 0;

		for (int i = 0; i < menores.size(); i++){
			suma += menores[i];
		}

		return suma;
	}

private:
	vector<bool> marked;//para marcar en profundidad
	vector<bool> color;
	vector<int> menores;
	bool bipartito;
	int t = 0, f = 0;

	//función recursiva
	bool dfs(Grafo const & g, int v){
		marked[v] = true;
		//g.ady da los adyacentes
		for (int w : g.ady(v)){
			if (!marked[w]){//si está marcado
				color[w] = !color[v];
				if (color[w] == true){
					t++;
				}
				else{
					f++;
				}
				if (!dfs(g, w))//si la llamada recursiva da false
					return false;//no hay que devolver lo que devuelva la llamada
			}
			else if (color[w] == color[v]){//si no está marcado y las dos aristas estan pintadas del mismo color
				return false;
			}
		}

		return true;//si se acaba el bucle es que todo ha ido bien
	}

	bool pintar(){
		if (bipartito){
			if (t > f){
				menores.push_back(f);
			}
			else{
				menores.push_back(t);
			}
			return true;
		}
		else{
			return false;
		}
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

	Grafo graf(V);
	int a1, a2, n;

	for (int i = 0; i < A; i++){
		cin >> a1 >> a2;
		graf.ponArista(a1-1, a2-1);
	}
	Bipartito g(graf);

	if (g.esBipartito()){
		cout << g.minGuardias() << endl;
	}
	else{
		cout << "IMPOSIBLE" << endl;
	}
	

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos31.txt");
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
