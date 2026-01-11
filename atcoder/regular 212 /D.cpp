#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<long long>> A(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> A[i][j];
    }

    vector<int> x(N, 1);
    vector<long long> g(N, 0);
    for (int i = 0; i < N; i++) {
        long long s = 0;
        for (int j = 0; j < N; j++) s += A[i][j] * x[j];
        g[i] = s;
    }

    while (true) {
        int bad = -1;
        for (int i = 0; i < N; i++) {
            if (1LL * x[i] * g[i] < 0) {
                bad = i;
                break;
            }
        }
        if (bad == -1) break;

        int i = bad;
        int old = x[i];
        x[i] = -x[i];
        long long delta = (long long)x[i] - old;

        for (int k = 0; k < N; k++) {
            g[k] += A[k][i] * delta;
        }
    }

    string ans;
    ans.reserve(N);
    for (int i = 0; i < N; i++) ans.push_back(x[i] == 1 ? 'X' : 'Y');
    cout << ans << "\n";
    return 0;
}
