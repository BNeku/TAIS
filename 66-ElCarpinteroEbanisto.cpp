//Nerea Jimenez Gonzalez

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

using namespace std;

/*
cortes(i,j) = minimizar el esfuerzo de cortar un tablón 
¿qué parámetros? hay dos tipos:
	-Los que tienen como en la varillas, longitud y cortes
	-Los que son como el del paréntesis, se va cerrando un intervalo
Podemos pensar que es del primer tipo, pero es del segundo, ya que el coste de cortar depende de la longitud,
es decir, no vamos haciendo cortes en orden y elegimos unos si y otros no, si no que vamos a hacer todos los cortes
y tenemos que minimar el el esfuerzo entre los puntos i, j

Llamada inicial que resuelve el problema: cortes(0,numCortes)
Casos base: 
	como el caso base es una diagonal, lo mejor es recorrer la matriz por diagonales
	si no queremos recorrer en diagonales, siempre podemos recorrer de abajo a arriba y de izqda a dcha
	cortes(i, i+1)=0 , es decir, ya tengo una muesca y la siguiente, por lo que ya no tengo que cortar nada
Caso recursivo:
	cortes(i,j) = min(cortes(i,k) + cortes(k,j)+ 2*(v[j]-v[i])) donde i<k<j (j-i es la longitud)
	nuestra i es la f y la j la c
*/
//vector<int> cortes(numCortes+2);

const int INFINITO=1000000000;

/*coste:
	primer bucle : O(numCortes)
	segundo bucle: O(numCortes^2)
		-sus cuerpo es de O(numCortes)
		por lo que el coste del segundo bucle es de O(numCortes^3)
	en espacio necesita una matriz(numCortes*numCortes)
*/
int cortes(const vector<int> &cortes, int L){
	int n = cortes.size();
	//no hace falta sumarle +1 ya que no tenemos las filas de 0 de los casos base, ya que aqui el caso base es la diagonal
	//recordar poner el primer corte en el 0 y otro en el L
	Matriz<int> tabla(n, n,0);

	//es n+2 porque tenemos que incluir los cortes en 0 y en numcortes
	//ponemos la diagonal de 0 del caso base
	
	for(int d = 2; d <= n;d++){//diagonales
		for(int f = 0; f < n-d; f++){ //filas
			int c =f+d; //la columna es la fila + la diagonal
			int mini = INFINITO;
			for(int k = f+1; k < c; k++){
				mini = min(mini, tabla[f][k]+tabla[k][c]+(2*(cortes[c]-cortes[f])));
			}
			tabla[f][c]=mini;
		}
	}
	
	return tabla[0][n-1];
}

bool resuelveCaso() {
	int L, N;

	cin >> L >> N;

	if (L==0 && N==0)
		return false;

	vector<int> v(N+2,0);
	//mas dos porque tenemos que añadir el del principio y el del final
	v[0] = 0;
	v[N + 1] = L;

	for (int i = 1; i <= N; i++){
		cin >> v[i];
	}

	cout << cortes(v,L) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos66.txt");
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