// Model solution
// Time complexity: O(nk)

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


vector <int> solve(int n, int k, const vector <pt> &pts) {
    vector <int> init(k);
    vector <long long> minDist(n, INF);

    for (int i = 0; i < k; i++) {
        init[i] = max_element(minDist.begin(), minDist.end()) - minDist.begin();

        for (int v = 0; v < n; v++) {
            minDist[v] = min(minDist[v], dist(pts[v], pts[init[i]]));
        }
    }

    vector <int> color(n);
    for (int v = 0; v < n; v++) {
        long long distBest = INF;

        for (int i = 0; i < k; i++) {
            long long distHere = dist(pts[v], pts[init[i]]);

            if (distHere < distBest) {
                color[v] = i;
                distBest = distHere;
            }
        }
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
