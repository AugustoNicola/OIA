#include <vector>
#include <utility>

using namespace std;

double mod(double z)
{
	return (z >= 0 ? z : -z);
}

vector<double> apuesta(vector<int> &x, vector<int> &y)
{
	pair<double, double> vec1 = {mod(x[0] - x[1]), mod(y[0] - y[1])};
	pair<double, double> vec2 = {mod(x[1] - x[2]), mod(y[1] - y[2])};

	bool lineaVertical = false;
	bool esLinea = false;

	if(vec1.first == 0 or vec2.first == 0)
	{
		if(vec1.first == 0 and vec2.first == 0)
		{
			lineaVertical = true;
			esLinea = true;
		}
	} else {
		esLinea = mod(vec1.second / vec1.first) == mod(vec2.second / vec2.first);
	}

    vector<double> respuesta = {};
	if(esLinea)
	{
		if(lineaVertical)
		{
			if((y[0] < y[1] && y[0] > y[2]) or (y[0] < y[2] && y[0] > y[1])) respuesta = {(double)x[0], (double)y[0]};
			if((y[1] < y[0] && y[1] > y[2]) or (y[1] < y[2] && y[1] > y[0])) respuesta = {(double)x[1], (double)y[1]};
			if((y[2] < y[0] && y[2] > y[1]) or (y[2] < y[1] && y[2] > y[0])) respuesta = {(double)x[2], (double)y[2]};
		} else {
			if((x[0] < x[1] && x[0] > x[2]) or (x[0] < x[2] && x[0] > x[1])) respuesta = {(double)x[0], (double)y[0]};
			if((x[1] < x[0] && x[1] > x[2]) or (x[1] < x[2] && x[1] > x[0])) respuesta = {(double)x[1], (double)y[1]};
			if((x[2] < x[0] && x[2] > x[1]) or (x[2] < x[1] && x[2] > x[0])) respuesta = {(double)x[2], (double)y[2]};
		}
	}

	return respuesta;
}
