#include <string>
#include <vector>
#include <iostream>
 
using namespace std;
 
const int INF = 1e9;
 
int di[] = {-1, 0, 1};
 
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> mercado(n);
    for (int i = 0; i < n; i++) cin >> mercado[i];
 
    vector<vector<int>> puntaje(n, vector<int>(m, -INF));
    for (int i = 0; i < n; i++) if (mercado[i][0] == 'A') puntaje[i][0] = 0;
 

    for (int j = 0; j < m - 1; j++) {

        for (int i = 0; i < n; i++) {
            //itera entre -1 0 +1 para setear x
            for (int k = 0; k < 3; k++) {
                int x = i + di[k]; // x es i +-1
                if (x < 0 || x >= n) continue; //fuera de rango
                //la columna siempre se mueve uno para adelante, x es diagonales & medio
                //puntaje de esa posicion corrida es eñ maximo dee si misma o Esta + uno si hay joya
                puntaje[x][j + 1] = max(
                    puntaje[x][j + 1],
                    puntaje[i][j] + (mercado[x][j + 1] == 'J')
                );
                if (mercado[x][j + 1] == 'M') {
                    if (puntaje[x][j + 1] > 0) puntaje[x][j + 1] = 0;
                    else puntaje[x][j + 1] = -INF;
                }
            }
        }
    }
 
    int ans = -INF;
    for (int i = 0; i < n; i++) ans = max(ans, puntaje[i][m - 1]);
 
    /* Show entire matrix for debugging
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (puntaje[i][j] < 0) cout << -1 << " ";
            else cout << puntaje[i][j] << " ";
        }
        cout << '\n';
    }
    */
 
    if (ans < 0) cout << "SIN SALIDA\n";
    else cout << ans << '\n';
}