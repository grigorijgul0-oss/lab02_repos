#include <iostream>
#include <iomanip>
#include <cmath> 
using namespace std;


double h(double x);
double calculate_sum(double x);
double Y(double r);

int main()
{
    double r_p, r_k, dr, r, y_val;
    int n; 

    
    cout << "r_p= "; cin >> r_p;
    cout << "r_k="; cin >> r_k;
    cout << "n: "; cin >> n;
    dr = (r_k - r_p) / n;

    cout << fixed << setprecision(7); 
    cout << "----------------------------------------\n";
    cout << "|" << setw(15) << "r" << " |"
        << setw(20) << "Y(r)" << " |" << endl;
    cout << "----------------------------------------\n";

   
    for (int i = 0; i <= n; i++)
    {
        r = r_p + i * dr; 
        y_val = Y(r);

        
        cout << "|" << setw(15) << r << " |"
            << setw(20) << y_val << " |" << endl;
    }

    
    cout << "----------------------------------------\n";

    return 0;
}

double Y(double r)
{
    double h1 = h(r + 1.0);
    double h2 = h(r * r + 1.0);
    return h1 + (h2 * h2) + 1.0;
}
double h(double x)
{
  
    if (abs(x) < 1e-9)
    {
        return 1.0;
    }
    if (abs(x) >= 1.0)
    {
        return (cos(x) + 1.0) / exp(x);
    }
    else
    {
        double sum = calculate_sum(x);
        return (1.0 / sin(x * x)) * sum;
    }
}


double calculate_sum(double x)
{
    double a = x * x;
    double S = a;

    for (int n = 1; n <= 6; n++)
    {
        double R = (x * x * x * x) / ((2.0 * n) * (2.0 * n + 1.0));

        a *= R;

        S += a;
    }

    return S;
}