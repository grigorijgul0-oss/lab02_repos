#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 25;
const int MIN_VAL = -20;
const int MAX_VAL = 30;


void GenerateArray(int arr[], int size, int minVal, int maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

void PrintArray(const int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << setw(4) << arr[i];
    cout << endl;
}

int CountPositiveEven(const int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] > 0 && arr[i] % 2 == 0)
            count++;
    return count;
}

int SumPositiveEven(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] > 0 && arr[i] % 2 == 0)
            sum += arr[i];
    return sum;
}

void ReplacePositiveEvenWithZero(int arr[], int size) {
    for (int i = 0; i < size; i++)
        if (arr[i] > 0 && arr[i] % 2 == 0)
            arr[i] = 0;
}

int main() {
    srand((unsigned)time(0));

    int a[SIZE];

  
    GenerateArray(a, SIZE, MIN_VAL, MAX_VAL);

    cout << "start masiv:" << endl;
    PrintArray(a, SIZE);

    
    int count = CountPositiveEven(a, SIZE);
    int sum = SumPositiveEven(a, SIZE);

    
    cout << "\ncount: " << count << endl;
    cout << "sum: " << sum << endl;

    
    ReplacePositiveEvenWithZero(a, SIZE);

    cout << "\nmodufikovanij masiv" << endl;
    PrintArray(a, SIZE);

    return 0;
}
