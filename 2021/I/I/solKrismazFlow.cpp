// Model solution using Dinic's algorithm
//
// Time complexity: O((n log n)^(3 / 2))

#include <bits/stdc++.h>


using namespace std;


const int BITS = 20;
const int BITS_FULL = 32;
const int INF = 1 << 30;


int getBitValue(int x, int b) {
    return (x & (1 << b)) != 0;
}


struct Trie {
    vector <array<int, 2>> child;
    Trie() { addNode(); }

    int addNode() {
        child.push_back({-1, -1});
        return (int) child.size() - 1;
    }

    int makePath(int x) {
        int node = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int bitValue = getBitValue(x, b);

            if (child[node][bitValue] == -1) {
                child[node][bitValue] = addNode();
            }

            node = child[node][bitValue];
        }

        return node;
    }
};

struct FlowNetwork {
    typedef int flow_t;
    const flow_t FINF = 1000 * 1000 * 1000;

    struct edge {
        int u, v; flow_t flow, cap;
        int rev;
    };

    int n, src, dest;
    vector <vector<edge>> G;
    vector <int> start, dist;

    FlowNetwork(int n): n(n), G(n), start(n), dist(n) {}

    bool bfs(int s, int t, int n) {
        fill(dist.begin(), dist.end(), -1);
        dist[s] = 0;

        queue <int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (edge &e : G[u]) if (e.flow < e.cap && dist[e.v] == -1) {
                dist[e.v] = dist[u] + 1;
                q.push(e.v);
            }
        }

        return dist[t] != -1;
    }

    flow_t dfs(int x, int t, flow_t mini) {
        flow_t ans = 0;

        if (x == t) return mini;
        if (mini <= 0) return 0;

        for (int &i = start[x]; i < (int) G[x].size(); ++i) {
            edge &e = G[x][i];

            if (dist[x] + 1 == dist[e.v] && e.flow < e.cap) {
                flow_t added = dfs(e.v, t, min(mini, e.cap - e.flow));

                e.flow += added;
                G[e.v][e.rev].flow -= added;
                mini -= added; ans += added;

                if (mini <= 0) break;
            }
        }

        return ans;
    }

    flow_t getFlow(int s, int t) {
        flow_t ans = 0;

        while (bfs(s, t, n)) {
            fill(start.begin(), start.end(), 0);
            ans += dfs(s, t, FINF);
        }

        return ans;
    }

    void addEdge(int u, int v, flow_t cap) {
        int uSize = G[u].size(), vSize = G[v].size();

        G[u].push_back({u, v, 0, cap, vSize});
        G[v].push_back({v, u, 0, 0, uSize});
    }
};

int solveBipartite(int k, vector <int> &as, vector <int> &bs) {
    int na = as.size(), nb = bs.size();

    Trie trie;
    vector <int> bLeaf(nb);

    for (int i = 0; i < nb; i++) {
        bLeaf[i] = trie.makePath(bs[i]);
    }

    int numNodes = as.size() + trie.child.size() + 2;
    int source = numNodes - 2;
    int sink = numNodes - 1;

    FlowNetwork network(numNodes);

    for (int i = 0; i < na; i++) {
        network.addEdge(source, i, 1);
    }

    for (int i = 0; i < nb; i++) {
        network.addEdge(na + bLeaf[i], sink, 1);
    }

    for (int i = 0; i < (int) trie.child.size(); i++) {
        for (int idx = 0; idx < 2; idx++) {
            int j = trie.child[i][idx];
            if (j != -1) {
                network.addEdge(na + i, na + j, INF);
            }
        }
    }

    for (int i = 0; i < na; i++) {
        int node = 0;
        for (int b = BITS - 1; b >= 0 && node != -1; b--) {
            int nextBitValue = getBitValue(as[i] ^ k, b);
            if (!getBitValue(k, b)) {
                int otherNode = trie.child[node][!nextBitValue];
                if (otherNode != -1) {
                    network.addEdge(i, na + otherNode, 1);
                }
            }

            node = trie.child[node][nextBitValue];
        }
    }

    return na + nb - network.getFlow(source, sink);
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
