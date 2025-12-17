// Lab_9_1.cpp
#include <iostream>
#include <iomanip> // Для форматованого виводу
#include <cmath>
#include "dod.h"
#include "sum.h"
#include "var.h"

using namespace std;
using namespace nsDod;
using namespace nsSum;
using namespace nsVar;

int main() {
    
    // Область визначення |x| < 1
    cout << "Enter x_p (|x| < 1): "; cin >> x_p;
    cout << "Enter x_k (|x| < 1): "; cin >> x_k;
    cout << "Enter dx: "; cin >> dx;
    cout << "Enter e (precision): "; cin >> e;

    cout << endl;
    cout << fixed << setprecision(5);
    cout << "-------------------------------------------------" << endl;
    cout << setw(8) << "x" << setw(12) << "Sum(x)" << setw(15) << "Exact ln()" << setw(8) << "n" << endl;
    cout << "-------------------------------------------------" << endl;

    x = x_p;
    while (x <= x_k + e / 2) { // +e/2 для коректного порівняння float
        if (fabs(x) >= 1) {
            cout << setw(8) << x << "  Argument out of domain (|x|<1)" << endl;
        }
        else {
            sum(); // виклик процедури обчислення суми

            // Точне значення для перевірки: ln((1+x)/(1-x))
            double exact = log((1 + x) / (1 - x));

            cout << setw(8) << x
                << setw(12) << s
                << setw(15) << exact
                << setw(8) << n << endl;
        }
        x += dx;
    }

    cin.get();
    cin.get();
    return 0;
}