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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  REP(i, t) {
    string s;
    cin >> s;
    for (char& c: s) c = (c - 'a' + 13) % 26 + 'a';
    cout << s << '\n';
  }
}