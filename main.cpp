// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
// #include <ext/rope>
using namespace std;
// using namespace __gnu_cxx;
// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define repp(i, a, n) for (int i = a; i <= n; ++i)
#define ll long long
#define lrep(i, a, n) for (ll i = a; i < n; ++i)
#define lrepp(i, a, n) for (ll i = a; i <= n; ++i)
using ull = unsigned long long;
using ld = long double;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

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

template<class Range>
void read(Range&& a) {
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

int dy8[] = {0, 1, 1, 1, 0, -1, -1};
int dx8[] = {1, 1, 0, -1, -1, -1, 0};

// int h, w;

bool check(int i, int j, int h, int w) {
  return 0 <= i && i < h && 0 <= j && j < w;
}

bool check2(int i, int j, int h, int w) {
  return 0 < i && i < h && 0 < j && j < w;
}

ll modpow(ll a, ll n, ll mod) {
	ll res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

// -----自作ライブラリ (随時追加予定)-----

// -DSU (Union Find)-  Normal
struct DSU {
  vec<int> par, sz;
  int components;

  DSU(int n) : par(n + 1), sz(n + 1, 1) {
    iota(par.begin(), par.end(), 0);
	components = n;
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
	components--;
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
	T n;
	vec<T> bit;

	Fenwick(T _n) : n(_n), bit(_n + 1, T()) {}

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

struct combination { // 好きな素数mで計算できる版
	int max_n;
	ll mod;
	vector<ll> fact, inv;
	ll modpow(ll a, ll b) {
		ll res = 1;
		a %= mod;
		while (b > 0) {
			if (b & 1) res = (res * a) % mod;
			a = (a * a) % mod;
			b >>= 1;
		}
		return res;
	}

	ll modinv(ll a) {
		return modpow(a, mod - 2);
	}

	combination(int n, ll m) : max_n(n), mod(m), fact(n + 1), inv(n + 1) {
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) {
			fact[i] = (fact[i - 1] * i) % mod;
		}
		inv[n] = modinv(fact[n]);
		for (int i = n; i >= 1; --i) {
			inv[i - 1] = (inv[i] * i) % mod;
		}
	}

	ll nCr(int n, int r) {
		if (r < 0 || r > n) return 0;
		if (r == 0 || r == n) return 1;
		ll res = fact[n];
		res = (res * inv[r]) % mod;
		res = (res * inv[n - r]) % mod;
		return res;
	}

	ll nHr(int n, int r) {
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

struct LCA {
	int n, log;
	vector<vector<int>> up;
	vector<int> depth;
	vector<ll> sz;

	LCA(const vector<vector<int>>& adj, int root = 0) {
		n = adj.size();
		log = 1;
		while ((1 << log) <= n) log++;

		up.assign(log, vector<int>(n, 0));
		depth.assign(n, 0);
		sz.assign(n, 0);

		auto dfs = [&](auto& self, int u, int p) -> void {
			up[0][u] = p;
			sz[u] = 1;
			for (int v : adj[u]) {
				if (v != p) {
					depth[v] = depth[u] + 1;
					self(self, v, u);
					sz[u] += sz[v];
				}
			}
		};
		dfs(dfs, root, root);

		for (int i = 1; i < log; i++) {
			for (int j = 0; j < n; j++) {
				up[i][j] = up[i - 1][up[i - 1][j]];
			}
		}
	}

	int get_lca(int u, int v) const {
		if (depth[u] < depth[v]) swap(u, v);
		int diff = depth[u] - depth[v];
		for (int i = 0; i < log; i++) {
			if ((diff >> i) & 1) u = up[i][u];
		}
		if (u == v) return u;
		for (int i = log - 1; i >= 0; i--) {
			if (up[i][u] != up[i][v]) {
				u = up[i][u];
				v = up[i][v];
			}
		}
		return up[0][u];
	}

	int get_dist(int u, int v) const {
		return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
	}

	int get_ancestor_at_depth(int u, int d) const {
		int diff = depth[u] - d;
		for (int i = 0; i < log; i++) {
			if ((diff >> i) & 1) u = up[i][u];
		}
		return u;
	}
};

// struct LCA_W {
// 	int n, log;
// 	vector<vector<int>> up;
// 	vector<ll> dist;
// 	vector<int> level;

// 	LCA_W() {}
// 	LCA_W(const vector<vector<pair<int, ll>>>& adj, int root = 0) {
// 		n = adj.size();
// 		log = 1;
// 		while ((1 << log) <= n) log++;

// 		up.assign(log, vector<int>(n, 0));
// 		dist.assign(n, 0);
// 		level.assign(n, 0);

// 		auto dfs = [&](auto& self, int u, int p) -> void {
// 			up[0][u] = p;
// 			for (auto v : adj[u]) {
// 				if (v.first != p) {
// 					dist[v.first] = dist[u] + v.second;
// 					level[v.first] = level[u] + 1;
// 					self(self, v.first, u);
// 				}
// 			}
// 		};
// 		dfs(dfs, root, root);

// 		for (int i = 1; i < log; i++) {
// 			for (int j = 0; j < n; j++) {
// 				up[i][j] = up[i - 1][up[i - 1][j]];
// 			}
// 		}
// 	}

// 	int get_lca(int u, int v) const {
// 		if (level[u] < level[v]) swap(u, v);
// 		int diff = level[u] - level[v];
// 		for (int i = 0; i < log; i++) {
// 			if ((diff >> i) & 1) u = up[i][u];
// 		}
// 		if (u == v) return u;
// 		for (int i = log - 1; i >= 0; i--) {
// 			if (up[i][u] != up[i][v]) {
// 				u = up[i][u];
// 				v = up[i][v];
// 			}
// 		}
// 		return up[0][u];
// 	}

// 	ll get_dist(int u, int v) const {
// 		return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
// 	}
// };

template<class T>
struct SparseTable {
	vector<vector<T>> table;
	SparseTable(const vector<T>& a) {
		int n = a.size();
		int max_log = 0;
		while ((1 << max_log) <= n) {
			max_log++;
		}
		table.assign(max_log, vector<T>(n));
		for (int i = 0; i < n; ++i) {
			table[0][i] = a[i];
		}
		for (int k = 1; k < max_log; ++k) {
			int half_len = 1 << (k - 1);
			for (int i = 0; i + (half_len * 2) <= n; ++i) {
				table[k][i] = max(table[k - 1][i], table[k - 1][i + half_len]);
			}
		}
	}

	T query(int l, int r) {
		if (r < l) return -1;
		else if (r == l)  return table[0][l];
		int len = r - l;
		int k = 31 - __builtin_clz(len);

		return max(table[k][l], table[k][r - (1 << k)]);
	}
};

// struct BitVector {
// 	int n;
// 	vector<uint64_t> block;
// 	vector<int> count;

// 	BitVector() {}
// 	BitVector(int n) : n(n), block((n + 63) / 64 + 1, 0), count((n + 63) / 64 + 1, 0) {}

// 	void set(int i) {
// 		block[i / 64] |= (1ULL << (i % 64));
// 	}

// 	void build() {
// 		for (size_t i = 0; i < block.size() - 1; ++i) {
// 			count[i + 1] = count[i] + __builtin_popcountll(block[i]);
// 		}
// 	}

// 	int rank1(int i) const {
// 		if (i <= 0) return 0;
// 		int b = i / 64;
// 		uint64_t mask = (1ULL << (i % 64)) - 1;
// 		if (i % 64 == 0) mask = 0; 
// 		return count[b] + __builtin_popcountll(block[b] & mask);
// 	}

// 	int rank0(int i) const {
// 		return i - rank1(i);
// 	}
// };

// template <typename T, int MAXLOG = 30>
// struct WaveletMatrix {
// 	int n;
// 	vector<BitVector> mat;
// 	vector<int> zs;
// 	vector<vector<ll>> sum0;

// 	WaveletMatrix(vector<T> v) : n(v.size()), mat(MAXLOG), zs(MAXLOG), sum0(MAXLOG) {
// 		vector<T> l(n), r(n);
// 		for (int depth = MAXLOG - 1; depth >= 0; --depth) {
// 			mat[depth] = BitVector(n);
// 			sum0[depth].assign(n + 1, 0);
// 			int left = 0, right = 0;
// 			for (int i = 0; i < n; ++i) {
// 				bool bit = (v[i] >> depth) & 1;
// 				sum0[depth][i + 1] = sum0[depth][i];
// 				if (!bit) {
// 					sum0[depth][i + 1] += v[i];
// 				}
// 				if (bit) {
// 					mat[depth].set(i);
// 					r[right++] = v[i];
// 				} else {
// 					l[left++] = v[i];
// 				}
// 			}
// 			mat[depth].build();
// 			zs[depth] = left;

// 			for (int i = 0; i < left; ++i) v[i] = l[i];
// 			for (int i = 0; i < right; ++i) v[left + i] = r[i];
// 		}
// 	}

// 	T access(int k) const {
// 		T res = 0;
// 		for (int depth = MAXLOG - 1; depth >= 0; --depth) {
// 			bool bit = (mat[depth].rank1(k + 1) - mat[depth].rank1(k)) > 0;
// 			res |= (T(bit) << depth);
// 			if (bit) {
// 				k = zs[depth] + mat[depth].rank1(k);
// 			} else {
// 				k = mat[depth].rank0(k);
// 			}
// 		}
// 		return res;
// 	}

// 	// [l, r) の k 番目に小さい値
// 	T kth_smallest(int l, int r, int k) const {
// 		T res = 0;
// 		for (int depth = MAXLOG - 1; depth >= 0; --depth) {
// 			int cnt0 = mat[depth].rank0(r) - mat[depth].rank0(l);
// 			if (k < cnt0) {
// 				l = mat[depth].rank0(l);
// 				r = mat[depth].rank0(r);
// 			} else {
// 				res |= (T(1) << depth);
// 				k -= cnt0;
// 				l = zs[depth] + mat[depth].rank1(l);
// 				r = zs[depth] + mat[depth].rank1(r);
// 			}
// 		}
// 		return res;
// 	}

// 	// [l, r) の k 番目に大きい値
// 	T kth_largest(int l, int r, int k) const {
// 		return kth_smallest(l, r, r - l - k - 1);
// 	}

// 	// [l, r) に含まれる upper 未満の要素数
// 	int range_freq(int l, int r, T upper) const {
// 		int res = 0;
// 		for (int depth = MAXLOG - 1; depth >= 0; --depth) {
// 			bool bit = (upper >> depth) & 1;
// 			int cnt0 = mat[depth].rank0(r) - mat[depth].rank0(l);
// 			if (bit) {
// 				res += cnt0;
// 				l = zs[depth] + mat[depth].rank1(l);
// 				r = zs[depth] + mat[depth].rank1(r);
// 			} else {
// 				l = mat[depth].rank0(l);
// 				r = mat[depth].rank0(r);
// 			}
// 		}
// 		return res;
// 	}

// 	// [l, r) に含まれる [lower, upper) の要素数
// 	int range_freq(int l, int r, T lower, T upper) const {
// 		return range_freq(l, r, upper) - range_freq(l, r, lower);
// 	}

// 	// [l, r) で upper 未満の最大値
// 	T prev_value(int l, int r, T upper) const {
// 		int cnt = range_freq(l, r, upper);
// 		if (cnt == 0) return -1; 
// 		return kth_smallest(l, r, cnt - 1);
// 	}

// 	// [l, r) で lower 以上の最小値
// 	T next_value(int l, int r, T lower) const {
// 		int cnt = range_freq(l, r, lower);
// 		if (cnt == r - l) return -1;
// 		return kth_smallest(l, r, cnt);
// 	}

// 	ll range_sum(int l, int r, T upper) const {
// 		ll res = 0;
// 		for (int depth = MAXLOG - 1; depth >= 0; --depth) {
// 			if (l >= r) break;			
// 			bool bit = (upper >> depth) & 1;
// 			int cnt0_l = mat[depth].rank0(l);
// 			int cnt0_r = mat[depth].rank0(r);
			
// 			if (bit) {
// 				res += sum0[depth][r] - sum0[depth][l];
// 				l = zs[depth] + (l - cnt0_l);
// 				r = zs[depth] + (r - cnt0_r);
// 			} else {
// 				l = cnt0_l;
// 				r = cnt0_r;
// 			}
// 		}
// 		return res;
// 	}
// };

vec<ll> prime(ll n) {
	vec<bool> is_prime(n + 1, true);
	vec<ll> primes;
	if (n < 2) return primes;
	is_prime[0] = is_prime[1] = false;
	for (ll i = 2; i * i <= n; ++i) {
		if (is_prime[i]) {
			for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
		}
	}
	for (ll i = 2; i <= n; ++i) {
		if (is_prime[i]) primes.pb(i);
	}
	return primes;
}

// set<ll> prime_set(ll n) {
// 	vec<bool> is_prime(n + 1, true);
// 	set<ll> primes;
// 	if (n < 2) return primes;
// 	is_prime[0] = is_prime[1] = false;
// 	for (ll i = 2; i * i <= n; ++i) {
// 		if (is_prime[i]) {
// 			for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
// 		}
// 	}
// 	for (ll i = 2; i <= n; ++i) {
// 		if (is_prime[i]) primes.insert(i);
// 	}
// 	return primes;
// }

// struct Node {
// 	int min_val;
// 	ll sum_val;
// 	ll right_contrib;
// };

// struct SegTree {
// 	int n;
// 	vec<Node> tree;
// 	SegTree(int _n) : n(_n), tree(4 * n) {}
// 	ll calc(int node, int l, int r, int V) {
// 		if (l == r) {
// 			return min(V, tree[node].min_val);
// 		}
// 		int mid = l + (r - l) / 2;
// 		int lc = 2 * node;
// 		int rc = 2 * node + 1;
// 		if (V <= tree[lc].min_val) {
// 			return 1LL * V * (mid - l + 1) + calc(rc, mid + 1, r, V);
// 		}
// 		else {
// 			return calc(lc, l, mid, V) + tree[node].right_contrib;
// 		}
// 	}
// 	void update(int node, int l, int r, int pos, int val) {
// 		if (l == r) {
// 			tree[node].min_val = val;
// 			tree[node].sum_val = val;
// 			tree[node].right_contrib = 0;
// 			return ;
// 		}
// 		int mid = l + (r - l) / 2;
// 		int lc = 2 * node;
// 		int rc = 2 * node + 1;
// 		if (pos <= mid) {
// 			update(lc, l, mid, pos, val);
// 		} else {
// 			update(rc, mid + 1, r, pos, val);
// 		}
// 		tree[node].min_val = min(tree[lc].min_val, tree[rc].min_val);
// 		tree[node].right_contrib = calc(rc, mid + 1, r, tree[lc].min_val);
// 		tree[node].sum_val = tree[lc].sum_val + tree[node].right_contrib;
// 	}

// 	void update(int pos, int val) {
// 		update(1, 0, n - 1, pos, val);
// 	}
// 	ll get_sum() {
// 		return tree[1].sum_val;
// 	}
// };

// template <class S, S (*op)(S, S), S (*e)()>
// struct PersistentSegTree {
// 	struct Node {
// 		S val;
// 		int l, r;
// 	};

// 	vector<Node> tree;
// 	int n;

// 	PersistentSegTree(int n_) : n(n_) {
// 		tree.push_back({e(), 0, 0}); 
// 	}

// 	int build(const vector<S>& v) {
// 		auto dfs = [&](auto& self, int l, int r) -> int {
// 			if (l + 1 == r) {
// 				tree.push_back({v[l], 0, 0});
// 				return tree.size() - 1;
// 			}
// 			int m = (l + r) / 2;
// 			int lch = self(self, l, m);
// 			int rch = self(self, m, r);
// 			tree.push_back({op(tree[lch].val, tree[rch].val), lch, rch});
// 			return tree.size() - 1;
// 		};
// 		return dfs(dfs, 0, n);
// 	}

// 	int set(int root, int k, S x) {
// 		auto dfs = [&](auto& self, int p, int l, int r) -> int {
// 			int u = tree.size();
// 			tree.push_back(tree[p]); 
			
// 			if (l + 1 == r) {
// 				tree[u].val = x;
// 				return u;
// 			}
			
// 			int m = (l + r) / 2;
// 			if (k < m) {
// 				tree[u].l = self(self, tree[p].l, l, m);
// 			} else {
// 				tree[u].r = self(self, tree[p].r, m, r);
// 			}
			
// 			tree[u].val = op(tree[tree[u].l].val, tree[tree[u].r].val);
// 			return u;
// 		};
// 		return dfs(dfs, root, 0, n);
// 	}

// 	S prod(int root, int a, int b) {
// 		auto dfs = [&](auto& self, int p, int l, int r) -> S {
// 			if (p == 0 || r <= a || b <= l) return e();
// 			if (a <= l && r <= b) return tree[p].val;
			
// 			int m = (l + r) / 2;
// 			return op(self(self, tree[p].l, l, m), self(self, tree[p].r, m, r));
// 		};
// 		return dfs(dfs, root, 0, n);
// 	}
// };

// struct SegTreeBeats {
//     int n, size;

//     struct Node {
//         ll sum;
//         ll max_v;
//         ll max2_v;
//         ll max_c;
//         ll min_v;
//         ll min2_v;
//         ll min_c;
//         ll lazy_add;
//         ll len;
//     };

//     vector<Node> tree;

//     SegTreeBeats(const vector<ll>& a) {
//         n = a.size();
//         size = 1;
//         while (size < n) size *= 2;
//         tree.assign(2 * size, {0, -INFLL, -INFLL, 0, INFLL, INFLL, 0, 0, 0});
//         build(1, 0, size, a);
//     }

//     void push_up(int k) {
//         Node &p = tree[k], &l = tree[2 * k], &r = tree[2 * k + 1];
//         p.sum = l.sum + r.sum;

//         if (l.max_v == r.max_v) {
//             p.max_v = l.max_v;
//             p.max_c = l.max_c + r.max_c;
//             p.max2_v = max(l.max2_v, r.max2_v);
//         } else if (l.max_v > r.max_v) {
//             p.max_v = l.max_v;
//             p.max_c = l.max_c;
//             p.max2_v = max(l.max2_v, r.max_v);
//         } else {
//             p.max_v = r.max_v;
//             p.max_c = r.max_c;
//             p.max2_v = max(l.max_v, r.max2_v);
//         }

//         if (l.min_v == r.min_v) {
//             p.min_v = l.min_v;
//             p.min_c = l.min_c + r.min_c;
//             p.min2_v = min(l.min2_v, r.min2_v);
//         } else if (l.min_v < r.min_v) {
//             p.min_v = l.min_v;
//             p.min_c = l.min_c;
//             p.min2_v = min(l.min2_v, r.min_v);
//         } else {
//             p.min_v = r.min_v;
//             p.min_c = r.min_c;
//             p.min2_v = min(l.min_v, r.min2_v);
//         }
//     }

//     void apply_add(int k, ll x) {
//         if (x == 0) return;
//         tree[k].sum += x * tree[k].len;
//         tree[k].max_v += x;
//         if (tree[k].max2_v != -INFLL) tree[k].max2_v += x;
//         tree[k].min_v += x;
//         if (tree[k].min2_v != INFLL) tree[k].min2_v += x;
//         tree[k].lazy_add += x;
//     }

//     void apply_chmin(int k, ll x) {
//         if (tree[k].max_v <= x) return;
//         tree[k].sum -= (tree[k].max_v - x) * tree[k].max_c;
//         if (tree[k].min_v == tree[k].max_v) tree[k].min_v = x;
//         else if (tree[k].min2_v == tree[k].max_v) tree[k].min2_v = x;
//         tree[k].max_v = x;
//     }
	
//     void apply_chmax(int k, ll x) {
//         if (tree[k].min_v >= x) return;
//         tree[k].sum += (x - tree[k].min_v) * tree[k].min_c;
//         if (tree[k].max_v == tree[k].min_v) tree[k].max_v = x;
//         else if (tree[k].max2_v == tree[k].min_v) tree[k].max2_v = x;
//         tree[k].min_v = x;
//     }

//     void push_down(int k) {
//         if (tree[k].lazy_add != 0) {
//             apply_add(2 * k, tree[k].lazy_add);
//             apply_add(2 * k + 1, tree[k].lazy_add);
//             tree[k].lazy_add = 0;
//         }
//         if (tree[k].max_v < tree[2 * k].max_v) apply_chmin(2 * k, tree[k].max_v);
//         if (tree[k].max_v < tree[2 * k + 1].max_v) apply_chmin(2 * k + 1, tree[k].max_v);

//         if (tree[k].min_v > tree[2 * k].min_v) apply_chmax(2 * k, tree[k].min_v);
//         if (tree[k].min_v > tree[2 * k + 1].min_v) apply_chmax(2 * k + 1, tree[k].min_v);
//     }

//     void build(int k, int l, int r, const vector<ll>& a) {
//         tree[k].len = r - l;
//         if (r - l == 1) {
//             if (l < n) {
//                 tree[k].sum = tree[k].max_v = tree[k].min_v = a[l];
//                 tree[k].max_c = tree[k].min_c = 1;
//             }
//             return;
//         }
//         int mid = (l + r) / 2;
//         build(2 * k, l, mid, a);
//         build(2 * k + 1, mid, r, a);
//         push_up(k);
//     }

//     void update_chmin(int k, int l, int r, int ql, int qr, ll x) {
//         if (qr <= l || r <= ql || tree[k].max_v <= x) return;
//         if (ql <= l && r <= qr && tree[k].max2_v < x) {
//             apply_chmin(k, x); return;
//         }
//         push_down(k);
//         int mid = (l + r) / 2;
//         update_chmin(2 * k, l, mid, ql, qr, x);
//         update_chmin(2 * k + 1, mid, r, ql, qr, x);
//         push_up(k);
//     }

//     void update_chmax(int k, int l, int r, int ql, int qr, ll x) {
//         if (qr <= l || r <= ql || tree[k].min_v >= x) return;
//         if (ql <= l && r <= qr && tree[k].min2_v > x) {
//             apply_chmax(k, x); return;
//         }
//         push_down(k);
//         int mid = (l + r) / 2;
//         update_chmax(2 * k, l, mid, ql, qr, x);
//         update_chmax(2 * k + 1, mid, r, ql, qr, x);
//         push_up(k);
//     }

//     void update_add(int k, int l, int r, int ql, int qr, ll x) {
//         if (qr <= l || r <= ql) return;
//         if (ql <= l && r <= qr) {
//             apply_add(k, x); return;
//         }
//         push_down(k);
//         int mid = (l + r) / 2;
//         update_add(2 * k, l, mid, ql, qr, x);
//         update_add(2 * k + 1, mid, r, ql, qr, x);
//         push_up(k);
//     }

//     ll query_sum(int k, int l, int r, int ql, int qr) {
//         if (qr <= l || r <= ql) return 0;
//         if (ql <= l && r <= qr) return tree[k].sum;
//         push_down(k);
//         int mid = (l + r) / 2;
//         return query_sum(2 * k, l, mid, ql, qr) + query_sum(2 * k + 1, mid, r, ql, qr);
//     }

//     void chmin(int l, int r, ll x) { update_chmin(1, 0, size, l, r, x); }
//     void chmax(int l, int r, ll x) { update_chmax(1, 0, size, l, r, x); }
//     void add(int l, int r, ll x)   { update_add(1, 0, size, l, r, x); }
//     ll sum(int l, int r)           { return query_sum(1, 0, size, l, r); }
// };

// const int MAX_S = 5005;
// vvec<ll> c_memo(MAX_S, vec<ll>(MAX_S, 0));

// void init_comb(ll m) {
// 	rep(i, 0, MAX_S) {
// 		c_memo[i][0] = 1;
// 		repp(j, 1, i) {
// 			c_memo[i][j] = (c_memo[i - 1][j - 1] + c_memo[i - 1][j]) % m;
// 		}
// 	}
// }

// ll get_j(Fenwick<ll>& bit, ll target, ll n) {
// 	ll ok = n, ng = 0;
// 	while (ok - ng > 1) {
// 		ll mid = (ok + ng) / 2;
// 		if (bit.sum(mid) >= target) ok = mid;
// 		else ng = mid;
// 	}
// 	return ok;
// }

// using S = ll;
// using F = ll;

// struct S {
// };

// struct F {
// };

// S op(S l, S r) {
// 	return {l.sum + r.sum, l.len + r.len};
// }

// S e() {
// 	return {0, 0};
// }

// S mapping(F f, S x) {
// 	return {x.sum + f * x.len, x.len};
// }

// F comp(F f, F g) {
// 	return f + g;
// }

// F id() {
// 	return 0;
// }

void solve() {
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	(void)INF;
	(void)INFLL;
	int T;
	T = 1;
	// cin >> T;
	while(T--) solve();
	return 0;
}

/*

ライブラリURL

https://github.com/KWEKE633/My_atcoder

*/
