#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<vector<int>> valores(N, vector<int>(N, 0));
	vector<vector<long int>> DP(N, vector<long int>(N, 0));

	// guarda valores de entrada
	for(int i = 0; i < N; i++) {
		DP[i].resize(N);
		for(int j = 0; j < N; j++) {
			cin >> valores[i][j];
			valores[j][i] = valores[i][j];
		}
	}

	long int mesh = 0;
	// buscamos todas las posibilidades de una pareja (dos bits)

	return 0;
}