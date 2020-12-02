#include <iostream>
#include <string>
#include <vector>

using namespace std;

int analizar(vector<vector<int> > &muestras);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int> > muestras;
    muestras.resize(n);
    for (int i0 = 0; i0 < n; i0++) {
        int auxSize1;
        cin >> auxSize1;
        muestras[i0].resize(auxSize1);
        for (int i1 = 0; i1 < auxSize1; i1++) {
            cin >> muestras[i0][i1];
        }
    }
    int returnedValue;
    returnedValue = analizar(muestras);
    cout << returnedValue << "\n";
    return 0;
}
