#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long camas(vector<int> &p, vector<int> &c, vector<int> &a, vector<int> &b, vector<int> &l);

vector<int> evaluadorLlamadaAsignarPaciente;
vector<int> evaluadorLlamadaAsignarCama;

void asignar(int puebloPaciente, int puebloCama)
{
    evaluadorLlamadaAsignarPaciente.push_back(puebloPaciente);
    evaluadorLlamadaAsignarCama.push_back(puebloCama);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> p;
    vector<int> c;
    p.resize(N);
    c.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        cin >> c[i];
    }
    vector<int> a;
    vector<int> b;
    vector<int> l;
    a.resize(N-1);
    b.resize(N-1);
    l.resize(N-1);
    for (int i = 0; i < N-1; i++) {
        cin >> a[i];
        cin >> b[i];
        cin >> l[i];
    }
    long long returnedValue;
    returnedValue = camas(p, c, a, b, l);
    cout << returnedValue << "\n";
    for (int i=0; i < int(evaluadorLlamadaAsignarPaciente.size()); i++)
        cout << evaluadorLlamadaAsignarPaciente[i] << " " << evaluadorLlamadaAsignarCama[i] << "\n";
    return 0;
}
