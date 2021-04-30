#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<int> romperonda(vector<int> &ronda, int k) {
	ofstream output; output.open("romperonda1.out");
	
	
	int n = ronda.size();
	
	auto pos = [&](int index) -> int {
		return index % ronda.size();
	};
	
	//? tabla de DP[K][e][l]:
	//* si tengo K fragmentos para usar en el rango de inicio i y longitud l, cual es la mayor cantidad de puntaje que puedo obtener?
	vector<vector<vector<int> > > DP(k, vector<vector<int>>(n, vector<int>(n, 0)));

	//* calculo K = 1 (0-indexeado)
	//para cada elemento
	for (int e = 0; e < n; e++)
	{
		int suma = 0;
		//para cada longitud
		//output << endl << "E: " << e << endl;
		for (int l = 0; l < n - 1; l++)
		{
			suma += ronda[pos(e + l)];
			DP[0][e][l] = (suma % 16) * (suma % 16);
			//output << l << ": " << DP[0][e][l] << "/";
		}
		
	}

	//output << "test" << endl << endl << endl;

	//para cada K mayor a 1
	for (int ki = 1; ki <= k - 1; ki++)
	{
		//output << "ki: " << ki << endl;
		//para cada elemento
		for (int e = 0; e < n; e++)
		{
			//output << "e: " << e << endl; 
			//para cada longitud
			for (int l = ki; l < n - 1; l++)
			{	
				//output << "l: " << l << endl;
				//* analizar rango actual con cantidad determinada de fragmentos, verificar todas las posibilidades
				int maximoRangoTotal = 0;
				
				//para cada valor de k del grupo inicio
				for (int kii = 0; kii < ki; kii++)
				{
					//para cada longitud VALIDA del grupo inicio
					for (int lii = 0; lii < l; lii++)
					{
						int lii2 = l - lii - 1;
						int kii2 = ki - kii - 1;
						
						
						//? validar operacion
						if(kii <= lii && kii2 <= lii2)
						{
							/*
							output << "--- para " << ki << e << l << " ---" << endl
							<< "lii: " << lii << "/ kii: " << kii << "/ lii2: " << lii2 << "/ kii2: " << kii2 << ": DA " << DP[kii][e][lii] + DP[kii2][lii+1][lii2] << endl;
							*/
							maximoRangoTotal = (maximoRangoTotal >
								DP[kii][e][lii] + DP[kii2][lii+1][lii2]
							? maximoRangoTotal : DP[kii][e][lii] + DP[kii2][lii+1][lii2]);
						}
					}
				}
				DP[ki][e][l] = maximoRangoTotal;
				output << "ki: " << ki << "/ e: " << e << "/l: " << l << "/// " << DP[ki][e][l] << endl;
			}
		}
	}
	//* respuesta final
	int mejorResultado = 0;
	for (int a = 0; a < n; a++)
	{
		mejorResultado = (mejorResultado > DP[k-1][a][n-1] ? mejorResultado : DP[k-1][a][n-1]);
	}
	
	output << endl << endl << "RESPUESTA: " << mejorResultado;
	return {mejorResultado, 0};

}


int main() {
    
	ifstream input; input.open("romperonda1.in");
	ofstream output; output.open("romperonda1.out");

    int n;
    input >> n;
    int k;
    input >> k;
    vector<int> ronda;
    ronda.resize(n);
    for (int i0 = 0; i0 < n; i0++) {
        input >> ronda[i0];
    }
    vector<int> returnedValue;
    returnedValue = romperonda(ronda, k);
    for (int i = 0; i < int(returnedValue.size()); i++) {
        if (i > 0) output << " ";
        output << returnedValue[i];
    }
    output << "\n";
    return 0;
}
