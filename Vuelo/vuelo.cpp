#include <vector>
#include <fstream>

std::vector<std::vector<int> > grilla;
std::vector<int> alturasPajara;
std::vector<int> mejoresAlturas;

int min(int x, int y, int z)
{
	int min = x;
	min = y < min ? y : min;
	min = z < min ? z : min; 
	return min;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	// lectura de alturas de pajara
	std::ifstream input;
	input.open("vuelo.in");

	int I; input >> I;
	alturasPajara.resize(++I); alturasPajara[0] = 0;
	mejoresAlturas.resize(I); mejoresAlturas[0] = 0;
	
	grilla.resize(I);
	for(auto& g : grilla) g.resize(301, 301);
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
			int mejorPrevio = min(
				(fil > 0 ? grilla[col-1][fil-1] : 301),
				grilla[col-1][fil],
				(fil < 300 ? grilla[col-1][fil+1] : 301)
			);

			if(mejorPrevio != 301) grilla[col][fil] = mejorPrevio + abs(fil - alturasPajara[col]);
		}
	}

	//elije la mejor de la ultima casilla
	int mejorDistanciaTotal = 301;
	for(int fil = 0; fil < 301; fil++)
	{
		if(grilla[I-1][fil] < mejorDistanciaTotal)
		{
			mejorDistanciaTotal = grilla[I-1][fil];
			mejoresAlturas[I-1] = fil;
		}
	}

	for(int col = I-2; col >= 0; col--)
	{
		int fil = mejoresAlturas[col+1];

		int mejorFila = fil;
		if(fil > 0 && grilla[col][fil-1] < grilla[col][mejorFila]) mejorFila = fil-1;
		if(fil < 300 && grilla[col][fil+1] < grilla[col][mejorFila]) mejorFila = fil+1;

		mejoresAlturas[col] = mejorFila;
	}

	std::ofstream output;
	output.open("vuelo.out");

	output << mejorDistanciaTotal;
	
	for(int& altura : mejoresAlturas)
	{
		output << std::endl << altura;
	}

	return 0;
}
