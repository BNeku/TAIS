//Nerea Jiménez González
//30/40 no está bien la reconstruccion de la palabra

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;


/*tabla(i,j)= minimo numero de letras a añadir para alcanzar la palbra j y esta sea un palindromo
tabla(i,j)=tabla(i+1,j-1) si palabra[i]==palabra[j]
tabla(i,j)==min(tabla(i+1,j), tabla(i,j-1) si palabra[i]!=palabra[j]
CB:
tabla(i,j)=0 si i==j
El coste es O(n*n) en tiempo y en espacio, donde n es el numero de letras de la palabra
*/

void aibofobia(const string &palabra){
	int N = palabra.size();
	Matriz<int> tabla(N + 1, N + 1, 0);

	for (int d = 1; d <= N - 1; d++){
		for (int i = 1; i <= N - d; i++){
			int j = i + d;
			if (palabra[i - 1] == palabra[j - 1]){
				tabla[i][j] = tabla[i + 1][j - 1];
			}
			else{
				tabla[i][j] = min(tabla[i + 1][j], tabla[i][j - 1]) + 1;
			}
		}
	}

	string aux = "", pal = "";
	int valor = tabla[1][N];

	if (tabla[1][N] > 0){
		int pos = 0;

		for (int i = N; i >= 1; i--){
			if (tabla[1][i] > tabla[1][i - 1] && valor == tabla[1][i]){
				aux += palabra[i - 1];
				valor--;
			}
			else if (tabla[1][i] < tabla[1][i - 1] && valor != 0){
				pos = i;
			}
		}

		if (pos == 0){
			pal = aux + palabra;
		}
		else{
			for (int i = 0; i < N; i++){
				if (i == pos - 1){
					pal += palabra[i] + aux;
				}
				else{
					pal += palabra[i];
				}
			}
		}
	}
	else{
		pal = palabra;

	}

	cout << tabla[1][N] << " " << pal << "\n";
}
bool resuelveCaso() {
	string p;

	cin >> p;

	if (!std::cin)  // fin de la entrada
		return false;

	aibofobia(p);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos6C.txt");
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
