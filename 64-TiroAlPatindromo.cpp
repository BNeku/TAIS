//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include"Matriz.h"

using namespace std;

/*
palindromo(i,j)=tamaño del palindromo más grande que se puede contruir a partir de la palabra con letras de i a j
palindromo(i,j) = palindromo(i+1,j-1)+2 si letra(i)==letra(j)
				  max(palindromo(i+1,j),palindromo(i,j-1)) si letra(i)!=letra(j)			
CB:
palindromo(i,j) = 1 cuando i==j
*/
string palindromo(const string &palabra){
	int N = palabra.size()-1;
	Matriz<int> tabla(N + 1, N + 1, 0);

	for (int d = 1; d <= N - 1; d++)
		tabla[d][d] = 1;

	for (int d = 1; d <= N - 1; d++){
		for (int i = 1; i <= N - d; i++){
			int j = i + d;

			if (palabra[i] == palabra[j]){
				//sumamos +2 porque serían la misma letra dos veces la que escribiriamos
				tabla[i][j] = tabla[i + 1][j - 1] + 2;
			}
			else{
				tabla[i][j] = max(tabla[i+1][j], tabla[i][j-1]);
			}
		}
	}

	int tamanio = tabla[1][N];
	string pal(tabla[1][N]+1, ' ');
	int a = 1, b = N;
	int x = 1, y = tamanio;
	
	while (tamanio > 0){
		if (tamanio == 1){
			pal[x] = palabra[b];
			tamanio--;
		}
		else if (palabra[a] == palabra[b]){
			pal[x] = palabra[a];
			pal[y] = palabra[b];
			//se colocan dos letras, por lo que reducimos dos veces el tamaño de lo que nos queda por formar del palindromo
			tamanio--;
			tamanio--;
			a++; x++;
			b--; y--;
		}
		else{
			if (tabla[a][b - 1] > tabla[a + 1][b]){
				b--;
			}
			else{
				a++;
			}
		}
	}
	
	pal = pal.substr(1, pal.size() - 1);

	return pal;
}

bool resuelveCaso() {
	string palabra;
	
	cin >> palabra;
	palabra = ' ' + palabra;

	if (!std::cin)  // fin de la entrada
		return false;

	cout << palindromo(palabra) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos64.txt");
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