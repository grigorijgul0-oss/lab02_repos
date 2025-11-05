#include <iostream>
#include <cmath>
using namespace std;

// 1) Ітераційний спосіб
double P0(const int K, const int N) {
    double p = 1;
    for (int i = K; i <= N; i++)
        p *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    return p;
}

// 2) Рекурсивний спуск, параметр зростає
double P1(const int K, const int N, const int i) {
    if (i > N)
        return 1;
    else
        return ((pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i)) * P1(K, N, i + 1);
}

// 3) Рекурсивний спуск, параметр спадає
double P2(const int K, const int N, const int i) {
    if (i < K)
        return 1;
    else
        return ((pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i)) * P2(K, N, i - 1);
}

// 4) Рекурсивний підйом, параметр зростає
double P3(const int K, const int N, const int i, double t) {
    t *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    if (i >= N)
        return t;
    else
        return P3(K, N, i + 1, t);
}

// 5) Рекурсивний підйом, параметр спадає
double P4(const int K, const int N, const int i, double t) {
    t *= (pow(sin(i), 2) + pow(cos(1.0 / i), 2)) / (i * i);
    if (i <= K)
        return t;
    else
        return P4(K, N, i - 1, t);
}

int main() {
    int K = 1, N = 15;

    cout << "(iter) P0 = " << P0(K, N) << endl;
    cout << "(rec down ++) P1 = " << P1(K, N, K) << endl;
    cout << "(rec down --) P2 = " << P2(K, N, N) << endl;
    cout << "(rec up ++) P3 = " << P3(K, N, K, 1) << endl;
    cout << "(rec up --) P4 = " << P4(K, N, N, 1) << endl;

    return 0;
}
