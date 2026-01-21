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

int dx[] = {0, 0, -1, +1};
int dy[] = {-1, +1, 0, 0};

const int maxn = 5e5;
int par[maxn + 5], sz[maxn + 5], val[maxn + 5], important[maxn + 5];
void make_set(int u, int x) {
    par[u] = u; sz[u] = 1; val[u] = x; important[u] = 1;
}
int find_set(int u) {
    return (u == par[u] ? u : par[u] = find_set(par[u]));
}
bool unite(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u;
    sz[u] += sz[v];
    important[u] = min(important[u], important[v]);
    return true;
}

int n, m;
vector<pii> adj_cell(int x, int y) {
    vector<pii> res;
    for (int i = 0; i < 4; i++) {
        int _x = x + dx[i], _y = y + dy[i];
        if (1 <= _x && _x <= n && 1 <= _y && _y <= m)
            res.pb({_x, _y});
    }
    return res;
}

void solve() {
    cin >> n >> m;
    vector<vi> a(n + 5, vi(m + 5));
    vector<vi> cell_node(n + 5, vi(m + 5));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            cell_node[i][j] = m * (i - 1) + j;
            make_set(cell_node[i][j], a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
            for (auto [x, y] : adj_cell(i, j))
                if (a[x][y] < a[i][j]) 
                    important[cell_node[i][j]] = 0;

    int res = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (auto [x, y] : adj_cell(i, j))
                if (a[x][y] == a[i][j])
                    unite(cell_node[x][y], cell_node[i][j]);
                
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (find_set(cell_node[i][j]) == cell_node[i][j])   
                res += important[cell_node[i][j]];

    cout << res << '\n';

    int numQuery;
    cin >> numQuery;
    int cur_node = n * m;

    while (numQuery --) {
        int r, c, delta; 
        cin >> r >> c >> delta;
        
        ++cur_node;
        int new_val = a[r][c] - delta;
        make_set(cur_node, new_val);

        set<int> s;
        for (auto [x, y] : adj_cell(r, c)) 
            s.insert(find_set(cell_node[x][y]));
        s.insert(find_set(cell_node[r][c]));
                
        for (int comp : s) 
            res -= important[comp];
    
        for (int comp : s) {
            if (val[comp] == new_val)
                unite(cur_node, comp);
        }

        s.clear();
        for (auto [x, y] : adj_cell(r, c))
            s.insert(find_set(cell_node[x][y]));

        for (int comp : s)
            if (val[comp] > new_val) 
                important[comp] = 0;
            else if (val[comp] < new_val)
                important[find_set(cur_node)] = 0;

        for (int comp : s)
            res += important[comp];

        if (!s.count(find_set(cur_node))) 
            res += important[cur_node];
        
        a[r][c] = new_val;
        cell_node[r][c] = cur_node;

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