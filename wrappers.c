#include "funcs.h"   // объявления extern

unsigned long f1_calls = 0,
              f2_calls = 0,
              f3_calls = 0,
              df1_calls = 0,
              df2_calls = 0,
              df3_calls = 0;

extern double f1(double);
extern double f2(double);
extern double f3(double);
extern double df_poly2(double, double, double);
extern double df_f3(double);

static double f1_w(double x) { ++f1_calls; return f1(x); }
static double f2_w(double x) { ++f2_calls; return f2(x); }
static double f3_w(double x) { ++f3_calls; return f3(x); }

static double df1_w(double x) { ++df1_calls; return df_poly2(x, 0.35, -0.95); }
static double df2_w(double x) { ++df2_calls; return df_poly2(x, 0.0, 3.0); }
static double df3_w(double x) { ++df3_calls; return df_f3(x); }

double (*funcs[3])(double)  = { f1_w, f2_w, f3_w };
double (*dfuncs[3])(double) = { df1_w, df2_w, df3_w };