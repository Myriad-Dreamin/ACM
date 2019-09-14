# Gauss Jordan Elimination
```c++

long long Gauss(int n, int m) {
  for (int i = 1; i <= n; i++) {
    long long inv = qp(a[i][i], mod - 2);
    for (int j = i; j <= m; j++) {
      a[i][j] = inv * a[i][j] % mod;
    }
    for (int k = i + 1; k <= n; k++) {
      long long muler = a[k][i];
      for (int j = i; j <= m; j++) {
        a[k][j] = (a[k][j] + mod - muler * a[i][j] % mod) % mod;
      }
    }
  }

  // for(int i=1;i<=n;i++) {
  //     for(int j=1;j<=m;j++) {
  //         printf("%lld ",a[i][j]);
  //     }
  //     puts("");
  // }

  for (int i = n; i >= 1; i--) {
    for (int j = 1; j < i; j++) {
      a[j][m] = (a[j][m] + mod - a[j][i] * a[i][m] % mod) % mod;
      a[j][i] = 0;
    }
  }
  // for(int i=1;i<=n;i++) {
  //     for(int j=1;j<=m;j++) {
  //         printf("%lld ",a[i][j]);
  //     }
  //     puts("");
  // }
}

```
