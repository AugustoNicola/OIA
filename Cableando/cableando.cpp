#include <vector>
#include <algorithm>
#include <iostream>

int cableando(int N, int K, std::vector<int> ki)
{
	ki.push_back(K);
	std::sort(ki.begin(), ki.end());

	int cableadoTotal = 0;
	for(unsigned int i = 1; i < ki.size(); i++)
	{
		cableadoTotal += ki[i] - ki[i - 1];
	}

	return cableadoTotal;
}

int main()
{
	int N, K, numActual;
	std::vector<int> ciudades;
	std::cin >> N >> K;
	
	for(int i = 0; i < N; i++)
	{
		std::cin >> numActual;
		ciudades.push_back(numActual);
	}

	std::cout << cableando(N, K, ciudades);
}