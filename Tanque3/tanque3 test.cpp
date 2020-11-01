#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

struct conexion
{
	int distancia, final;
	conexion(int D, int V2) : distancia(D), final(V2) {};
};
struct menorDistancia {
    bool operator() (const conexion& a, const conexion& b) const {
        return a.distancia <= b.distancia;
    }
};

int T, Q;
std::vector<int> V, V_copy, padre, respuestas;
std::vector<std::priority_queue<conexion, std::vector<conexion>, menorDistancia> > conexiones, conexiones_copy;

int analizarContenedor(int litrosRestantes)
{
	std::vector<bool> tanqueConAgua(T, false);
	int contadorTanquesConAgua = 0;

	int tanqueActual = 0;
	const conexion* conexionMasBaja = nullptr;

	while(true)
	{
		//std::cout << "****** ELEMENTO " << tanqueActual << std::endl;
		// ? calcula la conexion mas baja de haber
		conexionMasBaja = (!conexiones[tanqueActual].empty() ? &conexiones[tanqueActual].top() : nullptr);
		//std::cout << "CMB: " << (conexionMasBaja != nullptr ? conexionMasBaja->final : -1) << std::endl;

		// ? llena hasta encontrar una tuberia o el techo
		//std::cout << "ANTES " << V[tanqueActual] << " ";
		
		int litrosLlenados = V[tanqueActual] - (conexionMasBaja != nullptr ? conexionMasBaja->distancia : 0);

		V[tanqueActual] -= litrosLlenados;
		litrosRestantes -= litrosLlenados;

		if(!tanqueConAgua[tanqueActual] && litrosLlenados > 0)
		{
			contadorTanquesConAgua++;
			tanqueConAgua[tanqueActual] = true;
			//std::cout << "(AUMENTO) ";
		}
		
		//std::cout << " // AHORA " << V[tanqueActual] << std::endl << "Litros restantes: " << litrosRestantes << std::endl;

		if (litrosRestantes <= 0)
		{
			break;
		}
		else if (conexionMasBaja != nullptr)
		{
			//std::cout << "accediendo a hijo..." << std::endl;
			tanqueActual = conexionMasBaja->final;
			conexiones[padre[tanqueActual]].pop();

		}
		else if (tanqueActual != 0)
		{
			//std::cout << "regresando a padre..." << std::endl;
			tanqueActual = padre[tanqueActual];
		}
		else
		{
			break; //no hay mas tanques a llenar
		}
	}

	return contadorTanquesConAgua;
	
}

int main()
{
	std::ifstream input;
	input.open("input.txt");

	// lectura de tanques y capacidades
	input >> T;
	for(int i = 0; i < T; i++)
	{
		int Vi;
		input >> Vi;
		V.push_back(Vi);
	}
	V_copy = V;

	//lectura de conexiones
	conexiones.resize(T); //conexiones[0] es contenedor "1"
	padre.resize(T); padre[0] = -1;
	for(int j = 0; j < T - 1; j++)
	{
		int V1, D, V2;
		input >> V1 >> D >> V2;
		conexiones[V1 - 1].push(conexion(D, V2 - 1));
		padre[V2 - 1] = V1 - 1;
	}
	conexiones_copy = conexiones;

	//lectura de preguntas
	input >> Q;
	for(int k = 0; k < Q; k++)
	{
		int Ki;
		input >> Ki;

		respuestas.push_back(analizarContenedor(Ki));
		
		V = V_copy;
		conexiones = conexiones_copy;
	}
	input.close();

	//impresion de respuestas
	for(int r = 0; r < Q; r++)
	{
		std::cout << respuestas[r] << (r == Q - 1 ? "" : " ");
	}
	
	return 0;

}