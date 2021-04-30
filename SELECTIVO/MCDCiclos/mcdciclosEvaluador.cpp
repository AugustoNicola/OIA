#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mcdciclos(int N, vector<int> &a, vector<int> &b);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    int m;
    cin >> m;
    vector<int> a;
    vector<int> b;
    a.resize(m);
    b.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        cin >> b[i];
    }
    int returnedValue;
    returnedValue = mcdciclos(N, a, b);
    cout << returnedValue << "\n";
    return 0;
}
