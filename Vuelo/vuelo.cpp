#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>

unsigned int MAX = std::numeric_limits<unsigned int>::max();

std::vector<std::vector<unsigned int> > grilla;
std::vector<int> alturasPajara;
std::vector<int> mejoresAlturas;

int main()
{
	std::ios_base::sync_with_stdio(false);

	// lectura de alturas de pajara
	std::ifstream input;
	input.open("vuelo.in");

	int I; input >> I; I++;
	alturasPajara.resize(I); alturasPajara[0] = 0;
	mejoresAlturas.resize(I); mejoresAlturas[0] = 0;
	
	grilla.resize(I);
	for(auto& g : grilla) g.resize(301, MAX);
	grilla[0][0] = 0; //inicializa valor inicial

	for(int i = 1; i < I; i++)
	{
		int Mi; input >> Mi;
		alturasPajara[i] = Mi;
	}
	input.close();

	//calcula mejor posicion para cada casilla
	for(int col = 1; col < I; col++)
	{
		for(int fil = 0; fil < 301; fil++)
		{
			unsigned int mejorPrevio = std::min(
				(fil > 0 ? grilla[col-1][fil-1] : MAX),
				(fil < 300 ? grilla[col-1][fil+1] : MAX)
			);

			if(mejorPrevio != MAX) grilla[col][fil] = mejorPrevio + abs(fil - alturasPajara[col]);
		}
	}

	//elije la mejor de la ultima casilla
	unsigned int mejorDistanciaTotal = MAX;
	for(int fil = 0; fil < 301; fil++)
	{
		if(grilla[I-1][fil] < mejorDistanciaTotal)
		{
			mejorDistanciaTotal = grilla[I-1][fil];
			mejoresAlturas[I-1] = fil;
		}
	}

	//elije camino a tomar
	for(int col = I-2; col >= 0; col--)
	{
		int fil = mejoresAlturas[col+1];

		mejoresAlturas[col] = (
			(fil > 0 ? grilla[col][fil-1] : MAX) < (fil < 300 ? grilla[col][fil+1] : MAX)
			? fil-1 : fil+1
		);
	}

	std::ofstream output;
	output.open("vuelo.out");

	output << mejorDistanciaTotal;
	
	for(int i = 1; i < I; i++)
	{
		output << std::endl << mejoresAlturas[i];
	}

	return 0;
}
