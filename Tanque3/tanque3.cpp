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

std::vector<int> V, V_copy, respuestas;
std::vector<std::priority_queue<conexion, std::vector<conexion>, menorDistancia> > conexiones, conexiones_copy;
int contadorTanques;

int analizarContenedor(int litrosRestantes, int contenedor)
{
	bool contenedorActualConAgua = false;
	const conexion* conexionMasBaja;

	do
	{
		// ? calcula la conexion mas baja de haber
		conexionMasBaja = (!conexiones[contenedor].empty() ? &conexiones[contenedor].top() : nullptr);

		// ? llena hasta encontrar una tuberia o el techo
		if(litrosRestantes > 0)
		{
			if(conexionMasBaja != nullptr)
			{
				// * hay conexiones disponibles, asi que resta lo que se pueda hasta la conexion mas baja
				int remanente = V[contenedor] - conexionMasBaja->distancia;
				int litrosLlenados = std::min(litrosRestantes, remanente);
				V[contenedor] -= litrosLlenados;
				litrosRestantes -= litrosLlenados;

				if(litrosLlenados > 0 && !contenedorActualConAgua)
				{
					contadorTanques++;
					contenedorActualConAgua = true;
				}
			} else {
				// * no hay conexiones disponibles, asi que resta lo que se pueda del contenedor entero
				int litrosLlenados = std::min(litrosRestantes, V[contenedor]);
				V[contenedor] -= litrosLlenados;
				litrosRestantes -= litrosLlenados;

				if(!contenedorActualConAgua && litrosLlenados != 0)
				{
					contadorTanques++;
					contenedorActualConAgua = true;
				}
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
				conexiones[contenedor].pop();
			};
		} else {break;} // ! sale de la ejecucion si no puede seguir
	}while(litrosRestantes > 0 && conexionMasBaja != nullptr);

	// * devuelve la cantidad de litros que quedaron, tanto sea porque no quedaron como porque no se puede llenar mas
	return litrosRestantes;
	
}

int main()
{
	
	int T, Q;

	// lectura de tanques y capacidades
	std::cin >> T;
	for(int i = 0; i < T; i++)
	{
		int Vi;
		std::cin >> Vi;
		V.push_back(Vi);
	}
	V_copy = V;

	//lectura de conexiones
	conexiones.resize(T); //conexiones[0] es contenedor "1"
	for(int j = 0; j < T - 1; j++)
	{
		int V1, D, V2;
		std::cin >> V1 >> D >> V2;
		conexiones[V1 - 1].push(conexion(D, V2 - 1));
	}
	conexiones_copy = conexiones;

	//lectura de preguntas
	std::cin >> Q;
	for(int k = 0; k < Q; k++)
	{
		int Ki;
		std::cin >> Ki;

		contadorTanques = 0;
		analizarContenedor(Ki, 0);
		V = V_copy;
		conexiones = conexiones_copy;
		respuestas.push_back(contadorTanques);
	}

	//impresion de respuestas
	for(int r = 0; r < Q; r++)
	{
		std::cout << respuestas[r] << (r == Q - 1 ? "" : " ");
	}
	
	return 0;

}