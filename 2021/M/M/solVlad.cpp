// Model solution in O(n log n + q^5 log q)
// Polynomial interpolation can be done much faster, but who cares
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

constexpr int kMod = 1000 * 1000 * 1000 + 7;
constexpr int kN = 35;

struct Tree {
  struct Node {
    int type, val;
    vector<Node*> c;

    Node(int val): type(0), val(val) {}
    Node(const vector<Node*>& c): type(1), c(c) {}

    ~Node() { REP(i, SZ(c)) delete c[i]; }
  };

  Node* root = nullptr;
  
  Tree(const vi& a) { root = Build(0, SZ(a) - 1, a); }
  ~Tree() { delete root; }

  pr Split(int l, int r) {
    int len = r - l + 1;
    int s1 = len / 3, s2 = s1;
    if (len % 3 >= 1) ++s1;
    if (len % 3 >= 2) ++s2;
    return {l + s1, l + s1 + s2};
  }

  int GetNumber(int l, int r, const vi& a) {
    if (l == r) return a[l];
    if (l + 1 == r) return min(a[l], a[l + 1]);
    auto [m1, m2] = Split(l, r);
    int x = GetNumber(l, m1 - 1, a);
    int y = GetNumber(m1, m2 - 1, a);
    int z = GetNumber(m2, r, a);
    return x + y + z - max({x, y, z}) - min({x, y, z});
  }

  Node* Build(int l, int r, const vi& a) {
    if (l == r) return new Node(a[l]);
    bool found_undecided = false;
    for (int i = l; i <= r; ++i) {
      if (a[i] == -1) {
        found_undecided = true;
        break;
      }
    }
    if (!found_undecided) return new Node(GetNumber(l, r, a));
    if (l + 1 == r) return new Node({Build(l, l, a), Build(r, r, a)});
    auto [m1, m2] = Split(l, r);
    Node *x = Build(l, m1 - 1, a);
    Node *y = Build(m1, m2 - 1, a);
    Node *z = Build(m2, r, a);
    return new Node({x, y, z});
  }

  struct State {
    int winner, lesser, greater;
    friend bool operator <(const State& a, const State& b) {
      return make_tuple(a.winner, a.lesser, a.greater) <
             make_tuple(b.winner, b.lesser, b.greater);
    }
  };

  map<State, int> Count(Node *root, int val) {
    if (root->type == 0) {
      map<State, int> result;
      if (root->val < 0) {
        REP(winner, 3) {
          int lesser = (winner == 0), greater = (winner == 2);
          result[{winner, lesser, greater}] = 1;
        }
      } else {
        int winner{};
        if (root->val < val) winner = 0; else
        if (root->val == val) winner = 1; else
        winner = 2;
        result[{winner, 0, 0}] = 1;
      }
      return result;
    }

    map<State, int> cur_states = {{State{0, 0, 0}, 1}};
    REP(i, SZ(root->c)) {
      map<State, int> new_states;
      auto child_states = Count(root->c[i], val);
      for (const auto& [cur_state, cur_val] : cur_states) {
        if (cur_val == 0) continue;
        for (const auto& [child_state, child_val] : child_states) {
          if (child_val == 0) continue;
          int winner = cur_state.winner * 3 + child_state.winner;
          int lesser = cur_state.lesser + child_state.lesser;
          int greater = cur_state.greater + child_state.greater;
          State state = {winner, lesser, greater};
          new_states[state] = (new_states[state] + 1LL * cur_val * child_val) % kMod;
        }
      }
      cur_states = new_states;
    }

    map<State, int> result;
    for (const auto& [cur_state, cur_val] : cur_states) {
      if (!cur_val) continue;
      vi cands; int mask = cur_state.winner;
      REP(i, SZ(root->c)) {
        cands.push_back(mask % 3);
        mask /= 3;
      }
      sort(ALL(cands));
      int winner = SZ(cands) == 2 ? cands[0] : cands[1];
      State state = {winner, cur_state.lesser, cur_state.greater};
      result[state] = (result[state] + cur_val) % kMod;
    }

    return result;
  }

