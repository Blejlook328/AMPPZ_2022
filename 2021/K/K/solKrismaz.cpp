// Model solution
// Time complexity: O(n + m)

#include <bits/stdc++.h>


using namespace std;


struct Testcase {
    int n, m;
    vector <vector<int>> g;
    vector <int> seq, par;
    vector <double> value, lazy;

    Testcase(int n, int m, int c, vector <vector<int>> &g, vector <int> &seq):
        n(n), m(m), g(g), seq(seq), par(n, -1), value(n, 0.0), lazy(n, 0.0) { value[c] = 1.0; }

    void dfs(int v) {
        for (int u : g[v]) if (u != par[v]) {
            par[u] = v;
            dfs(u);
        }
    }

    double getValue(int v) {
        return value[v] + (par[v] != -1 ? lazy[par[v]] : 0.0);
    }

    double solve() {
        dfs(0);

        double ans = 0.0;
        for (int v : seq) {
            double val = getValue(v);

            ans += val;
            value[v] -= val;

            val /= g[v].size();

            lazy[v] += val;
            if (par[v] != -1) {
                value[par[v]] += val;
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(12) << fixed;

    int t;
    cin >> t;

    while (t--) {
        int n, c;
        cin >> n >> c; c--;

        vector <vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v; u--; v--;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        int m;
        cin >> m;

        vector <int> seq(m);
        for (int &si : seq) {
            cin >> si; si--;
        }

        cout << Testcase(n, m, c, g, seq).solve() << '\n';
    }

    return 0;
}
