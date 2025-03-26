#include <stdio.h>
#include <stdlib.h>
#include "erf_module.h"

int main() {
    double z;
    printf("Enter Z-score: ");
    
    if (scanf("%lf", &z) != 1) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }

    printf("\nNormal Distribution Confidence Intervals:\n");
    printf(" 90%%: %.5f\n", normal_cdf(z * 1.645)); // Z для 90%
    printf(" 95%%: %.5f\n", normal_cdf(z * 1.960)); // Z для 95%
    printf(" 99%%: %.5f\n", normal_cdf(z * 2.576)); // Z для 99%

    int df;
    printf("\nEnter degrees of freedom for Student's t-distribution: ");
    if (scanf("%d", &df) != 1 || df < 1) {
        fprintf(stderr, "Invalid input!\n");
        return 1;
    }

    printf("\nStudent's t-Distribution Confidence Intervals:\n");
    printf(" 90%%: %.5f\n", student_t_cdf(z * 1.860, df));
    printf(" 95%%: %.5f\n", student_t_cdf(z * 2.306, df));
    printf(" 99%%: %.5f\n", student_t_cdf(z * 3.291, df));

    return 0;
}

