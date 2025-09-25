

// Lab_02.1.cpp
// < Гуль Григорій>
// Лабораторна робота № 2.
// Лінійні програми.
// Варіант 5
#include <iostream>
#include <cmath>

using namespace std;
int main()
{
	double m; // вхідний параметр
	double z1; // результат обчислення 1-го виразу
	double z2; // результат обчислення 2-го виразу
	cout << "m = "; cin >> m;
	z1 = 1-(0.25*(sin(2*m)*sin(2*m)))+cos(2*m);
	z2 = pow(cos(m),2) + pow(cos(m), 4);
	cout << endl;
	cout << "z1 = " << z1 << endl;
	cout << "z2 = " << z2 << endl;
	cin.get();
	return 0;
}
