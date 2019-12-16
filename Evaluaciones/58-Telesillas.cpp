//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int ordenarUsuarios(vector<int> &pesos, const int &peso_max){
	int sillas=0;
	int i=0, j=pesos.size()-1;
	
	sort(pesos.begin(), pesos.end());
	
	while(i<=j){
		if(pesos[i]+pesos[j]<=peso_max){
			sillas++;
			i++;
			j--;
		}else{
			sillas++;
			j--;
		}
	}
	
	return sillas;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   int peso_max, N;
   
   cin >>peso_max >> N;
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   vector<int> pesos(N);
   
   for(int i=0; i<N;i++){
	   cin >> pesos[i];
   }
   
   cout << ordenarUsuarios(pesos, peso_max) << "\n";
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos58.txt");
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
