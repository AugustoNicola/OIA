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
			int wRestante = W;
			int hRestante = H;
			do
			{
				wRestante -= w[t];
				hRestante -= h[t];
			areaDesperdicio = min(
				calcularDesperdicio(wRestante, H - hRestante, w,h) +
				calcularDesperdicio(W - wRestante, hRestante, w,h) +
				calcularDesperdicio(wRestante, hRestante, w,h), 
				areaDesperdicio);

			}while(wRestante >= w[t] && hRestante >= h[t]);
		}
	}
	return areaDesperdicio;
}


int barbijos(int W,int H, vector<int> &w, vector<int> &h) {
	return calcularDesperdicio(W, H, w, h);
}
