/* Model solution
 * O(q log n + n)
 * Krzysztof Kleiner
*/

#include <bits/stdc++.h>
#define REP(i, n) for (int (i) = 0; (i) < (n); (i)++)
using namespace std;
using K = double;

int cinDecrement() {
    int u;
    cin >> u;
    return u - 1;
}

class Solution {
    int n, m, c;
    vector<int> deg;
    vector<int> roomba;
    
    vector<K> catExpVal;
    // alreadyPushed[u][v] - how much expected value had already been pushed from u to v (during the previous u->v moves of Roomba)
    vector<map<int, K>> alreadyPushed;
    bool catStartedMoving = false;
    K result = 0;


    void processRoombaStep(int from, int to) {
        K surplus = catExpVal[from] / deg[from];
        auto& pushedFromTo = alreadyPushed[from][to];
        K pushing = surplus - pushedFromTo;
        pushedFromTo = surplus;

        catExpVal[to] += pushing;
        result += pushing;
    }
    
public:
    Solution() {
        cin >> n;
        deg.resize(n);
        c = cinDecrement();
        
        int u;
        REP(i, n - 1) {
            deg[cinDecrement()]++;
            deg[cinDecrement()]++;
        }
        
        cin >> m;
        roomba.resize(m);
        REP(i, m)
            roomba[i] = cinDecrement();
            
        catExpVal.resize(n);
        alreadyPushed.resize(n);
    }

    void solve() {
        catExpVal[c] = 1;
        REP(i, m - 1) {
            if(roomba[i+1] == c && !catStartedMoving) {
                catStartedMoving = true;
                result = 1;
            }
            processRoombaStep(roomba[i], roomba[i+1]);
        }
        cout << result << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout << setprecision(8) << fixed;
    int z; cin >> z;
    while (z--)
        Solution().solve();
    return 0;
}
