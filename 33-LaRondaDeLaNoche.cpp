// NEREA JIMENEZ GONZALEZ

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const vector<pair<int, int>> dirs = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

//N numero de columnas
//M numero de filas
bool bfs(vector<vector<char>>jardin, vector<vector<bool>> marked, pair<int,int> ini, pair<int,int> fin, int &baldosas){
	int M = jardin.size(), N = jardin[0].size();
	vector<vector<int>> distTo(M, vector<int> (N));
	queue<pair<int,int>> q;
	bool posible;

	//si algun sensor llega a la casilla de entrada o salida
	if (marked[ini.first][ini.second] || marked[fin.first][fin.second]){
		posible = false;
	}
	else{
		distTo[ini.first][ini.second] = 0;
		marked[ini.first][ini.second] = true;
		q.push(ini);

		while (!q.empty()) {
			pair<int, int> v = q.front(); q.pop();
			for (auto d : dirs) {
				pair<int, int> w = { v.first + d.first, v.second + d.second };
				if (0 <= w.first && w.first < M && 0 <= w.second && w.second < N){
					if (!marked[w.first][w.second]) {
						distTo[w.first][w.second] = distTo[v.first][v.second] + 1;
						marked[w.first][w.second] = true;
						q.push(w);
					}
				}
			}
		}

		baldosas = distTo[fin.first][fin.second];
		posible = marked[fin.first][fin.second];
	}
	

	return posible;
}

void resuelveCaso() {
	int N, M;
	//N numero de columnas
	//M numero de filas
	cin >> N >> M;

	vector<vector<char>> jardin(M);
	vector<pair<int,int>> sensoresPos;
	char x;
	pair<int,int> ini, fin;
	vector<vector<bool>> marcados(M, vector<bool>(N));
	
	//i fila j columna
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			cin >> x;
			jardin[i].push_back(x);
			int y = (int(x) - 48);

			if (y>=0 && y<=9){
				sensoresPos.push_back({ i, j });
				marcados[i][j] = true;
			}

			if (x == '#')
				marcados[i][j] = true;
			if (x == 'E')
				ini = { i, j };
			if (x == 'P')
				fin = { i, j };
			
		}
	}

	
	for (int i = 0; i < sensoresPos.size(); i++){
		int fila = sensoresPos[i].first;
		int col = sensoresPos[i].second;
		int sensor = jardin[fila][col]-48;
		bool paredArr = false, paredAba = false, paredIzq = false, paredDcha = false;

		for (int j = 0; j < sensor; j++){
			int fPintaAba = fila + j + 1;
			//verticalmente hacia abajo
			if (fPintaAba <= M - 1 && !paredAba){//si esta dentro del tablero
				if (jardin[fPintaAba][col] == '#')
					paredAba = true;
				else marcados[fPintaAba][col] = true;
				//else jardin[fPintaAba][col] = 'x';
			}
			
			int fPintaArr = fila - j - 1;
			//verticalmente hacia arriba
			if (fPintaArr >=0 && !paredArr){//si esta dentro del tablero
				if (jardin[fPintaArr][col] == '#')
					paredArr = true;
				else marcados[fPintaArr][col] = true;
				//else jardin[fPintaArr][col] = 'x';
			}

			int cPintaDcha = col + j + 1;
			
			//horizontalmente hacia la derecha
			if (cPintaDcha <= N - 1 && !paredDcha){//si esta dentro del tablero
				if (jardin[fila][cPintaDcha] == '#')
					paredDcha = true;
				else marcados[fila][cPintaDcha] = true;
				//else jardin[fila][cPintaDcha] = 'x';
			}

			int cPintaIzq = col - j - 1;
			
			//horizontalmente hacia la izquierda
			if (cPintaIzq >= 0 && !paredIzq){//si esta dentro del tablero
				if (jardin[fila][cPintaIzq] == '#')
					paredIzq = true;
				else marcados[fila][cPintaIzq] = true;
				//else jardin[fila][cPintaIzq] = 'x';
			}
		}

		jardin[fila][col] = 'x';
	}
	int baldosas;

	if (!bfs(jardin, marcados, ini,fin,baldosas)){
		cout << "NO" << endl;
	}
	else{
		cout << baldosas << endl;
	}

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos33.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
