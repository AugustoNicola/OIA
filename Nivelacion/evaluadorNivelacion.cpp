// La siguiente linea se usa para compilar en Geany con F9. Compilando de otra forma, podria ser necesario quitarla.
#include "nivelacion.cpp"

#include <iostream>
#include <string>

using namespace std;

int  nivelacion( string palabra );

int main()
{
    string s; cin >> s;
    cout << nivelacion(s) << endl;
    return 0;
}
