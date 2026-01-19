#include <bits/stdc++.h>
#define int long long
#define ll long long
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pb push_back
#define re exit(0);
#define FOR(i, a, b)   for(int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, a, b)  for(int i = (a), _b = (b); i >= _b; i--)
#define LOOP(a)        for(int i = 0, _a = (a); i < _a; i++)
#define left (id<<1)
#define right (id<<1|1)
#define _lower(v, x) lower_bound(v.begin(), v.end(), x) - v.begin() + 1

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

template<typename T> void chkmin(T &x, T y) {if (y < x) x = y;}
template<typename T> void chkmax(T &x, T y) {if (y > x) x = y;}

const int mod = 1e9 + 7;
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    if (a < 0) a += mod;
}

int _pow(int a, int b) {
   int ans = 1;
   while (b) {
   if (b % 2 == 1) ans = 1ll * ans * a % mod;
        a = 1ll * a * a % mod;
        b /= 2;
   }
   return ans;
}

//--------------------------------------------------------------------------------------------------------------------------------------

const int maxn = 5e5;
int a[maxn + 5], b[maxn + 5];
long long max_odd, max_even , min_odd, min_even;
long long Sb;
int n;

int calc() {
    int mx = *max_element(b + 1, b + n + 1);
    return max(mx, (Sb + (n - 1) - 1) / (n - 1));
}

int calc_delta(long delta) {
    return max({max_even + delta, max_odd - delta, (Sb + (n - 1) - 1) / (n - 1)}); 
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Sb = accumulate(a + 1, a + n + 1, 0ll) / 2;

    if (n & 1) {
        b[1] = Sb;
        for (int i = 3; i <= n; i += 2)
            b[1] -= a[i];
        for (int i = 2; i <= n; i++)
            b[i] = a[i] - b[i - 1];
        cout << calc() << '\n';
        return;
    }
    else {
        b[1] = 0;
        for (int i = 2; i <= n; i++)
            b[i] = a[i] - b[i - 1];

        max_odd = -1e18, max_even = -1e18, min_odd = 1e18, min_even = 1e18;
        for (int i = 1; i <= n; i ++) {
            if (i & 1) {
                chkmax(max_odd, b[i]);
                chkmin(min_odd, b[i]);
            }
            else {
                chkmax(max_even, b[i]);
                chkmin(min_even, b[i]);
            }
        }

        long long res = 1e18;
        long long delta = (max_odd - max_even) / 2;
        if (-min_even <= delta && delta <= min_odd) 
            chkmin(res, calc_delta(delta));

        delta = (max_odd - max_even) / 2;
        if (-min_even <= delta && delta <= min_odd) 
            chkmin(res, calc_delta(delta));

        delta = -min_even;
        chkmin(res, calc_delta(delta));
        
        delta = min_odd;
        chkmin(res, calc_delta(delta));

        cout << res << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //#define name "mooo"
    //if (fopen(name".inp", "r")) {
    //     freopen(name".inp", "r", stdin);
    //     freopen(name".out", "w", stdout);
    //}
    
    int numTest; cin >> numTest;
    while (numTest --)
        solve();

    return 0;
}
