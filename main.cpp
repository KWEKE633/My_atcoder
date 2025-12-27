#include "All.hpp" // 自分のVScode用のヘッダー

//　提出はここから下を！

// #include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define repp(i, a, n) for (int i = a; i <= n; ++i)
#define ll long long
#define lrep(i, a, n) for (ll i = a; i < n; ++i)
#define lrepp(i, a, n) for (ll i = a; i <= n; ++i)
using ull = unsigned long long;

// #include <atcoder/all>

#include <atcoder/fenwicktree>
#include <atcoder/segtree>
#include <atcoder/lazysegtree>
#include <atcoder/string>

#include <atcoder/math>
#include <atcoder/convolution>
#include <atcoder/modint>

#include <atcoder/dsu>
#include <atcoder/maxflow>
#include <atcoder/mincostflow>
#include <atcoder/scc>
#include <atcoder/twosat>

using namespace atcoder;

using mint = modint998244353;

#define YES cout << "Yes" << "\n"
#define NO cout << "No" << "\n"

#define el endl

using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
using vec = vector<T>;

template <typename T>
using vvec = vector<vector<T>>;

template<class T> using pq = priority_queue<T>;
template<class T> using rpq = priority_queue<T, vector<T>, greater<T>>;

constexpr ll INFLL = (1LL<<60);
constexpr int INF = (1<<30);

template<class T>
bool chmax(T &a, const T &b) {
  if (a < b) { a = b; return true; }
  return false;
}

template<class T>
bool chmin(T &a, const T &b) {
  if (a > b) { a = b; return true; }
  return false;
}

template<class T>
void read(vec<T>& a) {
  for(auto &x : a) cin >> x;
}

template<class T>
void print(const vec<T>& a) {
  for(auto &x : a) cout << x << " ";
  cout << "\n";
}

// ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); 

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  return 0;
}
