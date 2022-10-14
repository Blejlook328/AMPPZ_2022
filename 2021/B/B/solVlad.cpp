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

struct Node {
  int x = 0, y = -1;

  friend Node operator +(const Node& a, const Node& b) {
    return a.x >= b.x ? a : b;
  }
};

struct SegTree {
  int n;
  vector<Node> t;

  SegTree(int n): n(n), t(4 * n) {}

  void Update(int pos, int val) {
    Update(1, 0, n - 1, pos, {val, pos});
  }

  Node Go(int l, int r) {
    return Go(1, 0, n - 1, l, r);
  }

  void Update(int v, int l, int r, int pos, const Node& val) {
    if (l == r) {
      t[v] = val;
      return;
    }
    int m = (l + r) / 2;
    if (pos <= m) {
      Update(2 * v, l, m, pos, val);
    } else {
      Update(2 * v + 1, m + 1, r, pos, val);
    }
    t[v] = t[2 * v] + t[2 * v + 1];
  }

  Node Go(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl) return Node{};
    if (l <= tl && r >= tr) return t[v];
    int tm = (tl + tr) / 2;
    return Go(2 * v, tl, tm, l, r) + Go(2 * v + 1, tm + 1, tr, l, r);
  }
};

void Rec(int v, int l, int r, SegTree& t, map<int, vi>& gr) {
  if (r < l) return;
  auto [u, p] = t.Go(l, r);
  gr[v].push_back(u);
  gr[u].push_back(v);
  Rec(u, l, p - 1, t, gr);
  Rec(u, p + 1, r, t, gr);
}

void Dfs(int v, int p, map<int, vi>& gr, vector<pair<int, int>>& ops, map<int, int>& ps, int sz) {
  vector<pair<int, int>> children;
  for (int to : gr[v]) {
    children.emplace_back((ps[v] - ps[to] + sz) % sz, to);
  }
  sort(ALL(children));
  for (auto [_, to] : children) {
    if (to == p) {
      ops.emplace_back(v, p);
      continue;
    } 
    Dfs(to, v, gr, ops, ps, sz);
  }
}

void GetOps(vector<pair<int, int>>& ops, vi& seq) {
  int mx_pos = max_element(ALL(seq)) - seq.begin();
  rotate(seq.begin(), seq.begin() + mx_pos, seq.end());
  SegTree t(SZ(seq));
  REP(i, SZ(seq)) t.Update(i, seq[i]);
  map<int, vi> gr;
  Rec(seq[0], 1, SZ(seq) - 1, t, gr);
  map<int, int> ps;
  REP(i, SZ(seq)) ps[seq[i]] = i;
  Dfs(seq[0], -1, gr, ops, ps, SZ(seq));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n, c;
    cin >> n >> c;

    vi a(n), b(n);
    map<int, int> p, pos;
    REP(i, n) {
      cin >> a[i] >> b[i];
      pos[a[i]] = i;
      p[b[i]] = a[i];
    }

    set<int> used;
    ll total = 0;
    vector<pair<int, int>> ops;
    REP(i, n) if (!used.count(a[i])) {
      int x = a[i];
      vi seq;
      while (!used.count(x)) {
        seq.push_back(x);
        used.insert(x);
        x = p[x];
      }

      if (SZ(seq) == 1) continue;
      ll cur = 2LL * (SZ(seq) - 1) * c;
      REP(i, SZ(seq)) cur += abs(seq[i] - seq[(i + 1) % SZ(seq)]);
      total += cur / 2;

      GetOps(ops, seq);
    }

    cout << total << ' ' << SZ(ops) << '\n';
    for (auto [x, y]: ops) {
      cout << pos[x] + 1 << ' ' << pos[y] + 1 << '\n';
      swap(pos[x], pos[y]);
    }
  }
}