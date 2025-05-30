#ifndef NEWTON_H
#define NEWTON_H

double root(double (*f)(double), double (*g)(double),
            double (*df)(double), double (*dg)(double),
            double a, double b, double eps,
            unsigned *iters /* число итераций будет записано сюда */);

#endif // NEWTON_H