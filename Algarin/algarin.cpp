#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int max(int x, int y, int z)
{
	int max = x;
	max = y > max ? y : max;
	max = z > max ? z : max; 
	return max;
}
int max(int x, int y)
{
	return x > y ? x : y;
}
int max(int x) {return x;}

void algarin(std::string nombreArchivo)
{
	int N, M;
	std::vector<std::string> filas;
	std::vector<std::vector<int>> grilla;

	std::ifstream input;
	input.open(nombreArchivo);

	input >> M >> N;
	filas.resize(M);
	std::getline(input,filas[0]); //dummy
	
	//guardar filas individuales
	for(int i = 0; i < M; i++)
	{
		std::getline(input,filas[i]);
	}
	input.close();
	
	//valores de inicio de la grilla
	grilla.resize(M);
	for(int i = 0; i < M; i++)
	{
		grilla[i].resize(N);
		for(int j = 0; j < N; j++)
		{
			grilla[i][j] = (filas[i].at(0) == 'A') ? 0 : -2;
		}
	}

	// calcular maximo en cada celda (sin contar primera columna)
	for(int j = 1; j < N; j++)
	{
		for(int i = 0; i < M; i++)
		{
			int maximoPrevio = max(
				(i > 0 ? grilla[i-1][j-1] : -2), // diagonal arriba
				grilla[i][j-1],                  // medio
				(i < M-1 ? grilla[i+1][j-1] : -2)// diagonal abajo
			);
			
			if(filas[i].at(j) == 'M')
			{
				// HAY MALHECHOR
				grilla[i][j] = maximoPrevio > 0 ? 0 : -1; //decide si se pierden joyas o invalidar
			} else {
				// NO HAY MALHECHOR
				grilla[i][j] = maximoPrevio + (filas[i].at(j) == 'J' ? 1 : 0); // aniadir joya
			}
		}
	}
	//devolver maximo
	int numeroMaximoDeJoyas = -1;
	for(int i = 0; i < M; i++)
	{
		numeroMaximoDeJoyas = grilla[i][N-1] > numeroMaximoDeJoyas ? grilla[i][N-1] : numeroMaximoDeJoyas;
	}
	
	if(numeroMaximoDeJoyas == -1)
	{
		std::cout << "SIN SALIDA";
	} else {
		std::cout << "Joyas Maximas: " << numeroMaximoDeJoyas;
	}

}

int main()
{
	algarin("input.in");
	return 0;
}