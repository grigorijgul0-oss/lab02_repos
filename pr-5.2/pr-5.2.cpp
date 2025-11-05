#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std;


double S(const double x, const double eps, int& n);
double A(const double x, const int n, double a);

int main()
{
    double xp, xk, x, dx, eps;
    int n = 0; 

    cout << "xp = "; cin >> xp;
    cout << "xk = "; cin >> xk;

    
    if (xp <= -1 || xk >= 1 || xp > xk) {
        cout << "error" << endl;
        return 1;
    }

    cout << "dx = "; cin >> dx;
    cout << "eps = "; cin >> eps;
    cout << fixed;
    cout << "-------------------------------------------------" << endl;
    cout << "|" << setw(7) << "x" << " |"
        << setw(13) << "ln((1+x)/(1-x))" << " |" 
        << setw(10) << "S" << " |"
        << setw(5) << "n" << "    |"
        << endl;
    cout << "-------------------------------------------------" << endl;

    x = xp;
    while (x <= xk)
    {
        
        double s = S(x, eps, n);

       
        double y = log((1.0 + x) / (1.0 - x));

        cout << "|" << setw(7) << setprecision(2) << x << " |"
            << setw(13) << setprecision(5) << y << "   |" 
            << setw(10) << setprecision(5) << s << " |"
            << setw(5) << n << "    |"
            << endl;
        x += dx;
    }
    cout << "-------------------------------------------------" << endl;
    return 0;
}


double S(const double x, const double eps, int& n)
{
    n = 0;

  
    double a = 2 * x;
    double s = a;

    do {
        n++; 
        a = A(x, n, a); 
        s += a; 
    } while (abs(a) >= eps);

    return s;
}


double A(const double x, const int n, double a)
{
    double R = (x * x) * (2.0 * n - 1.0) / (2.0 * n + 1.0);
    a *= R;
    return a;
}
