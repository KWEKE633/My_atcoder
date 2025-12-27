#include "All.hpp"

// Union-Find

dsu uf(n);
uf.merge(u, v);
if(uf.same(u, v)){}
int size = uf.size(u);



// Bit 全探索（N ≤ 20）

rep(bit, 0, 1<<n) {
    vec<int> sel;
    rep(i, 0, n){
        if(bit>>i & 1) sel.push_back(i);
    }
}


// 二分探索（条件判定型）

ll l = -1, r = INFLL;
while(r - l > 1) {
    ll m = (l + r) / 2;
    if(check(m)) r = m;
    else l = m;
}


// 区間 DP 雛形

vvec<ll> dp(n, vec<ll>(n, INFLL));
rep(i, 0, n) dp[i][i] = 0;

for (int len = 2; len <= n; ++len) {
    rep(l, 0, n - len + 1) {
        int r = l + len - 1;
        for(int k = l; k < r; ++k) {
            chmin(dp[l][r], dp[l][k] + dp[k+1][r]);
        }
    }
}



// 木 DP 雛形

vvec<int> g(n);
vec<ll> dp(n);

void dfs(int v, int p) {
    dp[v] = 1;
    for(int to : g[v]) {
        if(to == p) continue;
        dfs(to, v);
        dp[v] += dp[to];
    }
}


// BFS（最短距離）

queue<int> q;
vec<int> dist(n, -1);
dist[s] = 0;
q.push(s);

while(!q.empty()) {
    int v = q.front(); q.pop();
    for(int to : g[v]) {
        if(dist[to] != -1) continue;
        dist[to] = dist[v] + 1;
        q.push(to);
    }
}


// DFS

void dfs(int v, int p) {
    for(int to : g[v]) {
        if(to == p) continue;
        dfs(to, v);
    }
}


// Dijkstra（重み付き）

vec<ll> dist(n, INFLL);
rpq<pll> q;
dist[s] = 0;
q.push({0, s});

while(!q.empty()) {
    auto [d, v] = q.top(); q.pop();
    if(d != dist[v]) continue;
    for(auto [to, cost] : g[v]) {
        if(chmin(dist[to], d + cost)) {
            q.push({dist[to], to});
        }
    }
}


