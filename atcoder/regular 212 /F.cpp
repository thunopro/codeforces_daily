#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, X;
    cin >> N >> M >> X;
    long long k = (long long)N - 2;

    long long ans = 0;

    for (int u = 0; u <= M; u++) {
        long long a = X, b = u;
        long long steps = k;

        while (steps > 0) {
            if (a == 0 || b == 0) {
                int r = (int)(steps % 3);
                for (int i = 0; i < r; i++) {
                    long long na = b;
                    long long nb = llabs(b - a);
                    a = na;
                    b = nb;
                }
                break;
            }

            if (b >= a && steps >= 3) {
                if (b == a) {
                    steps %= 3;
                    continue;
                }
                long long t_chain = (b - a) / (2 * a) + 1;
                long long t = min(steps / 3, t_chain);

                if (t < t_chain) b = b - 2 * a * t;
                else b = llabs(b - 2 * a * t);

                steps -= 3 * t;
                continue;
            }

            long long na = b;
            long long nb = llabs(b - a);
            a = na;
            b = nb;
            steps--;
        }

        ans = (ans + (a % MOD) * (b % MOD)) % MOD;
    }

    cout << ans % MOD << "\n";
    return 0;
}
