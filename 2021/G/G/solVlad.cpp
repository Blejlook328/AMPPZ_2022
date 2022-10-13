// O(q log n)
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

constexpr long long kMax = 1e12;

struct Node {
  ll a{0}, b{0}, c{0};

  ll Apply(ll h) {
    return h <= a ? 0 : max(h, b) + c;
  }
};

Node operator +(const Node& first, const Node& second) {
  return {
    max(first.a, first.b <= second.a - first.c ? second.a - first.c : -kInfLL),
    max(first.b, second.b - first.c),
    first.c + second.c,
  };
}

struct Tree {
  int n;
  vector<Node> t;

  Tree(int n): n(n), t(4 * n) {}

  void Update(int pos, const Node& val) {
    Update(1, 0, n - 1, pos, val);
  }

  int Go(ll h, int pos) {
    auto val = Go(1, 0, n - 1, h, pos);
    if (val.first > 0) ++val.second;
    return val.second;
  }

  void Update(int v, int tl, int tr, int pos, const Node& val) {
    if (tl == tr) {
      t[v] = val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      Update(2 * v, tl, tm, pos, val);
    } else {
      Update(2 * v + 1, tm + 1, tr, pos, val);
    }
    t[v] = t[2 * v] + t[2 * v + 1];
  }

  pair<ll,int> Go(int v, int tl, int tr, ll h, int pos) {
    if (tr < pos) return {h, tr};
    if (tl == tr) {
      return {t[v].Apply(h), tl};
    }
    if (pos <= tl) {
      ll val = t[v].Apply(h);
      if (val > 0) return {val, tr};
    }
    int tm = (tl + tr) / 2;
    auto lf = Go(2 * v, tl, tm, h, pos);
    if (lf.first == 0) return lf;
    return Go(2 * v + 1, tm + 1, tr, lf.first, pos);
  }
};

void ChangePos(int pos, char c, ll val, Tree& t) {
  if (c == 'B') t.Update(pos, {val, 0, -val}); else 
  if (c == 'C') t.Update(pos, {0, val, 0}); else 
  if (c == 'K') t.Update(pos, {val - 1, kMax, -kMax + val}); else 
  throw 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n, q;
    ll h;
    cin >> n >> q >> h;
    Tree t(n);
    REP(i, n) {
      char c; ll val;
      cin >> c >> val;
      ChangePos(i, c, val, t);
    }
    REP(i, q) {
      char type;
      cin >> type;
      if (type == 'Z') {
        int pos; cin >> pos; --pos;
        char c; ll val;
        cin >> c >> val;
        ChangePos(pos, c, val, t);
      } else {
        int pos; cin >> pos; --pos;
        int result = t.Go(h, pos);
        if (result == pos) {
          cout << -1 << '\n';
          continue;
        }
        cout << result << '\n';
      }
    }
  }
}