#include <string>
#include <vector>

using namespace std;

int decada(int fecha) {

    string fechaStr = to_string(fecha);
    string fechaSubstr = fechaStr.substr(2,2);

    return stoi(fechaSubstr);
}

bool esmayor(int edad) {
    return edad >= 18;
}

string nombrecompleto(string nombre, string apellido) {
    return nombre.append(" ").append(apellido);
}

int cantidadmayores(vector<int> &edades) {
    int contadorMayores = 0;
    for(int& persona : edades)
    {
        if(esmayor(persona)) contadorMayores++;
    }
    return contadorMayores;
}