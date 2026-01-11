#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

static inline long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    if (N < M) {
        cout << 0 << "\n";
        return 0;
    }

    int k = N - M;

    vector<int> inv(k + 2);
    inv[1] = 1;
    for (int i = 2; i <= k + 1; i++) {
        inv[i] = (int)(MOD - (long long)(MOD / i) * inv[MOD % i] % MOD);
    }

    vector<int> B(k + 1);
    B[0] = 1;
    for (int t = 0; t < k; t++) {
        long long val = B[t];
        val = val * (3LL * M + t) % MOD;
        val = val * inv[t + 1] % MOD;
        B[t + 1] = (int)val;
    }

    long long A = 1;
    long long S = 0;
    for (int b = 0; b <= k; b++) {
        S = (S + A * B[k - b]) % MOD;
        if (b < k) {
            long long tmp = A * (M + (long long)b) % MOD;
            tmp = tmp * inv[b + 1] % MOD;
            A = (MOD - tmp) % MOD;
        }
    }

    long long ans = mod_pow(2, M) * (S % MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
