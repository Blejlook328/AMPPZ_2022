#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SZ(a) ((int)(a).size())
#define ALL(a) (a).begin(), (a).end()

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pr = pair<int, int>;

constexpr int kInf = 1000 * 1000 * 1000 + 7;
constexpr long long kInfLL = 1e18;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  REP(_, t) {
    int n, m, q;
    cin >> n >> m >> q;
    int b = 2 * (n + m);
    const int dx[] = {-1, +1, 0, 0};
    const int dy[] = {0, 0, -1, +1};
    map<char,int> conv = {{'N', 0}, {'S', 1}, {'W', 2}, {'E', 3}};
    set<pr> pts_a;
    vector<pr> pts_b;
    REP(i, n) {
      string s;
      cin >> s;
      REP(j, m) {
        if (s[j] == 'A') pts_a.insert({i, j});
        if (s[j] == 'B') pts_b.push_back({i, j});
      }
    }
    bool inf = false;
    vector<char> dir(q);
    string s;
	cin >> s;
    REP(i, q) dir[i] = s[i];
    for (char c: dir) {
      int cnt = 0;
      while (true) {
        bool collide = false;
        for (auto [x, y]: pts_b) {
          x += dx[conv[c]]; y += dy[conv[c]];
          if (pts_a.count({x, y})) {
            collide = true;
            break;
          }
        }
        if (collide || cnt == b) break;
        ++cnt;
        for (auto& [x, y]: pts_b) {
          x += dx[conv[c]]; y += dy[conv[c]];
        }
      }
      if (cnt == b) {
        inf = true;
        break;
      }
    }

    if (inf) {
      cout << "TAK\n";
      continue;
    }

    cout << "NIE\n";
    // int min_x = kInf, max_x = -kInf;
    // int min_y = kInf, max_y = -kInf;
    // auto all = pts_b;
    // all.insert(all.end(), ALL(pts_a));
    // for (auto [x, y]: all) {
    //   min_x = min(min_x, x); max_x = max(max_x, x);
    //   min_y = min(min_y, y); max_y = max(max_y, y);
    // }
    // vector<string> result(max_x - min_x + 1, string(max_y - min_y + 1, '.'));
    // for (auto [x, y]: pts_a) result[x - min_x][y - min_y] = 'A';
    // for (auto [x, y]: pts_b) result[x - min_x][y - min_y] = 'B';
    // for (auto row: result) cout << row << '\n';
  }
}
