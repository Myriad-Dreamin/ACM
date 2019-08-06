# Euclid Like

$$
f(a,b,c,n) = \sum_{i=0}^n\left\lfloor \frac{ai+b}{c}\right\rfloor
$$

$$
f(a,b,c,n) = g(a,b,c,n) + f(a\bmod c, b\bmod c, c, n)\\
g(a,b,c,n)=\frac{n(n+1)}{2}\left\lfloor \frac{a}{c}\right\rfloor+ (n+1)\left\lfloor \frac{b}{c}\right\rfloor
$$

$$
f(a,b,c,n) = nm - f(c,c-b-1,a, m-1) = nm - g(c,c-b-1,a,n)\\ - f(c \bmod a, c-b-1 \bmod a, a, m-1), m = \left\lfloor \frac{an+b}{c}\right\rfloor
$$

