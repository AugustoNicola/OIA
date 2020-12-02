#include <string>
#include <vector>

using namespace std;

vector<int> tutubo(vector<int> &siguiente, vector<int> &preguntaX, vector<long long> &preguntaK)
{
    int N = siguiente.size();
    vector<long long> ciclo(N, 0);

    int video; long long cont;
    //para cada video
    for(int i = 0; i < N; i++)
    {
        video = i;
        //maximo de iteraciones
        for(int j = 1; j <= N; j++)
        {
            video = siguiente[video];
            if(video == i) {ciclo[i] = j; break;}
        }
    }

    vector<int> respuestas;

    long long Q = preguntaX.size();
    for(int q = 0; q < Q; q++)
    {
        long long operRest = preguntaK[q];
        int videoActual = preguntaX[q];
        while(operRest > 0)
        {
            if(ciclo[videoActual] && operRest >= ciclo[videoActual])
            {
                operRest %= ciclo[videoActual];
            }
            if(operRest > 0) 
            {
                videoActual = siguiente[videoActual];
                operRest--;
            }
        }
        respuestas.push_back(videoActual);
    }
    return respuestas;
}
