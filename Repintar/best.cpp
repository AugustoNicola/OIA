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
const string C = "RAV";
int n, p, node[N][N];
char t[N][N], col[R];
bool g[R][R];
ll done;

map<ll, int> dp;
map<ll, pair<ll, char>> nxt;

int f(ll s) {
    if (s == done) return 0;
    if (dp.count(s)) return dp[s];

    int b = n; ll bs; char bc; 
    for (char c : C) {
        ll ns = s;
        forn(i, n) if (!(s & (1LL << i)) && col[i] == c)
            forn(j, n) if (s & (1LL << j) && g[i][j])
                { ns |= 1LL << i; break; }

        if (ns != s) {
            int x = 1 + f(ns); 
            if (x < b) b = x, bs = ns, bc = c;
        }
    }
    nxt[s] = {bs, bc};
    return dp[s] = b;
}

bool fill(int x, int y) {
    if (node[x][y] != -1) return false; //si node ya no es -1 devuelve false
    char c = t[x][y]; // recupera el color
    node[x][y] = p, col[p] = c; // * p va aumentando cada vez que la funcion devuelve true
	//? col es el color de cada region?
    if (x > 0 && t[x-1][y] == c) fill(x-1, y);
    if (y > 0 && t[x][y-1] == c) fill(x, y-1);
    if (x+1 < n && t[x+1][y] == c) fill(x+1, y);
    if (y+1 < n && t[x][y+1] == c) fill(x, y+1);
    return true;
}

void build(int x, int y) {
    int u = node[x][y];
    char c = t[x][y];
    if (x+1 < n && t[x+1][y] != c) {
        int v = node[x+1][y];
        g[u][v] = g[v][u] = true;
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
    forn(i, n) forn(j, n) cin >> t[i][j]; // t guarda los colores

    forn(i, n) forn(j, n) node[i][j] = -1; // inicializa node a -1
    forn(i, n) forn(j, n) if (fill(i, j)) p++;
    forn(i, n) forn(j, n) build(i, j);

    n = p, done = (1LL << n) - 1;
    cout << f(1) << endl;
    ll c = 1;
    while (c != done) {
        auto x = nxt[c];
        cout << x.snd;
        c = x.fst;
    }
    cout << endl;
    return 0;
}
