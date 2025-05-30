BITS 64
default rel

section .data
    a1  dq 0.35
    b1  dq -0.95
    c1  dq 2.7
    b2  dq 3.0
    c2  dq 1.0
    two dq 2.0
    one dq 1.0

section .text
global _f1, _f2, _f3, _df_poly2, _df_f3

; f1(x) = 0.35*x^2 - 0.95*x + 2.7
_f1:
    movsd xmm1, xmm0          ; xmm1 = x
    mulsd xmm1, xmm1          ; xmm1 = x^2
    mulsd xmm1, [rel a1]      ; xmm1 = 0.35*x^2

    movsd xmm2, xmm0          ; xmm2 = x
    mulsd xmm2, [rel b1]      ; xmm2 = -0.95*x

    addsd xmm1, xmm2          ; xmm1 = 0.35*x^2 - 0.95*x
    addsd xmm1, [rel c1]      ; xmm1 += 2.7

    movsd xmm0, xmm1          ; возвращаем результат в xmm0
    ret

; f2(x) = 3*x + 1
_f2:
    mulsd xmm0, [rel b2]  ; 3*x
    addsd xmm0, [rel c2]  ; +1
    ret

; f3(x) = 1/(x+2)
_f3:
    addsd xmm0, [rel two] ; xmm0 = x+2
    movsd xmm1, [rel one]
    divsd xmm1, xmm0      ; xmm1 = 1/(x+2)
    movsd xmm0, xmm1      ; result в xmm0
    ret

; df_poly2(x, a, b) = 2*a*x + b
_df_poly2:
    mulsd xmm1, [rel two] ; xmm1 = 2*a
    mulsd xmm1, xmm0      ; xmm1 = 2*a*x
    addsd xmm1, xmm2      ; xmm1 = 2*a*x + b
    movsd xmm0, xmm1      ; result
    ret

; df_f3(x) = -1/(x+2)^2
_df_f3:
    addsd xmm0, [rel two] ; x+2
    movsd xmm1, xmm0
    mulsd xmm1, xmm1      ; (x+2)^2
    movsd xmm2, [rel one]
    divsd xmm2, xmm1      ; 1/(x+2)^2
    movsd xmm0, xmm2
    xorpd xmm1, xmm1
    subsd xmm1, xmm0      ; -1/(x+2)^2
    movsd xmm0, xmm1
    ret
