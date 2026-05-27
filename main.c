#include <stdio.h>

double f(double x, double y) {
    return -3 * y + x * x;
}

double my_abs(double x) {
    return x < 0 ? -x : x;
}

// e^x через ряд Тейлора
double exp_taylor(double x) {
    double sum = 1.0;
    double term = 1.0;

    for (int n = 1; n <= 50; n++) {
        term *= x / n;
        sum += term;

        if (my_abs(term) < 1e-15)
            break;
    }

    return sum;
}

// Аналитическое решение
double exact_solution(double x) {
    return (25.0 / 27.0) * exp_taylor(-3.0 * x)
           + (x * x) / 3.0
           - (2.0 * x) / 9.0
           + 2.0 / 27.0;
}

int main() {
    double x0 = 0.0;
    double y0 = 1.0;
    double x_end = 2.0;
    double h = 0.1;

    double x = x0;
    double y = y0;

    printf("x\t\tRK2\t\tExact\t\tError\n");

    printf("%.2f\t\t%.6f\t%.6f\t%.6f\n",
           x,
           y,
           exact_solution(x),
           my_abs(y - exact_solution(x)));

    while (x < x_end) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h, y + k1);

        y = y + (k1 + k2) / 2.0;
        x = x + h;

        double exact = exact_solution(x);
        double error = my_abs(y - exact);

        printf("%.2f\t\t%.6f\t%.6f\t%.6f\n",
               x,
               y,
               exact,
               error);
    }

    return 0;
}