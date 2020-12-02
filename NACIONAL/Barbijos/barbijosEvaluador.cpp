#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int calcularDesperdicio(int W,int H, vector<int> &w, vector<int> &h)
{
	if(W == 0 or H == 0) return 0;

	int areaDesperdicio = W*H;

	for(int t = 0; t < w.size(); t++)
	{
		if(w[t] <= W && h[t] <= H)
		{
			int wRestante = W % w[t];
			int hRestante = H % h[t];

			areaDesperdicio = min(
				calcularDesperdicio(wRestante, H - hRestante, w,h) +
				calcularDesperdicio(W - wRestante, hRestante, w,h) +
				calcularDesperdicio(wRestante, hRestante, w,h), 
				areaDesperdicio);
		}
	}
	return areaDesperdicio;
}


int barbijos(int W,int H, vector<int> &w, vector<int> &h) {
	return calcularDesperdicio(W, H, w, h);
}

int main() {
	ifstream input; input.open("0.in");

    int W;
    input >> W;
    int H;
    input >> H;
    int t;
    input >> t;
    vector<int> w;
    vector<int> h;
    w.resize(t);
    h.resize(t);
    for (int i = 0; i < t; i++) {
        input >> w[i];
        input >> h[i];
    }
	input.close();
    int returnedValue;
    returnedValue = barbijos(W,H,w,h);
    cout << returnedValue << "\n";
    return 0;
}
