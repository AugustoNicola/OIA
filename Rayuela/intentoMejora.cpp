#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

pair<int,int> movs[4] = {{0,1},{1,0},{0,-1},{-1,0}}; // derecha abajo izquierda arriba
const int D = 100, P = 10000;
int d, p;

int puntosLetra[D][D];
char letra[D][D];

int puntosPalabra[P];
string palabra[P];

map<string, vector<int>> DP_opciones;

void buscarPalabra(int x, int y, string str, int puntaje, vector<int> opcionesPrevias)
{
	str += letra[x][y]; puntaje += puntosLetra[x][y];

	bool palabraMarcada[p] = {false};
	vector<int> opcionesActualizadas;

	bool hayDP = DP_opciones.count(str) ? true : false;
	vector<int> opciones = hayDP ? DP_opciones[str] : opcionesPrevias;

	for(pair<int,int>& mov : movs)
	{
		int a = x + mov.first, b = y + mov.second;
		if(a >= 0 && a < d   &&   b >= 0 && b < d)
		{
			//va buscando que palabras son validas en esta direccion
			vector<int> opcionesFisicas;
			for(int op : opciones)
			{	
				//si la proxima letra es viable:
				if(str.size() < palabra[op].size() && letra[a][b] == palabra[op][str.size()])
				{
					//si es la ultima letra (palabra finalizada) anota el mejor puntaje y elimina la opcion
					if(str.size() == palabra[op].size() - 1)
					{
						int nuevoPuntaje = puntaje + puntosLetra[a][b];
						puntosPalabra[op] = nuevoPuntaje > puntosPalabra[op] ? nuevoPuntaje : puntosPalabra[op];
					}
					//si no es la ultima letra guarda la opcion
					else
					{
						if(!hayDP && !palabraMarcada[op]) opcionesActualizadas.push_back(op); palabraMarcada[op] = true;
						opcionesFisicas.push_back(op);
					}	
				}
			}
			if(!hayDP) DP_opciones[str] = opcionesActualizadas; // si no se uso el DP hay que actualizar los resultados
			
			//si hay palabras validas, realiza la busqueda recursivamente
			if(opcionesFisicas.size()) buscarPalabra(a, b, str, puntaje, proxOpciones);
		}
	}
}

int main()
{
	ifstream input; input.open("rayuela.in");

	input >> d >> p;

	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			input >> letra[i][j] >> puntosLetra[i][j];
		}

	}
	for(int k = 0; k < p; k++)
	{
		input >> palabra[k]; puntosPalabra[k] = 0;
	}

	input.close();

	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			string ch(1, letra[i][j]);
			vector<int> opcionesIniciales;
			if(!DP_opciones.count(ch))
			{
				for(int z = 0; z < p; z++)
				{
					if(letra[i][j] == palabra[z][0]) opcionesIniciales.push_back(z);
				}
				DP_opciones[ch] = opcionesIniciales;
			} else {opcionesIniciales = DP_opciones[ch]; }

			if(opcionesIniciales.size()) buscarPalabra(i, j, "", 0, opcionesIniciales);
		}
	}

	ofstream output; output.open("rayuela.out");

	for(int k = 0; k < p; k++)
	{
		output << puntosPalabra[k] << endl;
	}
	output.close();

	return 0;
}