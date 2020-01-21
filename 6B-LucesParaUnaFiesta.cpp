//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INFINITO = 1000000000;

struct bombillas{
	int coste;
	int potencia;
};

/*
Potencia máxima PMax la cual no podemos sobrepasar
Potencia mínimo PMin a la que tenemos que llegar
coste bombillas
potencia bombillas

bombilla(i,P) = minimo coste de una instalación con potencia P utilizando las bombillas de la 1 a la i
caso base:
	bombillas(0,P) = INFINITO  P>0
	bombillas(i,P) = 0 P=0
caso recursivo:
				 | bombillas(i-1,p) si P[i]>p //no cojo la bombilla si su potencia no me vale
bombillas(i,P) = { min(bombillas(i-1,p), bombillas(i,p-P[i])+coste[i])		si P[i]<=p
				  //no uso la bombilla i   uso la bombilla i, pero tengo varias de la misma, por lo que no es i-1, sino i
solucion: min(tabla[nBombillas][k]) Pmin <= k <= Pmax
es el minimo de la última fila entre Pmin y Pmax
*/
pair<int,int> bombilla(const vector<bombillas> v, const int &Pmax, const int &Pmin){
	int n = v.size();
	Matriz<int> tabla(n, Pmax+ 1, INFINITO);

	tabla[0][0] = 0;

	/*
	optimizacion: coste O(n*P)
	en espacio O(n) donde n es el tamaño del vector tabla
	vector<int> tabla(potencia+1, INFINITO);
	tabla[0]=0;
	for(int i=1; i<=n;i++){
	for(int j=1; i<=p;j++){
	if(!potencias[i]>j)
	tabla[j] = min(tabla[j], tabla[j-potencias[i]+costeBombillas[i]);
	}
	}
	int mini= tabla[Pmin];
	for(int i=Pmin+1; i<Pmax;i++){
	mini= min(mini, tabla[i]);
	}
	*/

	for (int i = 1; i <= n-1; i++){
		tabla[i][0] = 0;
		for (int j = 1; j <= Pmax; j++){
			if (v[i].potencia > j){
				tabla[i][j] = tabla[i - 1][j];
			}
			else{
				tabla[i][j] = min(tabla[i - 1][j], tabla[i][j - v[i].potencia ]+ v[i].coste);
			}
		}
	}

	int costeMin = tabla[n-1][Pmin];
	int p = Pmin;

	for (int i = Pmin; i<=Pmax; i++){
		if (costeMin > tabla[n - 1][i]){
			costeMin = tabla[n - 1][i];
			p = i;
		}
	}


	return{ costeMin, p };
}

bool resuelveCaso() {
	int N, pMax, pMin;

	cin >> N >> pMax >> pMin;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<bombillas> v(N + 1);

	for (int i = 1; i <= N; i++){
		cin >> v[i].potencia;
	}
	for (int i = 1; i <= N; i++){
		cin >> v[i].coste;
	}

	pair<int,int> sol = bombilla(v, pMax, pMin);

	if (sol.first == INFINITO){
		cout << "IMPOSIBLE\n";
	}
	else{
		cout << sol.first << " " << sol.second << "\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos6B.txt");
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