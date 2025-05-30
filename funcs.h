#ifndef FUNCS_H
#define FUNCS_H

extern double (*funcs[3])(double);
extern double (*dfuncs[3])(double);

extern unsigned long f1_calls, f2_calls, f3_calls,
                     df1_calls, df2_calls, df3_calls;

#endif // FUNCS_H