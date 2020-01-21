//Nerea Jiménez González

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"
#include "Matriz.h"

using namespace std;

struct moneda{
	int valor;
	int cantidad;
};


const int INFINITO = 1000000000;
/*
Vamos cogiendo monedas del valor mas alto, hasta que no queden de estas y pasamos al siguiente.
Si nos pasamos del valor, pasamos al siguiente.
Si hemos llegado al precio exacto, paramos.

minMonedas(i,C) = número mini de monedas que necesito para conseguir el valor exacto del coche
valor[i] = valor que tiene la moneda i
cantidad[i] = cantidad de monedas i que tenemos

minMonedas(i,C) = minMonedas(i-1,C) si cantidad[i]<0  || valor[i] >C
				  min(minMonedas(i-1, C-valor[i])+1, minMonedas(i-1,C)) si e.o.c
CB:
minMonedas(i,0)=0
minMonedas(0,C)=0
*/
int minMonedas(vector<moneda> v, const int coche){
	int N = v.size();
	Matriz<int> tabla(N+1,coche+1, INFINITO);
	tabla[0][0] = 0;

	for (int i = 1; i <= N; i++){//valores de las monedas
		tabla[i][0] = 0;
		for (int j = 1; j <= coche; j++){
			tabla[i][j] = tabla[i - 1][j];

			if (j >= v[i - 1].valor){
				int aux = INFINITO;

				for (int k = 1; k <= v[i - 1].cantidad && j - k*v[i - 1].valor >= 0 && j - k*v[i - 1].valor <=coche; k++){
					aux = tabla[i - 1][j - k*v[i - 1].valor] + k;
					if (aux < tabla[i][j])
						tabla[i][j] = aux;
				}
			}

		}
	}

	return tabla[N][coche];
}


bool mayor (const moneda &a,const moneda &b){
	return a.valor > b.valor;
}

bool resuelveCaso() {
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<moneda> v(N);

	for (int i = 0; i < N; i++){
		cin >> v[i].valor;
	}
	for (int i = 0; i < N; i++){
		cin >> v[i].cantidad;
	}
	sort(v.begin(), v.end(), mayor);

	int coche;
	cin >> coche;

	int rdo=minMonedas(v, coche);

	if (rdo == INFINITO){
		cout << "NO\n";
	}else{
		cout << "SI " << rdo << "\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos68.txt");
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
