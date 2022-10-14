// O(n log n)
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SZ(a) ((int)(a).size())
#define ALL(a) (a).begin(), (a).end()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pr = pair<int, int>;

constexpr int kInf = 1000 * 1000 * 1000 + 7;
constexpr long long kInfLL = 1e18;

ll Inversions(vi& a) {
  int n = SZ(a);
  if (n == 1) return 0;
  int m = n / 2;
  vi lf(a.begin(), a.begin() + m), rt(a.begin() + m, a.end());
  ll result = Inversions(lf) + Inversions(rt);
  int i = 0, j = 0, pos = 0;
  while (i < SZ(lf) && j < SZ(rt)) {
    if (lf[i] <= rt[j]) {
      a[pos++] = lf[i++];
    } else {
      result += SZ(lf) - i;
      a[pos++] = rt[j++];
    }
  }
  while (i < SZ(lf)) a[pos++] = lf[i++];
  while (j < SZ(rt)) a[pos++] = rt[j++];
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n;
    cin >> n;

    vector<pr> a(n), b(n);
    REP(i, n) cin >> a[i].first;
    REP(i, n) cin >> a[i].second;
    REP(i, n) cin >> b[i].first;
    REP(i, n) cin >> b[i].second;
    for (int i = 0; i < n; i += 2) {
      swap(a[i].first, a[i].second);
      swap(b[i].first, b[i].second);
    }
    map<pr, vi> c;
    REP(i, n) c[a[i]].push_back(i);
    vi arr;
    bool failed = false;
    for (int i = n - 1; i >= 0; --i) {
      if (c[b[i]].empty()) {
        failed = true;
        break;
      }
      arr.push_back(c[b[i]].back());
      c[b[i]].pop_back();
    }
    reverse(ALL(arr));

    if (failed) {
      cout << -1 << '\n';
      continue;
    }

    cout << Inversions(arr) << '\n';
  }
}