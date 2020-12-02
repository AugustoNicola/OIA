#include <iostream>
#include <string>
#include <vector>

using namespace std;

int decada(int fecha);
bool esmayor(int edad);
string nombrecompleto(string nombre, string apellido);
int cantidadmayores(vector<int> &edades);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int funcionId;
    cin >> funcionId;
    if (funcionId == 1) {
        int fecha;
        cin >> fecha;
        cout << decada(fecha) << "\n";
    } else if (funcionId == 2) {
        int edad;
        cin >> edad;
        cout << (const char *[]){"false", "true"}[esmayor(edad)] << "\n";
    } else if (funcionId == 3) {
        string nombre;
        cin >> nombre;
        string apellido;
        cin >> apellido;
        cout << nombrecompleto(nombre, apellido) << "\n";
    } else if (funcionId == 4) {
        int n;
        cin >> n;
        vector<int> edades;
        edades.resize(n);
        for (int i0 = 0; i0 < n; i0++) {
            cin >> edades[i0];
        }
        cout << cantidadmayores(edades) << "\n";
    }
    return 0;
}
