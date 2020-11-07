#include <iostream>
#include <vector>
#include <queue>

struct Investigador
{
	bool investigadoErdos = false;
	bool investigadoDarwin = false;

	int Erdos = -1;
	int Darwin = -1;

	std::vector<int> vecinos = {};
};

int main()
{
	//lee N y M
	int N, M;
	std::cin >> N >> M;
	std::vector<Investigador> investigadores(N,Investigador());

	//lee d
	int d;
	std::cin >> d;

	// lee conexiones
	int a,b;
	for(unsigned int i = 0; i < M; i++)
	{
		std::cin >> a >> b;
		investigadores[a-1].vecinos.push_back(b-1);
		investigadores[b-1].vecinos.push_back(a-1);
	}

	// ? ERDOS
	investigadores[0].Erdos = 0; investigadores[0].investigadoErdos = true; // es Erdos
	std::queue<int> colaErdos; colaErdos.push(0);
	while(!colaErdos.empty())
	{
		int numInv = colaErdos.front(); colaErdos.pop();
		Investigador& investigador = investigadores[numInv];

		for(int& numVecino : investigador.vecinos)
		{
			Investigador& vecino = investigadores[numVecino];

			if(!vecino.investigadoErdos)
			{
				vecino.Erdos = investigador.Erdos + 1;
				vecino.investigadoErdos = true;

				colaErdos.push(numVecino);
			}
		}
	}

	// ? DARWIN
	investigadores[N - 1].Darwin = 0; investigadores[N - 1].investigadoDarwin = true; // es Darwin
	std::queue<int> colaDarwin; colaDarwin.push(N - 1);
	while(!colaDarwin.empty())
	{
		int numInv = colaDarwin.front(); colaDarwin.pop();
		Investigador& investigador = investigadores[numInv];

		for(int& numVecino : investigador.vecinos)
		{
			Investigador& vecino = investigadores[numVecino];

			if(!vecino.investigadoDarwin)
			{
				vecino.Darwin = investigador.Darwin + 1;
				vecino.investigadoDarwin = true;

				colaDarwin.push(numVecino);
			}
		}
	}

	int contadorRespuesta = 0;
	for(unsigned int i = 0; i < N; i++)
	{
		if(investigadores[i].Erdos != -1 && investigadores[i].Darwin != -1
			&& investigadores[i].Erdos + investigadores[i].Darwin <= d) contadorRespuesta++;
	}

	std::cout << contadorRespuesta;

	return 0;
}