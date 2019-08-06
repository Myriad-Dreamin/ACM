## Sieves

待验证
### 欧拉筛
```c++
void init_prim(int n)
{
    memset(isprime,0,sizeof(isprime));
    sp = 0;
    for(int i = 2;i <= n;i++)
    {
        if(!isprime[i])
        {
            prime[++sp] = i;
            isprime[i] = i;
        }
        for(int j = 1;j <= sp && i * prime[j] <= n;j++) {
            isprime[i*prime[j]] = prime[j];
            if(prime[j] >= isprime[i]) break;//用isprime[i]来表示i的最小质因子,可能用mod比较慢 
        }
    }
}
```

### 积型函数筛
#### $\varphi(x) = x\prod_{p|x}(1-p^{-1})$
$$
\varphi(p) = p-1, \text{if p is prime}\\
\varphi(ip) = \varphi(i)p, p|i,\text{p is prime}\\
\varphi(ip) = \varphi(i)(p-1), p\nmid i, \text{,p is prime}\\
$$

```c++
void init_phi(int n)
{
    memset(isprime,0,sizeof(isprime));
    sp = 0;
    for(int i = 2;i <= n;i++)
    {
        if(!isprime[i])
        {
            prime[++sp] = i;
            isprime[i] = i;
            phi[i] = i-1;// if is prime
        }
        for(int j = 1;j <= sp && i * prime[j] <= n;j++) {
            isprime[i*prime[j]] = prime[j];
            if(prime[j] >= isprime[i]) {
                phi[i*prime[j]] = phi[i]*prime[j];// if is not coprime but pi(prime)>1
                break;
            }
            phi[i*prime[j]] = phi[i]*(prime[j]-1);// if is coprim
        }
    }
}
```
#### $\mu(x) = \prod_{p|x}-[p||x]$

$$
\mu(p) = -1, \text{if p is prime}\\
\mu(ip) = 0, p|i,\text{p is prime}\\
\mu(ip) = -\mu(i), p\nmid i, \text{,p is prime}\\
$$

```c++
void init_phi(int n)
{
    memset(isprime,0,sizeof(isprime));
    sp = 0;
    for(int i = 2;i <= n;i++)
    {
        if(!isprime[i])
        {
            prime[++sp] = i;
            isprime[i] = i;
            miu[i] = -1;// if is prime
        }
        for(int j = 1;j <= sp && i * prime[j] <= n;j++) {
            isprime[i*prime[j]] = prime[j];
            if(prime[j] >= isprime[i]) {
                miu[i*prime[j]] = 0;// if is not coprime but pi(prime)>1
                break;
            }
            miu[i*prime[j]] = -miu[i];// if is coprim
        }
    }
}
```

#### $d(x) = \prod_{p|x}(1+\pi _x(p))$

$$
d(p) = 1, \pi_{i}(p) = 1, \text{if p is prime}\\
d(ip) = d(i)\frac{1+\pi_{ip}(p)}{1+\pi_{i}(p)}, \pi_{ip}(p) = \pi_{i}(p) + 1, p|i,\text{p is prime}\\
d(ip) = 2d(i),\pi_{ip}(p) =1, p\nmid i, \text{,p is prime}\\
$$

#### $\sigma(x) = \prod_{p|x}\sum_{i=0}^{\pi_x(p)}p^i$

$$
\sigma(p) = p+1, g(p)=1+p, \text{if p is prime}\\
\sigma(ip) = \sigma(i)\frac{1+\pi_{ip}(p)}{1+\pi_{i}(p)}, g(ip)=g(i)p+1, p|i,\text{p is prime}\\
\sigma(ip) = (1+p)\sigma(i), g(p)=1+p, p\nmid i, \text{,p is prime}\\
$$

