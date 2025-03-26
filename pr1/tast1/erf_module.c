#include "erf_module.h"
#include <stdio.h>
#include <math.h>

// Нормальний (стандартний) розподіл
double normal_cdf(double z) {
    return 0.5 * (1 + erf(z / sqrt(2.0)));
}

// Функція для розподілу Стьюдента
double student_t_cdf(double t, int df) {
    if (df < 1) {
        fprintf(stderr, "Degrees of freedom must be >= 1\n");
        return -1;
    }
    return 0.5 + (t * t) / (2.0 * df); // Спрощена апроксимація
}
