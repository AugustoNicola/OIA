#include <bits/stdc++.h>
using namespace std;

#define dforsn(i,s,n) for(int i=int(n-1);i>=int(s);i--)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforn(i,n) for(int i=int(n-1);i>=0;i--)
#define forn(i,n) for(int i=0;i<int(n);i++)
#define D(a) cerr << #a << " = " << a << endl
#define all(a) a.begin(),a.end()
#define si(a) int((a).size())
typedef pair<int,int> pii;
typedef long long int ll;
typedef vector<int> vi;
#define pb emplace_back
#define mp make_pair
#define snd second
#define fst first

int n;
string a;
vector<vi> dp;

int go(int i, int j) {

	// CASOS ESPECIALES

    if (i == -1 && j == n) return 0; // alcanzados extremos de la palabra exitosamente
    if (i == -1) return n-j; // todo alcanzado extremo izquierdo
    if (j == n) return i+1; // todo alcanzado extremo derecho

	// FUNCIONAMIENTO NORMAL

    int &x = dp[i][j];
    if (x != -1) return x; // valor ya calculado

	//CALCULO DE VALOR DE CASILLA

    if (a[i] == a[j]) x = go(i-1, j+1); // si los valores son palindromos actualiza la casilla con el valor de la funcion alejandose
    else x = 1 + min(go(i-1, j), go(i, j+1)); //sino, actualiza con el mejor entre ir hacia un lado o hacia el otro + 1 de esta adicion
    return x; //devuelve el valor de la casilla
}

int nivelacion(string s) {
    a = s, n = si(s);
    dp = vector<vi>(n, vi(n));
    forn(i, n) forn(j, n) dp[i][j] = -1;
    int ans = n-1;
    forn(i, n-1) 
        ans = min(ans, min(go(i, i), go(i, i+1)));
    return ans;
}

int main()
{
	int respuesta = nivelacion("an");
	return 0;
}
