# Hash

```c++
template<int N, int mod, int z>
struct Hash {
    static int HB[N+10];
    int HA[N+10];
    inline void init() {
        if(HB[0]) {
            return;
        }
        HB[0]=1;
        for(int i=1;i<=N;i++) {
            HB[i] = 1ll * HB[i-1] * z % mod;
        }
    }
    const string &operator=(const string &s) {
        auto sz = s.size();
        for(int i=0;i<sz;i++) {
            HA[i+1] = (1ll * HA[i] * z + s[i]) % mod;
        }
        return s;
    }

    inline void extend(const string &s, int n) {
        auto sz = s.length();
        for(int i = n; i < sz;i++) {
            HA[i+1] = (1ll * HA[i] * z + s[i]) % mod;
        }
    }
    Hash() {init();}
    Hash(const string &s) {
        init();
        *this = s;
    }

    inline long long slice(int l, int r) {
        static int ret;
        ret = HA[r] - 1ll * HA[l-1] * HB[r-l+1]%mod;
        return ret < 0 ? ret + mod : ret;
    }
};
template<int N, int mod, int z>
int Hash<N, mod, z>::HB[N+10];

```

