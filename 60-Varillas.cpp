//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

//en ocasiones, optimizar el espacio optimiza el tiempo

const int INFINITO = 1000000000;

typedef struct varilla{
	int longitud;
	int coste;
};

/*4.			 _____
				| minCoste(i - 1, j) li>j
 minVar(i, j) = { min(minCoste(i - 1, j - li)+Ci, minCoste(i - 1, j)) //igual que 3 pero sumando el coste
				| _____
 casos base :
 minCoste(i, 0) = 0 //cuando la longitud es 0 no hay minimo de varillas
 minCoste(0, j) = INFINITO //cuando no tengo varillas

*/
int minCoste(vector<varilla> &varillas, const int &L){
	int n = varillas.size() - 1;
	Matriz<int> minCoste(n + 1, L + 1, INFINITO);
	
	minCoste[0][0] = 0;

	for (int i = 1; i <= n; i++){
		minCoste[i][0] = 0;
		for (int j = 1; j <= L; j++){
			minCoste[0][j] = INFINITO;

			if (varillas[i].longitud > j){
				minCoste[i][j] = minCoste[i - 1][j];
			}
			else{
				minCoste[i][j] = min(minCoste[i-1][j-varillas[i].longitud]+varillas[i].coste, minCoste[i-1][j]);
			}
		}
	}

	return minCoste[n][L];
}


/*3.			 _____
				| minVar(i - 1, j) li>j
 minVar(i, j) = { min(minVar(i - 1, j - li)+1, minVar(i - 1, j)) //nos quedamos con el minimo entre poner la varilla i o no ponerla
				| _____
casos base :
minVar(i, 0) = 0 //cuando la longitud es 0 no hay minimo de varillas
minVar(0, j) = INFINITO //cuando no tengo varillas

*/
int minVar(vector<varilla> &varillas, const int &L){
	int n = varillas.size() - 1;
	Matriz<int> numMin(n + 1, L + 1, INFINITO);

	numMin[0][0] = 0;

	for (int i = 1; i <= n; i++){
		numMin[i][0] = 0;
		for (int j = 1; j <= L; j++){
			numMin[0][j] = INFINITO;

			if (varillas[i].longitud > j){
				numMin[i][j] = numMin[i - 1][j];
			}
			else{
				
				numMin[i][j] = min(numMin[i - 1][j], numMin[i - 1][j - varillas[i].longitud]+1);
			}
		}
	}

	return numMin[n][L];
}

/*2.			_____
			   | formas(i-1, j)  li>j
 formas(i,j) = { formas(i-1, j-li) //numero de formas en las que está implicada i   li <=j
			   | + formas(i-1, j) //numero de formas en las que no está implicada i
			   |_____
 casos base:
 formas(i,0) = 1 //cuando la longitud es 0 solo hay 1 forma
 formas(0, j) = 0 //cuando no tengo varillas, no tengo formas (j>0)

 //una vez tenemos la primera recursión, la forma de pensar es similar para el resto de apartados
*/
int formas(vector<varilla> &varillas, const int &L){
	int n = varillas.size() - 1;
	Matriz<int> numFormas(n + 1, L + 1);

	numFormas[0][0] = 1;

	for (int i = 1; i <= n; i++){
		numFormas[i][0] = 1;
		for (int j = 1; j <= L; j++){
			numFormas[0][j] = 0;

			if (varillas[i].longitud > j){
				numFormas[i][j] = numFormas[i - 1][j];
			}
			else{
				numFormas[i][j] = (numFormas[i - 1][j] + numFormas[i - 1][j - varillas[i].longitud]);
			}
		}
	}

	return numFormas[n][L];
}

/* 1.			 ____
				|  sePuede(i-1, j)  li > j
 sePuede(i,j) = {  sePuede(i-1, j-li) //se puede con la i, por lo que seguimos con la longitud j menos la longitud de i (li)
				|  ó								li<=j
				|  sePuede(i-1, j) //se puede con todas menos con la i
				|____
 casos base:
 sePuede (i,0) = cierto //la longitud de la varilla es 0
 sePuede(0,j) = falso	//no tengo varillas (j>0)
*/
bool sePuede(vector<varilla> &varillas, const int &L){
	int n = varillas.size() - 1;
	Matriz<bool> esPosible(n + 1, L + 1);

	esPosible[0][0] = true;

	for (int i = 1; i <= n; i++){
		esPosible[i][0] = true;
		for (int j = 1; j <= L; j++){
			esPosible[0][j] = false;

			if (varillas[i].longitud > j){
				esPosible[i][j] = esPosible[i - 1][j];
			}
			else{
				esPosible[i][j] = (esPosible[i - 1][j-varillas[i].longitud] || esPosible[i-1][j]);
			}
		}
	}
	
	return esPosible[n][L];
}

bool resuelveCaso() {
	int N, L;

	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<varilla> v(N+1);
	varilla aux;

	for (int i = 1; i <= N; i++){
		cin >> aux.longitud >> aux.coste;
		v[i] = aux;
	}

	if (sePuede(v, L)){
		cout << "SI " << formas(v, L) << " " << minVar(v,L) <<" "<< minCoste(v, L) <<"\n";
	}
	else{
		cout << "NO\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos60.txt");
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
