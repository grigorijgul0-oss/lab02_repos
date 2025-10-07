// Lab_04_4.cpp
// < Гуль Григорій Олександрович>
// Лабораторна робота № 4.4
// Табуляція функції, заданої графіком.
// Варіант 5
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	double x, xp, xk, dx, R, y;
	cout << "R = "; cin >> R;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;
	cout << fixed;
	
	cout << "---------------------------" << endl;
	cout << "|" << setw(5) << "x" << " |"
		<< setw(7) << "y" << " |" << endl;
	cout << "---------------------------" << endl;


	x = xp;
	while (x <= xk)
	{
		if (-4 <= x && x <= -2)
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
		cout << "|" << setw(7) << setprecision(2) << x
			 << "   |" << setw(10) << setprecision(3) << y
			 << "    |" << endl;
		x += dx;
	}
	cout << "---------------------------" << endl;
	return 0;
}
