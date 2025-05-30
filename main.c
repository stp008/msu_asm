#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "newton.h"
#include "simpson.h"
#include "funcs.h"

static const double EPS  = 1e-3;   // точность площади
static const double EPS1 = 1e-5;   // точность корней
static const double EPS2 = 1e-4;   // точность интеграла

static void usage(const char *p) {
    printf("Использование: %s [опции]\n\n", p);
    puts("  -help           справка");
    puts("  -roots          вывести корни");
    puts("  -iters          вывести число итераций");
    puts("  -calls          вывести число вызовов функций");
    puts("  -test-root f g a b eps   тест root()\n");
    puts("  -test-integral f g a b eps   тест root()\n");
    puts("Функции нумеруются: 1 — f1, 2 — f2, 3 — f3.");
}

// Разности для интегрирования
static double diff_f3_f1(double x){ return funcs[2](x) - funcs[0](x); }
static double diff_f2_f1(double x){ return funcs[1](x) - funcs[0](x); }

int main(int argc, char **argv) {
    int show_roots = 0, show_iters = 0, show_calls = 0;

    // разбор аргументов
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-help")) { usage(argv[0]); return 0; }
        if (!strcmp(argv[i], "-roots")) show_roots = 1;
        else if (!strcmp(argv[i], "-iters")) show_iters = 1;
        else if (!strcmp(argv[i], "-calls")) show_calls = 1;
        else if (!strcmp(argv[i], "-test-root")) {
            if (i + 5 >= argc) { fprintf(stderr, "Недостаточно аргументов\n"); return 1; }
            int f = atoi(argv[++i]) - 1;
            int g = atoi(argv[++i]) - 1;
            double a = atof(argv[++i]);
            double b = atof(argv[++i]);
            double eps = atof(argv[++i]);
            unsigned iters = 0;
            double x = root(funcs[f], funcs[g], dfuncs[f], dfuncs[g], a, b, eps, &iters);
            printf("root = %.10g, iterations = %u\n", x, iters);
            return 0;
        }
        else if (!strcmp(argv[i], "-test-integral")) {
            if (i + 4 >= argc) { fprintf(stderr, "Недостаточно аргументов\n"); return 1; }
            int f = atoi(argv[++i]) - 1;
            double a = atof(argv[++i]);
            double b = atof(argv[++i]);
            double eps = atof(argv[++i]);
            double x = integral(funcs[f], a, b, eps);
            printf("integral = %.10g", x);
            return 0;
        }
        else { fprintf(stderr, "Неизвестная опция %s; попробуйте -help\n", argv[i]); return 1; }
    }

    unsigned it12, it13, it23;
    double x12 = root(funcs[0], funcs[1], dfuncs[0], dfuncs[1], 0.0, 1.0, EPS1, &it12);    // f1=f2
    double x13 = root(funcs[0], funcs[2], dfuncs[0], dfuncs[2], -2.0, -1.0, EPS1, &it13); // f1=f3
    double x23 = root(funcs[1], funcs[2], dfuncs[1], dfuncs[2], -1.5, 2, EPS1, &it23);   // f2=f3

    double area = 0.0;
    area += integral(diff_f3_f1, x13, x23, EPS2);
    area += integral(diff_f2_f1, x23, x12, EPS2);

    printf("Площадь фигуры ≈ %.6f\n", fabs(area)); // fabs, на всякий случай

    if (show_roots)
        printf("Корни: x13 = %.6f, x23 = %.6f, x12 = %.6f\n", x13, x23, x12);
    if (show_iters)
        printf("Итерации: f1=f3 %u, f2=f3 %u, f1=f2 %u\n", it13, it23, it12);
    if (show_calls)
        printf("Вызовы: f1 %lu, f2 %lu, f3 %lu, df1 %lu, df2 %lu, df3 %lu\n",
               f1_calls, f2_calls, f3_calls, df1_calls, df2_calls, df3_calls);
    return 0;
}