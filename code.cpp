#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

long long modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    vector<long long> fac(N + 1), ifac(N + 1);
    fac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[N] = modpow(fac[N], MOD - 2);
    for (int i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * i % MOD;

    auto C = [&](int n, int k) -> long long {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    };

    vector<int> parent(N, -1), leftc(N, -1), rightc(N, -1);
    vector<int> st;
    st.reserve(N);
    for (int i = 0; i < N; i++) {
        int last = -1;
        while (!st.empty() && P[st.back()] < P[i]) {
            last = st.back();
            st.pop_back();
        }
        if (!st.empty()) parent[i] = st.back();
        if (last != -1) parent[last] = i;
        st.push_back(i);
    }
    int root = -1;
    for (int i = 0; i < N; i++) if (parent[i] == -1) { root = i; break; }

    for (int i = 0; i < N; i++) {
        int p = parent[i];
        if (p == -1) continue;
        if (i < p) leftc[p] = i;
        else rightc[p] = i;
    }

    vector<int> order;
    order.reserve(N);
    vector<int> stack2;
    stack2.reserve(N);
    stack2.push_back(root);
    while (!stack2.empty()) {
        int u = stack2.back();
        stack2.pop_back();
        order.push_back(u);
        if (leftc[u] != -1) stack2.push_back(leftc[u]);
        if (rightc[u] != -1) stack2.push_back(rightc[u]);
    }
    reverse(order.begin(), order.end());

    vector<int> sz(N, 0);
    vector<long long> dp1(N, 1), dp2(N, 1), dp3(N, 1);

    for (int u : order) {
        int L = leftc[u], R = rightc[u];
        int sa = (L == -1 ? 0 : sz[L]);
        int sb = (R == -1 ? 0 : sz[R]);
        sz[u] = 1 + sa + sb;

        long long l2 = (L == -1 ? 1 : dp2[L]);
        long long l3 = (L == -1 ? 1 : dp3[L]);
        long long r1 = (R == -1 ? 1 : dp1[R]);
        long long r3 = (R == -1 ? 1 : dp3[R]);

        dp1[u] = l3 * r1 % MOD * C(sa + sb + 1, sa + 1) % MOD;
        dp2[u] = l2 * r3 % MOD * C(sa + sb + 1, sb + 1) % MOD;

        long long K = (C(sa + sb + 1, sa + 1) + C(sa + sb + 1, sb + 1) - C(sa + sb, sa)) % MOD;
        if (K < 0) K += MOD;
        dp3[u] = l3 * r3 % MOD * K % MOD;
    }

    int L = leftc[root], R = rightc[root];
    int sizeL = (L == -1 ? 0 : sz[L]);
    long long waysL = (L == -1 ? 1 : dp2[L]);
    long long waysR = (R == -1 ? 1 : dp1[R]);

    long long ans = waysL * waysR % MOD * C(N - 1, sizeL) % MOD;
    cout << ans << "\n";
    return 0;
}
