// O(n * k)
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

ll Sqr(ll x) { return x * x; }
ll DistSqr(const pr& a, const pr& b) {
  return Sqr(a.first - b.first) + Sqr(a.second - b.second);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n, k;
    cin >> n >> k;
    vector<pr> a(n);
    REP(i, n) cin >> a[i].first >> a[i].second;
    vi repr = {0};
    vector<ll> dst(n);
    REP(i, n) dst[i] = DistSqr(a[0], a[i]);
    REP(i, k) {
      int id = max_element(ALL(dst)) - begin(dst);
      repr.push_back(id);
      REP(i, n) dst[i] = min(dst[i], DistSqr(a[i], a[id]));
    }
    REP(i, n) {
      ll min_dist = kInfLL;
      int id = -1;
      REP(j, k) {
        ll dist = DistSqr(a[i], a[repr[j]]);
        if (dist < min_dist) {
          min_dist = dist;
          id = j;
        }
      }
      cout << id + 1 << ' ';
    }
    cout << '\n';
  }
}