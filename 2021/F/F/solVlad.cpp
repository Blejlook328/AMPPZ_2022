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

// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint998244353;

struct Dsu {
  int n;
  vi par, size;

  Dsu(int n): n(n), par(n), size(n, 1) { iota(ALL(par), 0); }
  int Root(int x) { return par[x] == x ? x : par[x] = Root(par[x]); }
  int Size(int x) { return size[Root(x)]; }
  void Merge(int x, int y) {
    x = Root(x); y = Root(y);
    if (x == y) return;
    if (size[x] < size[y]) swap(x, y);
    size[x] += size[y]; par[y] = x;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n;
    cin >> n;
    vi a(n);
    REP(i, n) cin >> a[i];
    int total = 0;
    vi difs(n + 1);
    for (int i = n - 1; i >= 0; --i) {
      total += a[i];
      difs[i] = a[i] - difs[i + 1];
    }
    auto get_dif = [&](int l, int r) {
      if (r < l) return 0;
      return difs[l] + ((r - l) % 2 ? -1 : +1) * difs[r + 1];
    };
    Dsu d(n);
    int mx = *max_element(a.begin(), a.end());
    for (int b = 1; b <= mx; ++b) {
      int cnt = 0, sum = 0;
      REP(i, n) {
        if (a[i] < b) {
          int size = d.Size(i);
          sum += (cnt % 2 == 0 ? +1 : -1) * get_dif(i, i + size - 1);
          cnt += size;
          if (i > 0 && max(a[i - 1], a[i]) <= b) d.Merge(i, i - 1);
          i += size - 1;
          continue;
        }

        int c = a[i] / b, r = a[i] % b;
        if (r == 0) {
          if (c % 2 == 0) continue;
          sum += cnt % 2 ? -b : +b;
          cnt += c;
        } else {
          int val = c % 2 ? b - r : r;
          sum += cnt % 2 ? -val : val;
          cnt += c + 1;
        }

        if (i > 0 && max(a[i - 1], a[i]) <= b) d.Merge(i, i - 1);
      }
      cout << (total + sum) / 2 << '\n';
    }
  }
}