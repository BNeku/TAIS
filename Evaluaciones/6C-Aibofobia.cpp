//Nerea Jiménez González


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Matriz.h"

using namespace std;

/*
				 palindromo(i-1,j-1)+1 si i!=j
palindromo(i,j)= min(palindromo(i-1,j), palindromo(i,j-1) e.o.c
*/
void palidromo(const string &palabra){
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

	int letras = tabla[1][N];
	int total = N + letras;
	string final(total,' ');
	int i = 0, k = 0, j = N - 1, t = total - 1;

	while (total>0){
		if (total == 1){
			final[t] = palabra[i];
			total--;
		}else if (palabra[i] == palabra[j]){
			final[k] = final[t] = palabra[j];
			i++; k++; t--; j--;
			total -= 2;
		}
		else{
			if (tabla[i + 1][j] < tabla[i][j - 1]){
				final[k] = final[t] = palabra[j];
				k++; t--; j--;
			}
			else{
				final[k] = final[t] = palabra[i];
				i++; k++; t--;
			}
			total -= 2;
		}
		
		
	}

	final.substr(0, ' ');

	cout << letras <<" " << final <<"\n";
}

bool resuelveCaso() {
	string palabra;

	cin >> palabra;

	if (!cin)
		return false;

	palidromo(palabra);

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
