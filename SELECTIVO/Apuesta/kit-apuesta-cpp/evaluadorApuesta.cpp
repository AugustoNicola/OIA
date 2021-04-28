#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<double> apuesta(vector<int> &x, vector<int> &y);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i=0; i<N; i++)
        cin >> x[i] >> y[i];
    vector<double> ret = apuesta(x,y);
    if (ret.empty())
        cout << "VACIO\n";
    else
    {
        bool pri = true;
        for (double value : ret)
        {
            if (pri)
                pri = false;
            else
                cout << " ";
            cout << fixed << setprecision(4) << value;
        }
        cout << "\n";
    }
    return 0;
}
