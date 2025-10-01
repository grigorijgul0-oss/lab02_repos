#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int i;
	double P;
	P = 1;
	i = 1;
	while (i <= 15)
	{
		double numerator = pow(sin(i), 2) + pow(cos(1.0 / i), 2);
		double denominator = pow(i, 2);
		P *= numerator / denominator;
		i++;
	}
	cout << P << endl;
	P = 1;
	i = 1;
	do {
		P *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / pow(i, 2);
		i++;
	} while (i <= 15);
	cout << P << endl;
	P = 1;
	for (i = 1; i <= 15; i++)
	{
		P *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / pow(i, 2);
	}
	cout << P << endl;
	P = 1;
	for (i = 15; i >= 1; i--)
	{
		P *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / pow(i, 2);
	}
	cout << P << endl;
	return 0;
}