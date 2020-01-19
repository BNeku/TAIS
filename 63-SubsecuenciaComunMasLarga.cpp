#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Matriz.h"

using namespace std;

/*
Tenemos dos palabras, X e Y tales que:
X[0...i]
Y[0...j]
Pensar en una función que calcule la longitud de la subsecuencia, no en un algoritmo
Si la última letra es común, debe de estar en la secuencia, y si no lo és, puede estar una u otra o ninguna
*/

//subsecuencia común a ambas secuencias
/*
			____
		   | sub(i-1, j-1) + 1  si X[i-1] = Y[j-1] si son iguales
sub(i,j) = { max((sub(i-1,j), sub(i, j-1))  e.o.c nos quedamos con el máximo
		   |___
i>0 ^ j>0

casos base:
sub(0,j) = 0
sub(i,0) = 0

   0..j..m
   _______
0 |00....0|
. |0  |  ||
. |0--*  ||
. |0     ||
n |0-----7|
  |_______|


Coste O(n*m)*/
string subcadena(const string &p1, const string &p2){
	int n = p1.size();
	int m = p2.size();
	Matriz<int> cadenas(n + 1, m + 1, 0);

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (p1[i-1] == p2[j-1]){
				cadenas[i][j] = cadenas[i-1][j - 1] + 1;
			}
			else{
				cadenas[i][j] = max(cadenas[i - 1][j], cadenas[i][j - 1]);
			}
		}
	}

	int tamanio = cadenas[n][m];
	string subcadena = "", aux="";
	int i = n, j = m;

	/*Si los caracteres i y j coinciden, entonces forman parte de la solución y te mueves en diagonal. 
	Si no, se ve de dónde viene el mínimo y te mueves a esa casilla, sin añadir nada a la palabra solución.*/
	while (tamanio > 0){
		if (p1[i-1] == p2[j-1]){
			subcadena += p1[i - 1];
			tamanio--;
			i--;
			j--;
		}
		else{
			if (cadenas[i][j] == cadenas[i][j - 1]){
				j--;
			}
			else{
				i--;
			}
		}
	}

	string palabra = "";
	for (int i = subcadena.size(); i > 0; i--){
		palabra += subcadena[i-1];
	}


	return palabra;
}

bool resuelveCaso() {
	string x1, x2;

	cin >> x1 >> x2;

	if (!std::cin)  
		return false;
	//subcadena(x1, x2);
	cout << subcadena(x1,x2) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos63.txt");
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

