#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    double xp, xk, x, dx, eps, a = 0, R = 0, S = 0;
    int n = 0;

    cout << "xp = "; cin >> xp;
    cout << "xk = "; cin >> xk;
    cout << "dx = "; cin >> dx;
    cout << "eps = "; cin >> eps;

    cout << fixed;
    cout << "---------------------------------------------------" << endl;
    cout << "|" << setw(7) << "x" << " |"
        << setw(15) << "ln((1+x)/(1-x))" << " |"
        << setw(15) << "S" << " |"
        << setw(5) << "n" << " |" << endl;
    cout << "---------------------------------------------------" << endl;

    x = xp;
    while (x <= xk)
    {
        if (fabs(x) >= 1.0)
        {
            cout << "|" << setw(7) << setprecision(2) << x << " |"
                << setw(15) << " |x|>=1 " << " |"
                << setw(15) << "-----" << " |"
                << setw(5) << "-" << " |" << endl;
            x += dx;
            continue;
        }

        n = 0;
        a = 2 * x;  
        S = a;

        do {
            n++;
            R = x * x * ((2.0 * n - 1) / (2.0 * n + 1));
            a *= R;
            S += a;
        } while (fabs(a) >= eps);

        cout << "|" << setw(7)  << setprecision(2) << x                      << " |"
                    << setw(15) << setprecision(8) << log((1 + x) / (1 - x)) << " |"
                    << setw(15) << setprecision(8) << S                      << " |"
                    << setw(5)  <<               n                           << " |" 
                    << endl;

        x += dx;
    }

    cout << "---------------------------------------------------" << endl;
    return 0;
}
