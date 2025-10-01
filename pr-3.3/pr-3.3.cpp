// Lab_03_3.cpp
// < прізвище, ім’я автора >
// Лабораторна робота № 3.3
// Розгалуження, задане графіком функції.
// Варіант 5
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double x; // вхідний аргумент
	double R; // вхідний параметр
	double y; // результат обчислення виразу
	cout << "R = "; cin >> R;
	cout << "x = "; cin >> x;

	// розгалуження в повній формі
	if ( -4 <= x && x <= -2)
		y = 1. / 2. + 3, 5;
	else
		if (-2 <= x && x <= 4)
			y = (6 + (R * x - x) + (-2 * R - 2)) / 6;
		else
			if (4 <= x && x <= 8 - R)
				y = -R;
			else
				if (8 - R < x && x <= 8)
					y = -R + sqrt(R * R - (pow(x, 2) - 8));
				else
					if (8 <= x && x <= 8 + R)
						y = -R + sqrt(R * R - (pow(x, 2) - 8));
					else
						if (8 + R <= x)
							y = -R;
					     
	cout << endl;
	cout << "y = " << y << endl;
	cin.get();
	return 0;
}
