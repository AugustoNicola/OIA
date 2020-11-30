//! complejidad aproximada de O(2^50 * n^2)
//! ademas, es un enfoque que ya probe con el problema muestras
//* la solucion optima utiliza algun tipo de DP con bitwise, investigar eso

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct casillero
{
	bool enRegion = false; //para poder meter los casilleros en el vector de regionCursor
	char color;
};

int colorAIndice(char color);
char indiceAColor(int indice);

typedef vector<vector<casillero>> grilla;
typedef pair<int,int> par;

vector<par> movs = {{1,0},{0,1},{-1,0},{0,-1}};
int N; grilla estadoInicial;
vector<char> solucion;

struct Arbol
{
	grilla estado;
	vector<par> regionCursor;
	vector<char> pintadas;

	Arbol* prox[2];
	Arbol* padre;

	Arbol(Arbol* papa, grilla est, vector<par> regCurs, vector<char> pint)
	: padre(papa), estado(est), regionCursor(regCurs), pintadas(pint) {prox[0] = nullptr; prox[1] = nullptr;}
	~Arbol(){delete prox[0]; delete prox[1];}

	bool calcularEstado(queue<Arbol*>& colaEstados)
	{
		// repinta la region con el color deseado
		if(pintadas.size() > 0)
		{
			for(par& cas : regionCursor) estado[cas.first][cas.second].color = pintadas[pintadas.size() - 1];
		}
		
		//BFS para mergear regiones y encontrar opciones
		bool opciones[3] = {0,0,0}; // R A V
		vector<vector<bool>> visitado(N, vector<bool>(N,false));

		queue<par> cola;
		cola.emplace(0,0); visitado[0][0] = true;

		while(!cola.empty())
		{
			par elem = cola.front(); cola.pop(); casillero& cas = estado[elem.first][elem.second];
			
			//ubica el casillero en la region
			if(!cas.enRegion)
			{
				regionCursor.emplace_back(elem.first, elem.second);
				cas.enRegion = true;
			}

			//busca mas casilleros de la region y opciones de color
			for(par& mov : movs)
			{
				int a = elem.first + mov.first, b = elem.second + mov.second;
				//si es una baldosa existente
				if(a >= 0 && a < N   &&   b >= 0 && b < N)
				{
					// es de diferente color
					if(estado[a][b].color != estado[0][0].color)
					{
						opciones[colorAIndice(estado[a][b].color)] = 1;
					}
					//es del mismo color y se puede visitar
					else if(!visitado[a][b])
					{
						cola.emplace(a,b);
						visitado[a][b] = true;
					}
				}
			}
		}

		//recursion
		if(opciones[0] == 0 && opciones[1] == 0 && opciones[2] == 0)
		{
			solucion = pintadas;
			return true;
		}
		else
		{
			for(int i = 0; i < 3; i++)
			{
				//si este color es una posibilidad
				if(opciones[i])
				{
					vector<char> proxMovimiento = pintadas; proxMovimiento.push_back(indiceAColor(i));
					prox[0] = new Arbol(this, estado, regionCursor, proxMovimiento);
					colaEstados.push(prox[0]); //izquierda
				}
			}
		}
		return false;
	}

};

int colorAIndice(char color)
{
	return
	color == 'R' ? 0 :
	color == 'A' ? 1 : 2 ;
}
char indiceAColor(int indice)
{
	return
	indice == 0 ? 'R' :
	indice == 1 ? 'A' : 'V' ;
}

int main()
{
	// INPUT
	std::ios_base::sync_with_stdio(false);
	std::ifstream input;
	input.open("repintar.in");

	input >> N; estadoInicial.resize(N, vector<casillero>(N));

	string strActual;
	for(int i = 0; i < N; i++)
	{
		input >> strActual;
		for(int j = 0; j < N; j++)
		{
			estadoInicial[i][j].color = strActual[j];
		}
	}	

	input.close();

	//resolucion
	queue<Arbol*> colaEstados; //para realizar bfs
	Arbol *raiz = new Arbol(nullptr, estadoInicial, {}, {});
	colaEstados.push(raiz);

	while (!colaEstados.empty())
	{
		Arbol* nodoARevisar = colaEstados.front(); colaEstados.pop();
		if(nodoARevisar->calcularEstado(colaEstados)) break;
	}

	
	// OUTPUT
	std::ofstream output;
	output.open("repintar.out");

	output << solucion.size() << std::endl;
	for(char& paso : solucion) output << paso;

	output.close();

	return 0;
}