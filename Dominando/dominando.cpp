#include <string>
#include <vector>
#include <iostream>

std::vector<int> dominando(std::string n, int d, std::vector<int> t, std::vector<int> a, std::vector<int> b)
{
	int q = t.size();
	std::vector<int> r;

	for(unsigned int i = 0; i < q; i++)
	{
		if(t[i] == 0)
		{
			int subNumero = std::stoi(n.substr(a[i] - 1, b[i] - a[i] + 1));
			r.push_back(subNumero % d);
		}
		if(t[i] == 1)
		{
			n.replace(a[i] - 1, 1, std::to_string(b[i]));
		}
	}

	return r;
}

int main()
{
	std::vector<int> t = {0, 1, 0, 1, 0, 0}, a = {1, 4, 5, 1, 1, 1}, b = {6, 3, 6, 4, 3, 6};
	std::vector<int> respuestas = dominando("123456", 100, t, a, b);
	for(int r : respuestas) std::cout << r << std::endl;
	return 0;
}