#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<int> conexionesHechas;
vector<int> aristasPorNodo;

vector<string> matrizAdj;
vector<int> numeracionOpuesta;

void buscarConexiones(const int &nodo)
{
	//buscamos asignarle a cada nodo todas sus aristas necesarias
	int aristasNecesarias = aristasPorNodo[nodo]; 
	//para cada nodo
	for (int i = 0; i < aristasPorNodo.size(); i++)
	{
		//* si ya terminamos de asignar, parar
		if(aristasNecesarias == conexionesHechas[nodo]) break;

		//nodo objetivo lleno, buscar otros candidados
		if(aristasNecesarias == conexionesHechas[i])
		{
			//*llamada a la funcion para buscar otro candidato para i
			if(buscarConexiones(i))
			{
				//*conexion exitosa
				conexionesHechas[nodo]++;
				//TODO asignar nodo en matriz de adyacencia
			}
		}
	}

	
}


bool analizarGrafo(const int &N)
{

	//* casos iniciales
	int sumaTotalAristas = 1 * N;
	int sumaTotalAristasOpuestas = (N-2) * N;

	//* calculo aristas posibles
	
	//para cada nodo exp n
	for (int i = 0; i < N; i++)
	{
		//para el resto de nodos
		for (int j = i; j < N; j++)
		{
			//? aumento valor de i hasta n, entonces vuelvo a 1 y aumento 1 el siguiente
			//*vuelvo a valor original y aumento 1 el siguiente?
		}
		
	}

	
	
	aristasPorNodo[i] += j;
				sumaTotalAristas += 1;
				sumaTotalAristasOpuestas -= 1;

				if(sumaTotalAristas != sumaTotalAristasOpuestas) continue;
	
}

int main()
{
	ifstream input; input.open("casos-grafos-curiosos/grafoscuriosos02.txt");
	ofstream output; output.open("output_grafoscuriosos02.txt");

	int T; input >> T;
	int N;

	for(int t = 0; t < T; t++)
	{
		input >> N;

		matrizAdj.resize(N);
		for(int )
		numeracionOpuesta.resize(N);
		bool existeGrafoCurioso = analizarGrafo(N);
	}

	return 0;
}