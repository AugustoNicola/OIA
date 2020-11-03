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

const int N = 4;
int v[N]; // ? capacidades de los tannques
int r[N]; // ? total minimo necesario para llegar hasta esta cantidad de tanques, acumula ya que elige el upper_bound()
int p;    // ? aumentador de cantidad de tanques
int s;    // ? volumen total acumulado hasta el momento
vector<pii> g[N]; // ? tuberias de cada tanque

void dfs(int u=0){
	std::cout << "\n ----- P: " << p << " -----";
	std::cout << "\nS: " << s << std::endl;
r[p++] = s+1; //* para llegar a este tanque se necesitan los litros de las llamadas anteriores mas uno
    int c = 0; //? diferencial total de este tanque (que ya se lleno)
    for(auto &i:g[u]){ //* para todas las tuberias desde la mas abajo:
		// ? cuantos litros necesito para alcanzar esta tuberia desde donde estaba, y ademas llama a la funcion en esa tuberia
		std::cout << "\n ### P: " << p << " ###";
		std::cout << "#CMB: " << i.second << " (distancia " << i.first << ")" << std::endl;
        int dif = v[u]-i.fst-c; //* calcula lo que se aniade con esta nueva tuberia; es decir la capacidad del tanque menos la distancia hasta la tuberia menos lo ya restado
		std::cout << "diferencia: " << dif << std::endl;
        c += dif; //* suma al total de esta llamada para calcular bien lo que se aumenta en cada una
		s += dif; //* suma los litros que se aniadieron para poder llegar hasta aca
		std::cout << "C: " << c << std::endl << "S: " << s << std::endl;
        dfs(i.snd); //* vuelve a llamar a la funcion con el nuevo tanque
    }
	std::cout << "~~~~~ TERMINAN CONEXIONES DE " << p - 1<< " ~~~~~" << std::endl;
    s += v[u]-c; //* si no quedan mas tuberias (porque no hay o porque ya se usaron), se termina de llenar el tanque
	std::cout << "nueva S: " << s << std::endl << std::endl;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int n; cin >> n;
    forn(i,n) cin >> v[i]; //guarda las capacidades
    forn(i,n-1){
        int x,d,y; cin >> x >> d >> y;
        g[x-1].pb(d,y-1); //guarda las tuberias
    }
    forn(i,n) sort(all(g[i]),greater<pii>()); //ordena las tuberias para que las mas bajas queden primero
    dfs(); //FUNCION RECURSIVA CON u=0

    int q; cin >> q;
    forn(i,q){
        int x; cin >> x;
        std::cout << "\nr: " << r << " (" << *r << ")" << std::endl;
		std::cout << "upper: " << upper_bound(r,r+n,x) << " (" << *upper_bound(r,r+n,x) << ")" << std::endl;
        std::cout << "menos r: respuesta final:" << upper_bound(r,r+n,x)-r << std::endl; //! wtf
    }
    cout << endl;
    return 0;
}
