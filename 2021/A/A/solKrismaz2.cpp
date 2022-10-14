// Another approach based on closest pairs of points
// Time complexity: O(nk^2)

#include <bits/stdc++.h>

#define x first
#define y second


using namespace std;


typedef pair <int,int> pt;

const long long INF = 1LL << 60;


long long dist(const pt &a, const pt &b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

struct FAU {
    vector <int> p, r;

    FAU(int n): p(n, -1), r(n, 0) {}

    int find(int x) {
        return p[x] == -1 ? x : p[x] = find(p[x]);
    }

    void join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return ;

        if (r[x] > r[y]) p[y] = x;
        else p[x] = y;

        if (r[x] == r[y]) r[y]++;
    }
};

vector <int> solve(int n, int k, const vector <pt> &pts) {
    FAU fau(n);

    vector <int> roots(k);
    iota(roots.begin(), roots.end(), 0);

    for (int v = k; v < n; v++) {
        roots.push_back(v);

        int u1, u2;
        long long minDist = INF;

        for (int i = 0; i <= k; i++) for (int j = i + 1; j <= k; j++) {
            long long d = dist(pts[roots[i]], pts[roots[j]]);
            if (d < minDist) {
                minDist = d;
                u1 = i, u2 = j;
            }
        }

        fau.join(roots[u1], roots[u2]);
        roots.erase(roots.begin() + u2);
    }

    for (int &r : roots) {
        r = fau.find(r);
    }

    sort(roots.begin(), roots.end());

    vector <int> color(n);
    for (int v = 0; v < n; v++) {
        int r = fau.find(v);
        color[v] = lower_bound(roots.begin(), roots.end(), r) - roots.begin();
    }

    return color;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector <pt> pts(n);
        for (auto &p : pts) {
            cin >> p.x >> p.y;
        }

        auto color = solve(n, k, pts);
        for (int i = 0; i < n; i++) {
            cout << color[i] + 1 << ' ';
        }

        cout << '\n';
    }

    return 0;
}
