#include "All.hpp"

//　二項係数

struct Combination {
  vec<mint> fact, inv;
  Combination(int n) : fact(n + 1), inv(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    inv[n] = fact[n].inv();
    for (int i = n; i >= 1; i--) inv[i - 1] = inv[i] * i;
  }
  mint nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv[r] * inv[n - r];
  }
};



struct DSU { // 自作DSUテンプレ
  int n;
  vector<int> parent, sz;
  vector<vector<int>> best; // 各連結成分の上位 K 個（降順）

  static constexpr int K = 10;

  DSU(int n_) : n(n_), parent(n_ + 1), sz(n_ + 1), best(n_ + 1) {
    for (int i = 1; i <= n; i++) {
      parent[i] = i;
      sz[i] = 1;
      best[i] = { i };
    }
  }

  int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
  }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;

    // union by size
    if (sz[x] < sz[y]) swap(x, y);

    parent[y] = x;
    sz[x] += sz[y];

    // best マージ（最大 2K → K）
    best[x].insert(best[x].end(), best[y].begin(), best[y].end());
    nth_element(
      best[x].begin(),
      best[x].begin() + min((int)best[x].size(), K),
      best[x].end(),
      greater<int>()
    );
    sort(best[x].begin(), best[x].begin() + min((int)best[x].size(), K), greater<int>());
    if ((int)best[x].size() > K) best[x].resize(K);

    return true;
  }

  // v を含む連結成分の k 番目に大きい頂点番号（1-indexed）
  int kth_largest(int v, int k) {
    v = find(v);
    if ((int)best[v].size() < k) return -1;
    return best[v][k - 1];
  }
};


// Fenwick木

template<class T>
struct Fenwick {
  int n;
  vector<T> bit;

  Fenwick(int n_) : n(n_), bit(n_ + 1, T()) {}

  // a[i] += x (1-indexed)
  void add(int i, T x) {
    for (; i <= n; i += i & -i) {
      bit[i] += x;
    }
  }

  // sum of [1, i]
  T sum(int i) const {
    T s = T();
    for (; i > 0; i -= i & -i) {
      s += bit[i];
    }
    return s;
  }

  // sum of [l, r]
  T sum(int l, int r) const {
    if (l > r) return T();
    return sum(r) - sum(l - 1);
  }
};

struct FenwickRange {
  int n;
  Fenwick<long long> fw1, fw2;

  FenwickRange(int n_) : n(n_), fw1(n_), fw2(n_) {}

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

//　セグ木

template<class S>
struct SegTree {
  int n;
  vector<S> seg;
  S e; // 単位元
  function<S(S, S)> op;

  SegTree(int n_, S e_, function<S(S, S)> op_)
      : e(e_), op(op_) {
    n = 1;
    while (n < n_) n <<= 1;
    seg.assign(2 * n, e);
  }

  SegTree(const vector<S>& v, S e_, function<S(S, S)> op_)
      : e(e_), op(op_) {
    int sz = v.size();
    n = 1;
    while (n < sz) n <<= 1;
    seg.assign(2 * n, e);
    for (int i = 0; i < sz; i++) seg[n + i] = v[i];
    for (int i = n - 1; i > 0; i--) seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
  }

  // a[p] = x
  void set(int p, S x) {
    p += n;
    seg[p] = x;
    while (p >>= 1) {
      seg[p] = op(seg[p << 1], seg[p << 1 | 1]);
    }
  }

  // query [l, r)
  S prod(int l, int r) const {
    S left = e, right = e;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) left = op(left, seg[l++]);
      if (r & 1) right = op(seg[--r], right);
    }
    return op(left, right);
  }

  S all_prod() const {
    return seg[1];
  }
};

// struct SegTree {
//   int n;
//   vector<long long> seg;

//   SegTree(int n_) {
//     n = 1;
//     while (n < n_) n <<= 1;
//     seg.assign(2 * n, 0);
//   }

//   void set(int p, long long x) {
//     p += n;
//     seg[p] = x;
//     while (p >>= 1) {
//       seg[p] = seg[p << 1] + seg[p << 1 | 1];
//     }
//   }

//   long long prod(int l, int r) const {
//     long long res = 0;
//     for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
//       if (l & 1) res += seg[l++];
//       if (r & 1) res += seg[--r];
//     }
//     return res;
//   }
// };

struct LazySegTree {
  int n;
  vector<long long> seg, lazy;

  LazySegTree(int n_) {
    n = 1;
    while (n < n_) n <<= 1;
    seg.assign(2 * n, 0);
    lazy.assign(2 * n, 0);
  }

  void push(int k) {
    if (lazy[k] != 0) {
      seg[k << 1] += lazy[k];
      seg[k << 1 | 1] += lazy[k];
      lazy[k << 1] += lazy[k];
      lazy[k << 1 | 1] += lazy[k];
      lazy[k] = 0;
    }
  }

  void range_add(int a, int b, long long x, int k, int l, int r) {
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      seg[k] += x;
      lazy[k] += x;
      return;
    }
    push(k);
    int m = (l + r) >> 1;
    range_add(a, b, x, k << 1, l, m);
    range_add(a, b, x, k << 1 | 1, m, r);
    seg[k] = max(seg[k << 1], seg[k << 1 | 1]);
  }

  void range_add(int l, int r, long long x) {
    range_add(l, r, x, 1, 0, n);
  }

  long long range_max(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return LLONG_MIN;
    if (a <= l && r <= b) return seg[k];
    push(k);
    int m = (l + r) >> 1;
    return max(
      range_max(a, b, k << 1, l, m),
      range_max(a, b, k << 1 | 1, m, r)
    );
  }

  long long range_max(int l, int r) {
    return range_max(l, r, 1, 0, n);
  }
};
