#include <string>
#include <vector>
#include <iostream>
 
using namespace std;
 
int analizar(vector<vector<int>> &muestras) {
    int n = (int)muestras.size();
    vector<int> minLeft(n, n + 1);
    vector<int> minRight(n, n + 1);
    vector<int> leftAmount(n, 0);
    vector<int> rightAmount(n, 0);
 
    for (int i = 0; i < n; i++) {
        for (auto a : muestras[i]) {
            minLeft[i] = min(minLeft[i], (i - a + n) % n); //siempre guarda la maquina a menor distancia si se mueve hacia la izquierda
            minRight[i] = min(minRight[i], (a - i + n) % n); //siempre guarda la maquina a menor distancia si se mueve hacia la derecha
        }
        leftAmount[minLeft[i]]++;
        rightAmount[minRight[i]]++;
    }
 
    vector<int> maxLeft(n, 0);
    vector<int> maxRight(n, 0);
    maxLeft[0] = 0;
    maxRight[0] = 0;
    for (int i = 1; i < n; i++) {
        if (leftAmount[i] > 0) maxLeft[i] = i;
        else maxLeft[i] = maxLeft[i - 1];
        if (rightAmount[i] > 0) maxRight[i] = i;
        else maxRight[i] = maxRight[i - 1];
    }
 
    vector<int> turns(n);
    for (int i = 0; i < n; i++) {
        int a = maxLeft[i];
        int b = maxRight[n - i - 1];
        turns[i] = min(2 * a + b, a + 2 * b);
    }
 
    int ans = n + 1;
    for (auto a : turns) ans = min(ans, a);
    return ans;
}

int main()
{
    vector<vector<int> > M = { {4}, {2}, {3}, {2,1,0,3,4}, {4,0}, {5} };
    cout << "movimientos: " << analizar(M);
}