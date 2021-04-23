#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define ff               first
#define ss               second
#define pb               push_back
#define all(x)           (x).begin(), (x).end()
#define mem0(x)          memset(x, 0, sizeof (x))
#define mem1(x)          memset(x, -1, sizeof (x))

typedef long long ll;
#define int ll
typedef vector <int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector <ii> vii;
typedef vector<vii> vvii;

const int MAXN = 16, INF = 1e17;
int memo[MAXN][1<<MAXN];
int G[MAXN][MAXN];
int n;

int dp(int city, int mask){
    if (!mask) return memo[city][mask] = 0;
    if (~memo[city][mask]) return memo[city][mask];
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        if ((1<<i)&mask) ans = min(ans, G[city][i] + dp(i, mask ^ (1<<i)));
    }
    return memo[city][mask] = ans;
}

void recovery(int city, int mask, int val, string &s){
    if (!mask) return;
    for (int i = 0; i < n; ++i) {
        if (((1<<i)&mask) && val ==  G[city][i] + dp(i, mask ^ (1<<i))){
            s += (i+'A');
            recovery(i,  mask^(1<<i), val - G[city][i], s);
            return;
        }
    }
}

string find_best(vvi &A){
    n = A.size();
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) G[i][j] = A[i][j];
    mem1(memo);
    int min_cost = INF;
    int start = -1;
    for (int i = 0; i < 1; ++i) {
        if (dp(i, ((1<<n)-1)^(1<<i))  < min_cost) min_cost = dp(i, ((1<<n)-1)^(1<<i)), start = i;
    }
    if (min_cost == INF){
        return "NO EXISTE CAMINO\n";
    }
    string s; s += start+'A';
    recovery(start, ((1<<n)-1)^(1<<start),  min_cost, s);
    cout << s << "\n";
    return s;
}

int32_t main(){
    int n, m; cin >> n >> m;
    vvi A(n, vi(n, INF));
    for (int i = 0; i < m; ++i) {
        int w;
        char u, v; cin >> u >> v >> w;
        A[u-'A'][v-'A'] = A[v-'A'][u-'A'] = w;
    }
    string s = find_best(A);
    cout << s << "\n";
}