// Lab 5_1
#include <iostream>
#include <cmath>

using namespace std;

double h(const double s, const double t); // прототип

int main()
{
	double a, b;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	double c = (a / (pow(b, 2) + 1)) + (1 / pow(a, 2) + pow(a, 2));
	cout << "c = " << c << endl;
	return 0;
}
double h(const double s, const double t) // визначення
{
	return (pow(h(s, t), 4) + h(1, pow(s, 2) + pow(t, 2))) / (1 + pow(h(s * t, 1), 2));
}
