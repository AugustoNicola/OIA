#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct conexion
{
	int distancia, final;
	conexion(int D, int V2) : distancia(D), final(V2) {};
};

std::vector<int> V, respuestas;
std::vector<std::vector<conexion> > conexiones;
int contadorTanques;

int analizarContenedor(int litrosRestantes, int contenedor)
{
	bool contenedorActualConAgua = false;

	while(true)
	{
		// ? calcula la conexion mas baja de haber
		conexion *conexionMasBaja = nullptr;
		for(conexion &tuberia : conexiones[contenedor])
		{
			conexionMasBaja = (conexionMasBaja == nullptr or tuberia.distancia < conexionMasBaja->distancia
			? conexionMasBaja : &tuberia);
		}

		// ? llena hasta encontrar una tuberia o el techo
		if(conexionMasBaja != nullptr)
		{
			// * hay conexiones disponibles, asi que resta lo que se pueda hasta la conexion mas baja
			int remanente = V[contenedor] - conexionMasBaja->distancia;
			V[contenedor] -= std::min(litrosRestantes, remanente);
			litrosRestantes -= std::min(litrosRestantes, remanente);

			if(remanente > 0 && !contenedorActualConAgua)
			{
				contadorTanques++;
				contenedorActualConAgua = true;
			}
		} else {
			// * no hay conexiones disponibles, asi que resta lo que se pueda del contenedor entero
			V[contenedor] -= std::min(litrosRestantes, V[contenedor]);
			litrosRestantes -= std::min(litrosRestantes, V[contenedor]);

			if(!contenedorActualConAgua)
			{
				contadorTanques++;
				contenedorActualConAgua = true;
			}
		}

		// ? verifica si se puede seguir
		if(litrosRestantes > 0 && conexionMasBaja != nullptr)
		{
			// * hay conexiones disponibles, asi que debe llamar recursivamente a la funcion con los litros restantes
			litrosRestantes = analizarContenedor(litrosRestantes, conexionMasBaja->final);
			// elimina el elemento del vector
			if(V[conexionMasBaja->final] == 0) 
			{
				conexiones[contenedor].erase(std::remove_if(conexiones[contenedor].begin(), conexiones[contenedor].end(), [conexionMasBaja](const conexion con){return con.final == conexionMasBaja->final;}), conexiones[contenedor].end());
			};
		} else {break;} // ! sale de la ejecucion si no puede seguir
	}

	// * devuelve la cantidad de litros que quedaron, tanto sea porque no quedaron como porque no se puede llenar mas
	return litrosRestantes;
	
}

int main(int argc, char const *argv[])
{
	
	int T, Q;

	//std::ifstream std::cin;
	//std::cin.open("std::cin.txt");

	// lectura de tanques y capacidades
	std::cin >> T;
	for(int i = 0; i < T; i++)
	{
		int Vi;
		std::cin >> Vi;
		V.push_back(Vi);
	}

	//lectura de conexiones
	for(int j = 0; j < T - 1; j++)
	{
		int V1, D, V2;
		std::cin >> V1 >> D >> V2;
		conexiones[V1].push_back(conexion(D, V2));
	}

	//lectura de preguntas
	std::cin >> Q;
	for(int k = 0; k < Q; k++)
	{
		int Ki;
		std::cin >> Ki;

		contadorTanques = 0;
		analizarContenedor(Ki, 1);
		respuestas.push_back(contadorTanques);
	}
	//std::cin.close();

	//impresion de respuestas
	for(int r = 0; r < Q; r++)
	{
		std::cout << respuestas[r] << (r == Q - 1 ? "" : " ");
	}
	
	return 0;

}