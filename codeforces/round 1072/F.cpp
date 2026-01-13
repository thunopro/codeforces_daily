#include<bits/stdc++.h>
using namespace std ; 
#define int long long
#define ll long long 
#define pb push_back 
#define fi first 
#define se second 
#define left id<<1
#define right id<<1|1 
#define re exit(0); 
#define _lower(x) lower_bound(v.begin(),v.end(),x)-v.begin()+1 
#define mid (l+r)/2
#define all(x) x.begin(),x.end()
#define TIME ( 1.0*clock() / CLOCKS_PER_SEC )
const int mod = 1e9+7 ;
const int INF = 1e9 ; 

typedef vector<int> vi ; 
typedef pair<int,int> pii ; 
typedef vector<pii> vii ; 

template < typename T > void chkmin ( T &a , T b ) { if ( a > b ) a = b ; } 
template < typename T > void chkmax ( T &a , T b ) { if ( a < b ) a = b ; } 

void add ( int &a , int b ) 
{
    a += b ; 
    if ( a >= mod ) a -= mod ; 
    if ( a < 0 ) a += mod ; 
}


int _pow ( int a , int n ) 
{
    if ( n == 0 ) return 1 ; 
    int res = _pow (a,n/2) ; 
    if ( n % 2 ) return 1ll*res*res%mod*a%mod ; 
    else return 1ll*res*res%mod ; 
}
#define maxn 200009

int n ; 
vi adjList [maxn] ; 
int dp [maxn] ; 
int fdp [maxn] ; 
void dfs ( int u , int par = -1 ) 
{
    int child = 0 ; 
    dp [u] = 1 ; 
    fdp [u] = 0 ; 
    for ( auto v : adjList [u] ) 
    {
        if ( v == par ) continue ; 
        dfs (v,u) ; 
        for ( int t1 = 0 ; t1 < 3 ; t1 ++ ) 
        {
            if ( dp [u] >> t1 & 1 ) 
            {
                for ( int t2 = 0 ; t2 < 3 ; t2 ++ ) 
                {
                    if ( dp [v] >> t2 & 1 ) 
                    {
                        fdp [u] |= 1<<((t1+t2)%3) ; 
                    }
                }
            }
        }
        dp [u] = fdp [u] ; fdp [u] = 0 ; 
        child ++ ; 
    }
    if ( child == 0 ) dp [u] = 1<<1 ; 
    else dp [u] |= 1<<1 ; 
}
signed main () 
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);cout.tie(0); 
    int test ; cin >> test ; 
    while ( test -- ) 
    {
        cin >> n ; 
        for ( int i = 1 ; i <= n ; i ++ ) adjList [i].clear() ; 
        for ( int i = 1 ; i < n ; i ++ ) 
        {
            int u , v ; cin >> u >> v ; 
            adjList [u] . pb (v) ; 
            adjList [v] . pb (u) ;
        }
        dfs (1) ; 
        if ( dp[1]>>0&1 ) cout << "YES\n" ; 
        else cout << "NO\n" ; 
    }
    return 0;
}