#include <string>
#include <vector>

using namespace std;

vector<int> romperonda(vector<int> &ronda, int k) {


	auto pos = [&](int index) -> int {
		return index % ronda.size();
	};
	//para K = 2
	//X guarda inicio del primer fragmento, Y guarda su longitud
	//iterar todas las longitudes y posiciones inciales moviendo los numeros
	int N = ronda.size();
	int mejorTotal = 0;

	//*para cada posicion inicial
	for (int X = 0; X < N; X++)
	{
		int sumaElementosA = 0;
		int sumaElementosB = 0;
		for(int &elem : ronda) sumaElementosB += elem; //segunda ronda empieza con todos los nodos, se le resta el primero en el loop

		//*para cada offset
		for (int Y = 0; Y < N - 2; Y++)
		{
			int valorNuevoNodo = ronda[pos(X + Y)];
			sumaElementosA += valorNuevoNodo; //suma nuevo elemento
			sumaElementosB -= valorNuevoNodo; //resta nuevo elemento

			int puntajeTotal = (
				((sumaElementosA % 16)*(sumaElementosA % 16)) +
				((sumaElementosB % 16)*(sumaElementosB % 16))
			);
			mejorTotal = (puntajeTotal > mejorTotal ? puntajeTotal : mejorTotal);
		}
	}

	int sumaGrupo = 0;
	for(int i = 1; i < N; i++) sumaGrupo += ronda[i];
	int total = ((sumaGrupo % 16)*(sumaGrupo % 16));
	total += ((ronda[0] % 16)*(ronda[0] % 16));
	

	return {mejorTotal, total};

}
