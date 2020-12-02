#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



int main() {
	ifstream input; input.open("0.in");
    int n;
    input >> n;
    int q;
    input >> q;
    vector<int> siguiente;
    siguiente.resize(n);
    for (int i0 = 0; i0 < n; i0++) {
        input >> siguiente[i0];
    }
    vector<int> preguntaX;
    vector<long long> preguntaK;
    preguntaX.resize(q);
    preguntaK.resize(q);
    for (int i = 0; i < q; i++) {
        input >> preguntaX[i];
        input >> preguntaK[i];
    }
	input.close();
    vector<int> returnedValue;
    returnedValue = tutubo(siguiente, preguntaX, preguntaK);
    for (int i = 0; i < int(returnedValue.size()); i++) {
        cout << returnedValue[i] << "\n";
    }
    return 0;
}
