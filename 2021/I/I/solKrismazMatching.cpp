// Turbomatching on a graph which is implicit but queryable through an oracle
//
// Time complexity: technically O(n^2 log n), but faster in practice

#include <bits/stdc++.h>


using namespace std;


const int BITS = 20;
const int BITS_FULL = 32;


int getBitValue(int x, int b) {
    return (x & (1 << b)) != 0;
}


struct Trie {
    vector <array<int, 2>> child;
    vector <int> subCnt;
    vector <vector<int>> leafIdx;

    Trie() { addNode(); }

    int addNode() {
        child.push_back({-1, -1});
        subCnt.push_back(0);
        leafIdx.emplace_back();

        return (int) child.size() - 1;
    }

    void makePath(int x) {
        int node = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int bitValue = getBitValue(x, b);

            if (child[node][bitValue] == -1) {
                child[node][bitValue] = addNode();
            }

            node = child[node][bitValue];
        }
    }

    void modify(int x, int chg, int xId) {
        int node = 0;
        subCnt[node] += chg;

        for (int b = BITS - 1; b >= 0; b--) {
            node = child[node][getBitValue(x, b)];
            subCnt[node] += chg;
        }

        if (chg > 0) {
            leafIdx[node].push_back(xId);
        } else {
            leafIdx[node].pop_back();
        }
    }

    int anyInSub(int node) {
        while (leafIdx[node].empty()) {
            int l = child[node][0];
            if (l != -1 && subCnt[l] > 0) {
                node = l;
            } else {
                node = child[node][1];
            }
        }

        return leafIdx[node].back();
    }
};

struct Turbo {
    int n, k, na, nb, value = 0;
    vector <int> as, bs, mate, vis;

    Trie active;
    vector <bool> isActive;
    vector <vector<int>> neighNodes;

    Turbo(int k, vector <int> &as, vector <int> &bs): k(k), na(as.size()), nb(bs.size()), as(as), bs(bs) {
        for (int b : bs) {
            active.makePath(b);
        }

        neighNodes.resize(na);
        for (int i = 0; i < na; i++) {
            int node = 0;
            for (int b = BITS - 1; b >= 0 && node != -1; b--) {
                int nextBitValue = getBitValue(as[i] ^ k, b);
                if (!getBitValue(k, b)) {
                    int otherNode = active.child[node][!nextBitValue];
                    if (otherNode != -1) {
                        neighNodes[i].push_back(otherNode);
                    }
                }

                node = active.child[node][nextBitValue];
            }
        }

        isActive.resize(nb, false);
        mate.resize(na + nb, -1);
        vis.resize(na, 0);
    }

    int getNeighbor(int i) {
        for (int node : neighNodes[i]) {
            if (active.subCnt[node] > 0) {
                return na + active.anyInSub(node);
            }
        }

        return -1;
    }

    void deactivate(int u) {
        if (isActive[u]) {
            active.modify(bs[u], -1, u);
            isActive[u] = false;
        }
    }

    bool findPath(int v) {
        if (vis[v]) return false;

        vis[v] = true;
        if (mate[v] != -1) {
            deactivate(mate[v] - na);
        }

        int u;
        while (true) {
            u = getNeighbor(v);
            if (u == -1) {
                break;
            }

            if (mate[u] == -1 || findPath(mate[u])) {
                mate[v] = u;
                mate[u] = v;
                deactivate(u - na);

                return true;
            }
        }

        return false;
    }

    int runMatching() {
        bs.push_back(0);

        while (true) {
            bool found = false;
            fill(vis.begin(), vis.end(), 0);

            for (int u = 0; u < nb; u++) if (!isActive[u]) {
                active.modify(bs[u], 1, u);
                isActive[u] = true;
            }

            for (int v = 0; v < na; v++) if (mate[v] == -1 && findPath(v)) {
                found = true;
                value++;
            }

            if (!found) break;
        }

        return value;
    }
};

int solveBipartite(int k, vector <int> &as, vector <int> &bs) {
    return as.size() + bs.size() - Turbo(k, as, bs).runMatching();
}

int solve(int n, int k, vector <int> &values) {
    int prefMask = 0;
    for (int i = 1; i <= __builtin_clz(k); i++) {
        prefMask |= 1 << (BITS_FULL - i);
    }

    map <int,vector<int>> valuesByPref;
    for (int v : values) {
        int pref = v & prefMask;
        valuesByPref[pref].push_back(v ^ pref);
    }

    int leadingBitMask = 1 << (BITS_FULL - 1 - __builtin_clz(k));
    int ans = 0;

    for (auto &e : valuesByPref) {
        vector <int> group[2];
        for (int v : e.second) {
            bool leadingBit = v & leadingBitMask;
            group[leadingBit].push_back(v);
        }

        int ansHere;
        if (group[0].empty() || group[1].empty()) {
            ansHere = e.second.size();
        } else {
            ansHere = solveBipartite(k, group[0], group[1]);
        }

        ans = max(ans, ansHere);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector <int> values(n);
        for (int &v : values) {
            cin >> v;
        }

        cout << solve(n, k, values) << '\n';
    }

    return 0;
}
