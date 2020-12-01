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

const int N = 2e3, R = 50;
const string C = "RAV"; //colores posibles
int n; // primero guarda tamanio de grilla, pero luego cambia a cantidad de regiones (linea 103)
int p; //p aumenta cada vez que se sale de la recursion (es decir una vez x region)
int node[N][N]; //la region a la que pertenece cada nodo

char t[N][N]; // t guarda los colores
char col[R]; // guarda el color de cada region

bool g[R][R]; // guarda la adyacencia entre las regiones

ll done; // mascara final con todos los bits de cada region seteados

map<ll, int> dp; // ll: mascara de regiones donde cada bit indica si esa region ya fue aniadida a la region final // int: cantidad total de pintadas para resolver el problema
map<ll, pair<ll, char>> nxt; // mapa que seniala hacia el proximo mejor estado (con su pintada necesaria) desde el estado actual, usado para seguir el hilo de la respuesta final

// analiza el estado actual de regionees aniadidas y no aniadidas e intenta (segun pintar por cada color) elegir la mejor solucion de ese subproblema (usa DP recursiva)
int f(ll s) {
    if (s == done) return 0; //si todas las regiones estan seteadas no hay que hacer nada
    if (dp.count(s)) return dp[s]; //si la mascara ya se encuentra en el dp la devuelve

    int b = n; // b es el maximo de movimientos hasta el momento (empieza en n nunca puede haber mas de n movimientos...)
	ll bs; // mejor proximo paso hasta el momento
	char bc; // mejor proximo movimiento hasta el momento

	//para cada color:
    for (char c : C) {
        ll ns = s; //crea una copia de la mascara
		// busca regiones no seteadas del color que se esta intentando
        forn(i, n) if (!(s & (1LL << i)) && col[i] == c) 
            // para cada region no seteada busca adyacencia con una seteada
			forn(j, n) if (s & (1LL << j) && g[i][j]) 
                { ns |= 1LL << i; break; } // setea bit de la region i (nueva) y sale del loop j (sigue buscando otras conexiones)

        if (ns != s) { //si se hicieron cambios con este color:
            int x = 1 + f(ns); //aumenta en uno los movimientos y hace recursion con esta nueva mascara
            if (x < b) b = x, bs = ns, bc = c; // si esta nueva ruta es mas optima, sobreescribe pintadas totales, proximo paso (mascara) y proximo color con este mejor resultado
        }
    }
    nxt[s] = {bs, bc}; //guarda la solucion asociada con este estado
    return dp[s] = b; //guarda la cantidad de movimientos asociada con este estado
}

//encuentra la region de este nodo si no fue visitado
bool fill(int x, int y) {
    if (node[x][y] != -1) return false; //si node ya no es -1 devuelve false
    char c = t[x][y]; // recupera el color
    node[x][y] = p, col[p] = c; //setea el color y el id de la region

	// INTENTA BUSCAR ADYACENCIAS SI EL COLOR ES EL MISMO
    if (x > 0 && t[x-1][y] == c) fill(x-1, y);
    if (y > 0 && t[x][y-1] == c) fill(x, y-1);
    if (x+1 < n && t[x+1][y] == c) fill(x+1, y);
    if (y+1 < n && t[x][y+1] == c) fill(x, y+1);
    return true;
}

// le asigna al nodo su region correspondiente
void build(int x, int y) {
    int u = node[x][y]; //u es la region del nodo
    char c = t[x][y]; //c es el color del nodo
    if (x+1 < n && t[x+1][y] != c) { //si el color del nodo siguiente no es el mismo:
        int v = node[x+1][y]; //v es la region del nodo siguiente
        g[u][v] = g[v][u] = true; // guarda que las regiones son adyacentes
    }
    if (y+1 < n && t[x][y+1] != c) {
        int v = node[x][y+1];
        g[u][v] = g[v][u] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    freopen("repintar.in", "r", stdin);
    freopen("repintar.out", "w", stdout);

    cin >> n;
    forn(i, n) forn(j, n) cin >> t[i][j]; // guarda los colores

    forn(i, n) forn(j, n) node[i][j] = -1; // inicializa node a -1
    forn(i, n) forn(j, n) if (fill(i, j)) p++; // analiza la pertenencia a regiones y el color de cada region
    forn(i, n) forn(j, n) build(i, j); // analiza las adyacencias de regiones

    n = p; // guarda la cantidad de regiones (ahorro innecesario?)
	done = (1LL << n) - 1; //configura la mascara done para que tenga todas las regiones seteadas
	
    cout << f(1) << endl; // comienza con la primera region seteada: lo que se imprime es el b del estado inicial

    ll c = 1; // comienza con la posicion inicial
    // mientras no se haya llegado al estado final:
	while (c != done) {
        auto x = nxt[c]; //recupera el par asociado con esta mascara
        cout << x.snd; //imprime el color pintado
        c = x.fst; //pasa al proximo paso
    }
    cout << endl;
    return 0;
}
