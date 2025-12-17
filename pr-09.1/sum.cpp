// sum.cpp
#include <cmath>
#include "dod.h"
#include "sum.h"
#include "var.h"

using namespace nsDod;
using namespace nsVar;

void nsSum::sum() {
    n = 0;
    // Перший член ряду при n=0 дорівнює 2*x
    a = 2 * x;
    s = a;

    do {
        n++;
        dod(); // Обчислення наступного доданку a
        s += a;
    } while (fabs(a) > e);
}