  map<pr, int> CountConfigurations(int val) {
    map<pr, int> result;
    for (const auto& [state, val] : Count(root, val)) {
      if (state.winner != 1) continue;
      pr key = {state.lesser, state.greater};
      result[key] = (result[key] + val) % kMod;
    }
    return result;
  }
};

int Power(int a, int n) {
  int result = 1;
  while (n > 0) {
    if (n % 2) result = (1LL * result * a) % kMod;
    a = (1LL * a * a) % kMod;
    n /= 2;
  }
  return result;
}

int Inv(int a) {
  return Power(a, kMod - 2);
}

vi operator *(const vi& a, const vi& b) {
  vi c(SZ(a) + SZ(b));
  REP(i, SZ(a)) REP(j, SZ(b)) c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % kMod;
  return c;
}
vi operator *(const vi& a, int b) {
  vi c = a;
  REP(i, SZ(c)) c[i] = (1LL * c[i] * b) % kMod;
  return c;
}
vi operator +(const vi& a, const vi& b) {
  vi c(max(SZ(a), SZ(b)));
  REP(i, SZ(c)) c[i] = ((i < SZ(a) ? a[i] : 0) + (i < SZ(b) ? b[i] : 0)) % kMod;
  return c;
}

// sum { i from l to r} (x + i)^a * (y - i)^b
int ComputeSum(int x, int a, int y, int b, int num) {
  vi pts;
  int sum = 0;
  REP(i, a + b + 10) {
    int first = Power((x + i) % kMod, a);
    int second = Power((y + kMod - i) % kMod, b);
    sum = (sum + 1LL * first * second) % kMod;
    pts.push_back(sum);
  }
  if (num < SZ(pts)) return pts[num];
  vi poly(1);
  REP(i, SZ(pts)) {
    vi cur(1, 1);
    REP(j, SZ(pts)) if (i != j) {
      vi now(2, 1); now[0] = (kMod - j) % kMod;
      now = now * Inv((kMod + i - j) % kMod);
      cur = cur * now;
    }
    poly = poly + cur * pts[i];
  }
  int result = 0;
  reverse(ALL(poly));
  REP(i, SZ(poly)) result = (1LL * result * num + poly[i]) % kMod;
  return result;
}

void Solve() {
  int n, m;
  cin >> n >> m;

  vi a(n);
  REP(i, n) cin >> a[i];

  Tree tree(a);
  int undecided = count(ALL(a), -1);

  sort(ALL(a)); reverse(ALL(a));
  while (!a.empty() && a.back() == -1) a.pop_back();
  reverse(ALL(a));

  auto count_interval = [&](int l, int r) {
    if (l > r) return 0;
    int upper = upper_bound(ALL(a), l) - a.begin();
    int lower = lower_bound(ALL(a), l) - a.begin();
    int same = undecided + upper - lower;
    int lesser = lower;
    int greater = SZ(a) - upper;
    if (lesser + same <= (n - 1) / 2) return 0;
    if (greater + same <= n / 2) return 0;
    int result = 0;
    for (const auto& [state, val]: tree.CountConfigurations(l)) {
      int cur_lesser = lesser + state.first;
      int cur_greater = greater + state.second;
      int cur_same = (upper - lower) + (undecided - state.first - state.second);
      if (cur_lesser + cur_same > (n - 1) / 2 && cur_greater + cur_same > n / 2) {
        int sum_val = ComputeSum(l, state.first, m - l - 1, state.second, r - l);
        result = (result + 1LL * val * sum_val) % kMod;
      }
    }

    return result;
  };

  int result = 0;
  REP(i, SZ(a)) {
    if (i == 0 || a[i - 1] != a[i]) {
      result = (result + count_interval(a[i], a[i])) % kMod;
    }
    if (i > 0 && a[i - 1] < a[i]) {
      result = (result + count_interval(a[i - 1] + 1, a[i] - 1)) % kMod;
    }
  }

  if (a.empty()) {
    result = (result + count_interval(0, m - 1)) % kMod;
  } else {
    result = (result + count_interval(0, a[0] - 1)) % kMod;
    result = (result + count_interval(a.back() + 1, m - 1)) % kMod;
  }

  cout << result << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) Solve();
}