// Model solution
// Time complexity: O((n + q) log n)

#include <bits/stdc++.h>


using namespace std;


const long long INF = 1LL << 60;


struct event {
    long long minSurvive, minLinear, constVal;
};

const event EMPTY_EVENT = {-1, -1, -1};

// An "empty" event, needed to initialize the out-of-range nodes in the segment tree.
const event UNIT_EVENT = {1, 1, 1};


event readEvent() {
    char type;
    long long value;

    cin >> type >> value;

    if (type == 'B') {
        return {value + 1, value + 1, 1};
    } else if (type == 'C') {
        return {1, value, value};
    } else if (type == 'K') {
        return {value, INF, value};
    } else {
        assert(false);
    }
}


struct query {
    int pos; event ev;

    bool isUpdate() const {
        return ev.minSurvive != -1;
    }
};


struct Tree {
    typedef event val_t;

    val_t combine(const val_t &a, const val_t &b) {
        event result;

        if (a.constVal >= b.minSurvive) {
            result.minSurvive = a.minSurvive;

            if (a.constVal >= b.minLinear) {
                result.minLinear = a.minLinear;
                result.constVal = b.constVal + (a.constVal - b.minLinear);
            } else {
                result.minLinear = a.minLinear + (b.minLinear - a.constVal);
                result.constVal = b.constVal;
            }
        } else {
            result.minSurvive = a.minLinear + (b.minSurvive - a.constVal);
            result.minLinear = a.minLinear + (b.minLinear - a.constVal);
            result.constVal = b.constVal;
        }

        result.minSurvive = min(result.minSurvive, INF);
        result.minLinear = min(result.minLinear, INF);

        if (result.minSurvive < INF) {
            assert(result.constVal < INF);
        } else {
            result.constVal = INF;
        }

        return result;
    }

    int n, p = 1;
    vector <val_t> tree;

    Tree(const vector <val_t> &init) {
        n = init.size();
        while (p < n) p *= 2;

        int m = 2 * p - 1;
        tree.resize(m, UNIT_EVENT);

        for (int i = 0; i < n; i++) {
            tree[i + p - 1] = init[i];
        }

        for (int i = p - 2; i >= 0; i--) {
            tree[i] = combine(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }

    int par(int x) { return (x - 1) / 2; }

    void update(int l, val_t v) {
        l += p - 1;
        tree[l] = v;

        while (l) {
            l = par(l);
            tree[l] = combine(tree[2 * l + 1], tree[2 * l + 2]);
        }
    }

    int query(int l, long long h) {
        l += p - 1;

        if (h < tree[l].minSurvive) {
            return -1;
        }

        val_t curr = tree[l];
        while (l) {
            if (l % 2 == 1) {
                auto currWithLeft = combine(curr, tree[l + 1]);

                if (h < currWithLeft.minSurvive) {
                    l++;
                    break;
                } else {
                    curr = currWithLeft;
                }
            }

            l = par(l);
        }

        if (l == 0) {
            return n - 1;
        }

        while (l < p - 1) {
            auto currWithLeft = combine(curr, tree[2 * l + 1]);

            if (h < currWithLeft.minSurvive) {
                l = 2 * l + 1;
            } else {
                curr = currWithLeft;
                l = 2 * l + 2;
            }
        }

        return l - p;
    }
};


vector <int> solve(int n, int q, long long h, const vector <event> &init, const vector <query> &queries) {
    Tree tree(init);
    vector <int> ans;

    for (int i = 0; i < q; i++) {
        if (queries[i].isUpdate()) {
            tree.update(queries[i].pos, queries[i].ev);
        } else {
            ans.push_back(tree.query(queries[i].pos, h));
        }
    }

    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n, q; long long h;
        cin >> n >> q >> h;

        vector <event> init(n);
        for (auto &e : init) {
            e = readEvent();
        }

        vector <query> queries(q);
        for (auto &e : queries) {
            char type;
            cin >> type >> e.pos; e.pos--;

            if (type == 'Z') {
                e.ev = readEvent();
            } else {
                e.ev = EMPTY_EVENT;
            }
        }

        auto ans = solve(n, q, h, init, queries);

        for (int i : ans) {
            cout << (i == -1 ? -1 : i + 1) << '\n';
        }
    }

    return 0;
}
