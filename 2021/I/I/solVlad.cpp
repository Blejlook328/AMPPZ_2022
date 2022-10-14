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

// https://cp-algorithms.com/graph/dinic.html
struct FlowEdge {
  int v, u;
  int cap, flow = 0;
  FlowEdge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  const int flow_inf = 1e9;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, int cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  int dfs(int v, int pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  int flow() {
    int f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (int pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    return f;
  }
};

template<int K>
struct Trie {
  struct Node {
    int t[2] = {0, 0}, cnt = 0;
  };

  vector<Node> nodes = { Node{} };

  void Add(int x) {
    int v = 0;
    for (int i = K; i >= 0; --i) {
      int b = (x >> i) & 1;
      if (!nodes[v].t[b]) {
        nodes.push_back(Node{});
        nodes[v].t[b] = SZ(nodes) - 1;
      }
      v = nodes[v].t[b];
      ++nodes[v].cnt;
    }
  }

  int Size() {
    return SZ(nodes);
  }

  void AddFlow(int v, Dinic& d) {
    int children = 0;
    REP(i, 2) if (nodes[v].t[i]) {
      int to = nodes[v].t[i];
      d.add_edge(v, to, d.flow_inf);
      AddFlow(to, d);
      ++children;
    }
    if (children == 0) {
      d.add_edge(v, d.t, nodes[v].cnt);
    }
  }

  void AddFlow(Dinic& d) {
    AddFlow(0, d);
  }

  vi GreaterVerts(int x, int k) {
    int v = 0;
    vi result;
    for (int i = K; i >= 0; --i) {
      int bx = (x >> i) & 1;
      int bk = (k >> i) & 1;
      if (!bk && nodes[v].t[bx ^ 1]) {
        result.push_back(nodes[v].t[bx ^ 1]);
      }
      if (!nodes[v].t[bx ^ bk]) break;
      v = nodes[v].t[bx ^ bk];
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    int n, k;
    cin >> n >> k;
    vi a(n);
    REP(i, n) cin >> a[i];
    int b = 20;
    while (~k & (1 << b)) --b;
    map<int,vi> groups;
    REP(i, n) groups[a[i] >> (b + 1)].push_back(a[i]);
    int result = 0;
    for (auto &[_, g]: groups) {
      Trie<20> trie;
      vi nums;
      for (int e: g) {
        int val = e % (1 << b);
        if (e & (1 << b)) {
          trie.Add(val);
        } else {
          nums.push_back(val);
        }
      }

      int total = trie.Size() + SZ(nums) + 2;
      Dinic d(total, total - 1, total - 2);
      trie.AddFlow(d);
      REP(i, SZ(nums)) {
        int id = trie.Size() + i;
        d.add_edge(d.s, id, 1);
        for (int ver: trie.GreaterVerts(nums[i], k % (1 << b))) {
          d.add_edge(id, ver, 1);
        }
      }
      int flow = d.flow();
      result = max(result, SZ(g) - flow);
    }
    cout << result << '\n';
  }
}