#include <iostream>
#include <algorithm>
using namespace std;



long long Q(int m, int n, int depth, int& maxDepth)
{

    if (depth > maxDepth)
        maxDepth = depth;

    
    if (m == 0) return 1;          
    if (n == 0 || m < 0) return 0; 
    if (m == 1 || n == 1) return 1;

    
    if (m < n)
        return Q(m, m, depth + 1, maxDepth);

    if (m == n)
        return 1 + Q(m, n - 1, depth + 1, maxDepth);

    return Q(m, n - 1, depth + 1, maxDepth) + Q(m - n, n, depth + 1, maxDepth);
}

int main()
{
    int m, n;;
    cout << "m="; cin >> m;
    cout << "n="; cin >> n;

    int maxDepth = 0; 
    long long result = Q(m, n, 1, maxDepth);

    cout << "Q(" << m << "," << n << ") = " << result << endl;
    cout << "max depth=: " << maxDepth << endl;

    return 0;
}
