/* Slow model solution
 * O(nk^2)
 * Krzysztof Kleiner
*/

#include <bits/stdc++.h>
#define REP(i, n) for (int (i) = 0; (i) < (n); (i)++)
using namespace std;
using LL = long long;
using Point = pair<int, int>;

const LL INF = 1e18 + 10;

LL dist(Point a, Point b) {
    return ((LL)a.first - b.first)*((LL)a.first - b.first)
         + ((LL)a.second - b.second)*((LL)a.second - b.second);
}

struct Solution {
    int n, k;
    vector<Point> students;
    vector<Point> leaders;
    
    Solution() {
        cin >> n >> k;
        students.resize(n);
        leaders.clear();

        REP(i, n)
            cin >> students[i].first >> students[i].second;
    }

    void chooseNewLeader() {
        int bestInd = -1;
        LL mx = -1;
        REP(i, n) {
            LL localMin = INF;

            for (auto leader : leaders)
                localMin = min(localMin, dist(students[i], leader));
                
            if(localMin > mx) {
                mx = localMin;
                bestInd = i;
            }
        }
        leaders.push_back(students[bestInd]);
    }

    int assignToLeader(Point p) {
        // Somewhat wasteful, as we could first check if p is not a leader themselves.
        int result = 0;
        LL mn = INF;
        REP(i, k) {
            Point leader = leaders[i];
            LL d = dist(p, leader);
            if(d < mn) {
                mn = d;
                result = i + 1;
            }
        }
        return result;
    }

    void solve() {
        REP(i, k)
            chooseNewLeader();
        REP(i, n)
            cout << assignToLeader(students[i]) << " \n"[i == n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while (z--)
        Solution().solve();
    return 0;
}
