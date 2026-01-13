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

int n , nq ; 

int T [maxn*4] ; 
void update ( int id ,int l , int r , int pos , int w ) 
{
    if ( pos < l || pos > r ) return ; 
    if ( l == r ) 
    {
        T [id] = w ; 
        return ; 
    }
    update (left,l,mid,pos,w) ; 
    update (right,mid+1,r,pos,w) ; 
    T [id] = min (T[left],T[right]) ; 
}
int get ( int id , int l , int r , int u , int v ) 
{
    if ( l > v || r < u ) return 1e18 ; 
    if ( u <= l && r <= v ) return T [id] ; 
    return min (get(left,l,mid,u,v),get(right,mid+1,r,u,v)) ; 
}

signed main () 
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);cout.tie(0); 
    int test ; cin >> test ; 
    while ( test -- ) 
    {
        cin >> n >> nq ; 
        for ( int i = 1 ; i <= n ; i ++ ) 
        {
            int x ; cin >> x ; 
            update (1,1,n,i,x) ; 
        }
        while ( nq -- ) 
        {
            int type ; 
            cin >> type ; 
            if ( type == 1 ) 
            {
                int pos , w ; cin >> pos >> w ; 
                update (1,1,n,pos,w) ; 
            }
            else 
            {
                int L,R ; cin >> L >> R ; 
                int l = L , r = R ; 
                int res = -1 ;
                while ( l <= r ) 
                {
                    if ( get (1,1,n,L,mid) >= mid-L ) res = mid , l = mid + 1 ; 
                    else r = mid - 1 ; 
                }
                if ( res != - 1 && get (1,1,n,L,res) == res-L ) cout << 1 << "\n" ; 
                else cout << "0\n" ; 
            }
        }
    }
    return 0;
}