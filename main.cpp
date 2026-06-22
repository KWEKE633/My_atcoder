// #pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
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
using mint2 = modint1000000007;

#define YES cout << "Yes" << "\n"
#define NO cout << "No" << "\n"

#define pb push_back
#define eb emplace_back

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
void print_el(const vec<T>& a) {
  for(auto &x : a) cout << x << "\n";
}

template<class T>
void print(const vec<T>& a) {
  rep(i, 0, (int)a.size()) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << el;
}

// ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); 

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

// int h, w;

bool check(int i, int j, int h, int w) {
  return 0 <= i && i < h && 0 <= j && j < w;
}

// -----自作ライブラリ (随時追加予定)-----

// -DSU (Union Find)-  Normal
struct DSU {
  vec<int> par, sz;

  DSU(int n) : par(n), sz(n, 1) {
    iota(par.begin(), par.end(), 0);
  }

  int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
  }
  
  bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    sz[x] += sz[y];
    par[y] = x;
    return true;
  }
  
  bool same(int x, int y) {
    return find(x) == find(y);
  }

  int size(int x) {
    return sz[find(x)];
  }
};

// Fenwicktree
template<class T>
struct Fenwick {
	int n;
	vec<T> bit;

	Fenwick(int _n) : n(_n), bit(_n + 1, T()) {}

	void add(int i, T x) {
		for (; i <= n; i += i & -i) {
			bit[i] += x;
		}
	}

	T sum(int i) const {
		T s = T();
		for (; i > 0; i -= i & -i) {
			s += bit[i];
		}
		return s;
	}

	T sum(int l, int r) const {
		if (r < l) return T();
		return sum(r) - sum(l - 1);
	}
};

struct FenwickRange {
	int n;
	Fenwick<ll> fw1, fw2;

	FenwickRange(int _n) : n(_n), fw1(_n), fw2(_n) {}
	void range_add(int l, int r, ll x) {
		fw1.add(l, x);
		fw1.add(r + 1, -x);
		fw2.add(l, x * (l - 1));
		fw2.add(r + 1, -x * r);
	}

	ll prefix_sum(int i) const {
		return fw1.sum(i) * i - fw2.sum(i);
	}

	ll range_sum(int l, int r) const {
		return prefix_sum(r) - prefix_sum(l - 1);
	}
};

struct Combination {
  int max_n;
  vec<mint> fact, inv;

  Combination(int n) : max_n(n), fact(n + 1), inv(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
    inv[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) inv[i - 1] = inv[i] * i;
  }

  mint nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    return fact[n] * inv[r] * inv[n - r];
  }

  mint nHr(int n, int r) {
    if (n == 0 && r == 0) return 1;
    if (n <= 0 || r < 0) return 0; 
    return nCr(n + r - 1, r);
  }
};

struct RollingHash {
	const int base = 9973;
	const int mod = 1e9 + 7;
	vec<ll> hashed;
	vec<ll> power;

	RollingHash(const string& s) {
		int n = s.size();
		hashed.assign(n + 1, 0);
		power.assign(n + 1, 1);
		rep(i, 0, n) {
			hashed[i + 1] = (hashed[i] * base + s[i]) % mod;
			power[i + 1] = (power[i] * base) % mod;
		}
	}

	ll get(int l, int r) {
		ll res = (hashed[r] - hashed[l] * power[r - l]) % mod;
		if (res < 0) res += mod;
		return res;
	}
};

struct XOR_Fenwick {
	int n;
	vec<ull> bit;
	XOR_Fenwick(int _n) : n(_n), bit(_n + 1, 0) {}
	void add(int i, ull x) {
		for (; i <= n; i += i & -i) {
			bit[i] ^= x;
		}
	}
	ull sum(int i) {
		ull s = 0;
		for (; i > 0; i -= i & -i) {
			s ^= bit[i];
		}
		return s;
	}

	ull sum(int l, int r) {
		if (l > r) return 0;
		return sum(r) ^ sum(l - 1);
	}
};

// struct S {
// 	ll val;
// 	int sz;
// };

// using F = ll;

// S op(S a, S b) {
// 	return {a.val + b.val, a.sz + b.sz};
// }

// S e() {
// 	return {0, 0};
// }

// S mapping(F f, S x) {
// 	return {x.val + f * x.sz, x.sz};
// }

// F comp(F f, F g) {
// 	return f + g;
// }

// F id() {
// 	return 0;
// }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	(void)INF;
	(void)INFLL;
	
	return 0;
}
