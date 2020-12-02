#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> cromosoma(string cadena);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cadena;
    cin >> cadena;
    vector<int> returnedValue;
    returnedValue = cromosoma(cadena);
    for (int i = 0; i < int(returnedValue.size()); i++) {
        if (i > 0) cout << " ";
        cout << returnedValue[i];
    }
    cout << "\n";
    return 0;
}
