// O(n log n) with doubles
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SZ(a) ((int)(a).size())
#define ALL(a) (a).begin(), (a).end()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pr = pair<int, int>;
using T = double;

constexpr int kInf = 1000 * 1000 * 1000 + 7;
constexpr long long kInfLL = 1e18;

struct Megaset {
  vi keys;
  vector<T> vals;
  T add;

  Megaset() {}
  Megaset(const vi& keys): keys(keys), vals(SZ(keys)), add(0) { sort(ALL(this->keys)); }

  T Value(int a) { return vals[Id(a)] + add; }
  void Set(int a, T val) { vals[Id(a)] = val - add; }
  void AddAll(T val) { add += val; }
  int Id(int a) { return lower_bound(ALL(keys), a) - keys.begin(); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n, c;
    cin >> n >> c;
    --c;

    vector<T> probs(n);
    probs[c] = 1;

    vvi g(n);
    REP(i, n - 1) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector<Megaset> s(n);
    REP(i, n) s[i] = Megaset(g[i]);

    int m;
    cin >> m;
    vi path(m);
    for (int &e: path) cin >> e, --e;

    T result = 0;
    int prv = -1;
    for (int v: path) {
      if (prv >= 0) {
        probs[v] += s[prv].Value(v);
        s[prv].Set(v, 0);
      }
      result += probs[v];
      s[v].AddAll(probs[v] / SZ(g[v]));
      probs[v] = 0;
      prv = v;
    }

    cout << setprecision(15) << fixed << result << '\n';
  }
}