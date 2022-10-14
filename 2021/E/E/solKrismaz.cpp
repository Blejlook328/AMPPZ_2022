// Model solution

#include <bits/stdc++.h>


using namespace std;


struct Testcase {
    int nPeople, nNodes;
    array <vector <vector<int>>, 2> g;
    vector <int> token, inUnhealthy;
    vector <bool> healthy;

    set <int> active;
    vector <set<int>> activePerVertex;

    Testcase(int n): nPeople(n), nNodes(n), token(n), inUnhealthy(n, 0), healthy(n, false), activePerVertex(n) {
        for (int dir = 0; dir < 2; dir++) {
            g[dir].resize(n);
        }

        for (int id = 0; id < nPeople; id++) {
            token[id] = id;
            active.insert(id);
            activePerVertex[id].insert(id);
        }
    }

    void mark(int v) {
        if (healthy[v]) return ;

        for (int id : activePerVertex[v]) {
            active.erase(id);
        }

        activePerVertex[v].clear();
        healthy[v] = true;

        for (int u : g[0][v]) {
            inUnhealthy[u]--;
            if (inUnhealthy[u] == 0) {
                mark(u);
            }
        }

        for (int u : g[1][v]) {
            mark(u);
        }
    }

    void recordPositiveTest(int id) {
        active.erase(id);
        activePerVertex[token[id]].erase(id);
    }

    void recordNegativeTest(int id) {
        mark(token[id]);
    }

    void runMeeting(vector <int> &ids) {
        int vNew = nNodes++;
        for (int dir = 0; dir < 2; dir++) {
            g[dir].emplace_back();
        }

        inUnhealthy.emplace_back();
        activePerVertex.emplace_back();

        for (int id : ids) {
            int v = token[id];
            token[id] = vNew;

            g[0][v].push_back(vNew);
            g[1][vNew].push_back(v);

            activePerVertex[v].erase(id);
            activePerVertex[vNew].insert(id);

            if (!healthy[v]) {
                inUnhealthy[vNew]++;
            }
        }

        if (!inUnhealthy[vNew]) {
            healthy.push_back(true);
        } else {
            healthy.push_back(false);

            for (int id : ids) {
                active.insert(id);
            }
        }
    }

    int getAnswer(int start) {
        if(active.empty())
            return -1;
        auto it = active.lower_bound(start);
        return *(it != active.end() ? it : active.begin());
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        Testcase test(n);

        int shift = 0;
        auto decode = [&](int x) {
            return (x - 1 + shift) % n;
        };

        while (q--) {
            char c; int value;
            cin >> c >> value;

            if (c == 'N') {
                test.recordNegativeTest(decode(value));
            } else if (c == 'P') {
                test.recordPositiveTest(decode(value));
            } else if (c == 'K') {
                vector <int> ids;
                while (value--) {
                    int v;
                    cin >> v;

                    ids.push_back(decode(v));
                }

                test.runMeeting(ids);
            } else {
                int ans = test.getAnswer(decode(value));
                if (ans == -1) {
                    cout << "TAK\n";
                    shift = 0;
                } else {
                    cout << "NIE " << ans + 1 << '\n';
                    shift = ans + 1;
                }
            }
        }
    }

    return 0;
}
