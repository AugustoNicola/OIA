#include <string>
#include <vector>
#include <iostream>

using namespace std;

int decada(int fecha) {

    std::string fechaStr = std::to_string(fecha);
    std::string fechaSubstr = fechaStr.substr(2,2);

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

int main()
{
    /*
    std::cout << "\ndecada 2000: " << decada(2000);
    std::cout << "\ndecada 1938: " << decada(1938);
    std::cout << "\ndecada 1900: " << decada(1900);
    std::cout << "\ndecada 2020: " << decada(2020);
    std::cout << "\ndecada 2010: " << decada(2010);
    std::cout << "\ndecada 1903: " << decada(1903);
    std::cout << "\ndecada 2004: " << decada(2004);
    */
    /*
    std::cout << "\nedad 0: " << esmayor(0);
    std::cout << "\nedad 120: " << esmayor(120);
    std::cout << "\nedad 34: " << esmayor(34);
    std::cout << "\nedad 18: " << esmayor(18);
    std::cout << "\nedad 17: " << esmayor(17);
    std::cout << "\nedad 60: " << esmayor(60);
    */

    /*
    std::cout << "\nnombre 'Juan Miguel': " << nombrecompleto("Juan", "Miguel");
    std::cout << "\nnombre 'Augusto Nicola': " << nombrecompleto("Augusto", "Nicola");
    std::cout << "\nnombre 'Este Banquito': " << nombrecompleto("Este", "Banquito");
    */
    /*
    vector<int> vector = {0,1,16,17,18,56,86,120};
    std::cout << "mayores " << cantidadmayores(vector);
    */
    return 0;
}