#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

void BFS(int x, int y);

struct baldosa
{
	bool visitado = false;
	bool accesible = true;
	bool esEntrada = false;
};

pair<int,int> movimientos[4] = {{-1,0}, {0,-1}, {1, 0}, {0,1}};
vector<vector<baldosa> > baldosas;
vector<pair<int,int>> visitadosIteracion;
int N, M, P;
int baldosasAccesibles;

vector<int> laboratorio(vector<string> mapa, vector<int> perrosFila, vector<int> perrosColumna)
{
	N = mapa.size(); M = mapa[0].size(); P = perrosFila.size(); vector<int> estadoBaldosas(P);

	baldosas.resize(N,vector<baldosa>(M));

	baldosasAccesibles = N * M; //inicializa el numero al maximo

	// localiza las entradas y los escritorios
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			if(mapa[i][j] == '#')
			{
				baldosas[i][j].accesible = false;
				baldosasAccesibles--;
			}
			if(mapa[i][j] == 'E')
			{
				baldosas[i][j].esEntrada = true;
			}
		}
	}
	
	for(int p = 0; p < P; p++)
	{
		// ? entrada de cada perro
		int x = perrosFila[p], y = perrosColumna[p];
		
		// si la baldosa no era accesible no es posible que se altere ninguna otra baldosa
		if(baldosas[x][y].accesible)
		{
			baldosas[x][y].accesible = false; 
			baldosas[x][y].esEntrada = false;
			baldosasAccesibles--;

			// * busca realizar el BFS
			for(pair<int,int>& mov : movimientos)
			{
				int a = x + mov.first; int b = y + mov.second;
				if(
					a >= 0 && a < N          &&
					b >= 0 && b < M          &&
					baldosas[a][b].accesible &&
					!baldosas[a][b].visitado    // si fue visitado y es accesible ya sabemos que es accesible
				) { BFS(a,b); }
			}

			// * visitados  reseteados
			for(pair<int,int>& v : visitadosIteracion) baldosas[v.first][v.second].visitado = false;
			visitadosIteracion = {};
		}
		estadoBaldosas[p] = baldosasAccesibles;
	}

	return estadoBaldosas;
}

// * precondicion: es accesible y existe
void BFS(int x, int y)
{
	bool salidaEncontrada = false;

	queue<pair<int,int>> cola; cola.emplace(x,y);
	vector<pair<int,int>> visitados;
	baldosas[x][y].visitado = true;
	
	while(!cola.empty())
	{
		// ? nuevo elemento
		pair<int,int> bald = cola.front(); cola.pop();
		int b_x = bald.first, b_y = bald.second;

		visitados.emplace_back(b_x, b_y); visitadosIteracion.emplace_back(b_x,b_y);
		if (baldosas[b_x][b_y].esEntrada)
		{
			salidaEncontrada = true; baldosas[b_x][b_y].visitado = false;
		}
		else //no puede seguir el BFS si es una entrada
		{
			// * busca hijos no recorridos
			for(pair<int,int>& mov : movimientos)
			{
				int a = b_x + mov.first, b = b_y + mov.second;
				//si es una baldosa visitable
				if(
					a >= 0 && a < N          &&
					b >= 0 && b < M          &&
					!baldosas[a][b].visitado &&
					baldosas[a][b].accesible
				) { cola.emplace(a,b); baldosas[a][b].visitado = true; }
			}
		}
	}

	// ? marca como no accesibles de ser necesario
	if(!salidaEncontrada)
	{
		for(pair<int,int>& v : visitados)
		{
			// !visitados no reseteados
			baldosas[v.first][v.second].accesible = false;
			baldosasAccesibles--;
		}
	}
}
// ! poscondicion: el estado de visitado de todas las baldosas es false

int main()
{
	vector<string> mapa = {
		"E..#...#..",
		"E..#...#..",
		"E..#...#..",
		"E..##.##.#",
		"E.........",
		"E..##.##.#",
		"E..#...#..",
		"E..#...#..",
		"E..#...#..",
		"E..#...#..",
	};
	vector<int> pF = {3, 5, 3, 5, 4, 4};
	vector<int> pC = {5, 5, 8, 8, 7, 3};


	vector<int> respuesta = laboratorio(mapa, pF, pC);
	for (int& r : respuesta)
	{
		std::cout << r << " ";
	}
	
	return 0;
}