#include <math.h>
#include <stdio.h>
#include "newton.h"

// f, g — функции; df, dg — их производные
double root(double (*f)(double), double (*g)(double),
            double (*df)(double), double (*dg)(double),
            double a, double b, double eps,
            unsigned *iters)
{
    double x = (a + b) / 2.0;          // старт из середины
    unsigned k = 0, MAX_ITER = 1000;

    while (k < MAX_ITER) {
        double Fx  = f(x) - g(x);
        if (fabs(Fx) < eps) break;
        double Fpx = df(x) - dg(x);
        if (Fpx == 0.0) { fprintf(stderr, "Нулевая производная в %g\n", x); break; }
        double x_new = x - Fx / Fpx;
        if (x_new < a || x_new > b) x_new = (a + x) / 2.0; // возврат в интервал
        if (fabs(x_new - x) < eps) { x = x_new; break; }
        x = x_new;
        ++k;
    }
    if (iters) *iters = k;
    return x;
}