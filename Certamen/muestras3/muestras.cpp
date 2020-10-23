#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Arbol
{
public:
    int offset, pasosTotales, muestrasRestantes;
    vector<bool> yaAnalizado;

    Arbol* prox[2];
    Arbol* padre;

    Arbol(Arbol* papa, vector<bool>& analisisPrevios, int pT, int off) : padre(papa), yaAnalizado(analisisPrevios), pasosTotales(pT), offset(off) {prox[0] = nullptr; prox[1] = nullptr;}
    ~Arbol(){delete prox[0]; delete prox[1];}

    int realizarMovimiento(vector<vector<int> >& muestras, std::queue<Arbol*>& cola)
    {
        muestrasRestantes = 0;
        if(padre == nullptr or abs(padre->offset - offset) != 0)
        {
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
            
        } else {muestrasRestantes = padre->muestrasRestantes;}
        //TERMINAMOS
        if(muestrasRestantes != 0)
        {
            prox[0] = new Arbol(this, yaAnalizado, pasosTotales+1, offset+1); cola.push(prox[0]); //izquierda
            prox[1] = new Arbol(this, yaAnalizado, pasosTotales+1, offset-1); cola.push(prox[1]); //derecha
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
    Arbol *raiz = new Arbol(nullptr, primerosAnalisis, 0, 0);
    cola.push(raiz);

    while (!cola.empty())
    {
        Arbol* nodoARevisar = cola.front(); cola.pop();
        movimientosTotales = nodoARevisar->realizarMovimiento(muestras, cola);
        if(nodoARevisar->muestrasRestantes == 0) break;
    }
    
    //delete raiz;
    return movimientosTotales;
}

int main()
{
    vector<vector<int> > M = { 

        {0, 3},
        {0, 2},
        {2, 3},
        {5, 10},
        {7, 8},
        {6, 7, 8},
        {1, 18},
        {17, 5},
        {3, 17},
        {1, 2, 3},
        {5, 9, 13},
        {16, 17, 5},
        {2, 18, 3},
        {1, 7, 17},
        {5, 7, 18},
        {2, 9, 15},
        {16, 17},
        {5},
        {7, 18},
        {1},
        {0, 3},
        {0, 2},
        {2, 3},
        {5, 10},
        {7, 8},
        {6, 7, 8},
        {1, 18},
        {17, 5},
        {3, 17},
        {1, 2, 3},
        {5, 9, 13},
        {16, 17, 5},
        {2, 18, 3},
        {1, 7, 17},
        {5, 7, 18},
        {2, 9, 15},
        {16, 17},
        {5},
        {7, 18},
        {1},
        {0, 3},
        {0, 2},
        {2, 3},
        {5, 10},
        {7, 8},
        {6, 7, 8},
        {1, 18},
        {17, 5},
        {3, 17},
        {1, 2, 3},
        {5, 9, 13},
        {16, 17, 5},
        {2, 18, 3},
        {1, 7, 17},
        {5, 7, 18},
        {2, 9, 15},
        {16, 17},
        {5},
        {7, 18},
        {1}
     };
    std::cout << "movimientos: " << analizar(M);
}
