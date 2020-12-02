#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void prueba(){cout << "prueba";}

class Arbol
{
public:
    int nodosRestantes;
    int offset;
    int pasosTotales;
    vector<bool> yaAnalizado;

    Arbol* prox[2];

    Arbol(vector<bool> analisisPrevios, int pT, int off) : yaAnalizado(analisisPrevios), pasosTotales(pT), offset(off) {prox[0] = nullptr; prox[1] = nullptr;}
    ~Arbol(){delete prox[0]; delete prox[1];}

    int realizarMovimiento(vector<vector<int> >& muestras, std::queue<Arbol*>& cola)
    {
        int muestrasRestantes = 0;

        //recorre cada muestra para comprobar cuales fueron analizadas esta iteracion
        for(int i = 0; i < muestras.size(); i++)
        {
            if(!yaAnalizado[i])
            {
                //recorre las maquinas de una muestra
                for(int j = 0; j < muestras[i].size(); j++)
                {
                    //la muestra coincide con su maquina
                    if(calcularOffset(muestras.size(), i, offset) == muestras[i][j])
                    {
                        yaAnalizado[i] = true;
                        break;
                    }
                }
            }
            //si sigue sin analizar luego de haber comprobado...
            if(!yaAnalizado[i]) muestrasRestantes++;
        }

        //TERMINAMOS
        if(muestrasRestantes == 0)
        {
            while(!cola.empty()) {cola.pop();}; //borra la cola
        } else {
            prox[0] = new Arbol(yaAnalizado, pasosTotales+1, offset+1); cola.push(prox[0]); //izquierda
            prox[1] = new Arbol(yaAnalizado, pasosTotales+1, offset-1); cola.push(prox[1]); //derecha
        }
        return pasosTotales;
    }

    int calcularOffset(int size, int i, int offset)
    {
        int resultado = i;

        while(offset != 0)
        {
            if(offset >= 0)
            {
                resultado = (resultado != size - 1 ? resultado+1 : 0); //suma 1 o resetea a 0 si es el ultimo
                offset--;
            }
            else if(offset <= 0 )
            {
                resultado = (resultado != 0 ? resultado-1 : size - 1); //resta 1 o resetea al ultimo si es 0
                offset++;
            }
        }
        return resultado;
    }
};




int analizar(vector<vector<int> > &muestras)
{
    std::queue<Arbol*> cola; //para realizar bfs
    int movimientosTotales;

    vector<bool> primerosAnalisis(muestras.size(), false);
    Arbol *raiz = new Arbol(primerosAnalisis, 0, 0);
    cola.push(raiz);

    while (!cola.empty())
    {
        Arbol* nodoARevisar = cola.front(); cola.pop();
        movimientosTotales = nodoARevisar->realizarMovimiento(muestras, cola);
    }

    delete raiz;
    return movimientosTotales;
}

int main()
{
    vector<vector<int> > M = { {4}, {2}, {3}, {2,1,0,3,4}, {4,0} };
    std::cout << "movimientos: " << analizar(M);
}
