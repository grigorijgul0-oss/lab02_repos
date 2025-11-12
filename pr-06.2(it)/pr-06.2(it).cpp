#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void createArray(int a[], int n, int minVal, int maxVal) {
    srand(time(0));
    for (int i = 0; i < n; i++)
        a[i] = minVal + rand() % (maxVal - minVal + 1);
}

void printArray(const int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << setw(5) << a[i];
    cout << endl;
}

double averageOdd(const int a[], int n) {
    int sum = 0, count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) {
            sum += a[i];
            count++;
        }
    }
    return (count == 0) ? 0 : (double)sum / count;
}

int main() {
    const int n = 10;
    int a[n];

    createArray(a, n, -10, 10);

    cout << "masiv:" << endl;
    printArray(a, n);

    double avg = averageOdd(a, n);
    cout << fixed << setprecision(2);
    cout << "avg = " << avg << endl;

    return 0;
}
