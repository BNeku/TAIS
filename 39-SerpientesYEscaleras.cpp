//ejercicio 39
/*grafo dirigido, porque solo avanzas hacia delante
vértices = número de casillas
aristas = casillas en las que puede caer según el número del dado
realizar búsqueda en anchura
*/
//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
//coste O(V+E) (busqueda en anchura) == O(N^2+K*N^2) = O(K*N^2)
class Serpientes{
public:
	Serpientes(int N, int K, vector<int> const& saltos):marked(N*N+1, false), dist(N*N+1), M(N){
		
		marked[1]=true;
		queue<int> cola;
		cola.push(1);
		dist[1] = 0;
		while(!cola.empty()){
			int p = cola.front(); cola.pop();
			for(int i=1; i<= K && p+1<=N*N;i++){
				int w = p+i;
				if(saltos[w]>0)
					w = saltos[w];
				if(!marked[w]){
					dist[w] = dist[p]+1;//hay solo que poner la distancia si no está marcado
					if(w==N*N) return;//si ya hemos llegado a la última casilla, N*N, hemos terminado
					marked[w]=true;
					cola.push(w);
				}
				
			}
		}
	}
	
	int sol(){
		return dist[M*M];
	}
	
private:
	vector<bool> marked;
	vector<int> dist;
	int M;
};

bool resuelveCaso(){
	int N,K,S,E;

	cin>> N >> K >> S >> E;
	
	if(N == 0)
		return false;
	
	vector<int> saltos(N*N+1);//1-based
	int o, d;//origen y destino de escalera o serpiente
	
	for(int i=0; i<S+E;i++){
		cin>> o >> d;
		saltos[o] = d;//atajos, no aristas
	}
	
	Serpientes s(N,K,saltos);
	
	cout << s.sol() << endl;
	
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos39.txt");
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