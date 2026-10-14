// atcoder::memo

// [LPS]

// vec<int> u;
// vec<int> lps(m, 0);
// rep(i, 1, 100) {
// 	int j = lps[i - 1];
// 	while (j > 0 && u[i] != u[j]) j = lps[j - 1];
// 	if (u[i] == u[j]) j++;
// 	lps[i] = j;
// }

// [LIS]

// int cnt = 0;
// 	int cur = 0;
// 	vec<int> r;
// 	rep(i, 0, n) {
// 		if (p[i] > cur) {
// 			cnt++;
// 			cur = p[i];
// 		} else {
// 			r.push_back(p[i]);
// 		}
// 	}
// 	vec<int> lis;
// 	for (int x : r) {
// 		auto it = lower_bound(lis.begin(), lis.end(), x);
// 		if (it == lis.end()) {
// 			lis.pb(x);
// 		} else *it = x;
// 	}
// 	cout << cnt + lis.size() << el;
