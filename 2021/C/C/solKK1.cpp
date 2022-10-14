/* Model solution
 * O(n log n)
 * Krzysztof Kleiner
*/

#include <bits/stdc++.h>
#define REP(i, n) for (int (i) = 0; (i) < (n); (i)++)
using namespace std;
using pii = pair<int, int>;
using LL = long long;
const LL base = 1e9 + 1;

LL getHash(pii val, int index) {
    return (index % 2) ?
        (val.first * base + val.second) :
        (val.second * base + val.first);
}

class Solution {
    int n;
    vector<pii> cakeA, cakeB;
    vector<LL> finalA;
    map<LL, queue<int>> renumbering;

    LL countInversions(int beg, int end) {
        if(beg >= end - 1)
            return 0;
        int mid = (beg + end) / 2;
        LL res = countInversions(beg, mid);
        res += countInversions(mid, end);

        vector<LL> tmp;
        for (int i = beg, j = mid; i < mid || j < end; ) {
            if(j == end || (i != mid && finalA[i] <= finalA[j]))
                tmp.push_back(finalA[i++]);
            else {
                tmp.push_back(finalA[j++]);
                res += (mid - i);
            }
        }
        for (LL v : tmp)
            finalA[beg++] = v;
        return res;
    }

public:
    Solution() {
        cin >> n;
        cakeA.resize(n);
        cakeB.resize(n);
        REP(i, n)
            cin >> cakeA[i].first;
        REP(i, n)
            cin >> cakeA[i].second;
        REP(i, n)
            cin >> cakeB[i].first;
        REP(i, n)
            cin >> cakeB[i].second;
    }

    void solve() {
        REP(i, n) {
            auto& q = renumbering[getHash(cakeB[i], i)];
            q.push(i);
        }

        REP(i, n) {
            auto& q = renumbering[getHash(cakeA[i], i)];
            if(q.empty()) {
                cout << -1 << endl;
                return;
            }
            finalA.push_back(q.front());
            q.pop();
        }

        cout << countInversions(0, n) << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while (z--)
        Solution().solve();
    return 0;
}
