// Model solution using a simple recurrence
//
// Time complexity: O(n log RANGE)

#include <bits/stdc++.h>

using namespace std;


const int BITS = 20;
const int BITS_FULL = 32;


int getBitValue(int x, int bit) {
    return (x & (1 << bit)) != 0;
}

array <vector <int>, 2> splitByBit(int bit, const vector <int> &values) {
    array <vector <int>, 2> groups;
    for (int v : values) {
        groups[getBitValue(v, bit)].push_back(v);
    }

    return groups;
}

int solveBipartite(int bit, int k, const array <vector <int>, 2> &values) {
    if (values[0].empty() && values[1].empty()) {
        return 0;
    }

    if (bit == -1) {
        return values[0].size() + values[1].size();
    }

    int ans = max(values[0].size(), values[1].size());

    array <array<vector <int>, 2>, 2> valuesSplit;
    for (int b = 0; b < 2; b++) {
        valuesSplit[b] = splitByBit(bit, values[b]);
    }

    if (getBitValue(k, bit) == 0) {
        ans = max(ans, solveBipartite(bit - 1, k, {valuesSplit[0][0], valuesSplit[1][0]}));
        ans = max(ans, solveBipartite(bit - 1, k, {valuesSplit[0][1], valuesSplit[1][1]}));
    } else {
        int ansHere = 0;
        ansHere += solveBipartite(bit - 1, k, {valuesSplit[0][0], valuesSplit[1][1]});
        ansHere += solveBipartite(bit - 1, k, {valuesSplit[0][1], valuesSplit[1][0]});

        ans = max(ans, ansHere);
    }

    return ans;
}

int solve(int k, const vector <int> &values) {
    int prefMask = 0;
    for (int i = 1; i <= __builtin_clz(k); i++) {
        prefMask |= 1 << (BITS_FULL - i);
    }

    map <int,vector<int>> valuesByPref;
    for (int v : values) {
        int pref = v & prefMask;
        valuesByPref[pref].push_back(v ^ pref);
    }

    int leadingBit = BITS_FULL - 1 - __builtin_clz(k);
    int ans = 0;

    for (auto &e : valuesByPref) {
        ans = max(ans, solveBipartite(leadingBit - 1, k, splitByBit(leadingBit, e.second)));
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

        cout << solve(k, values) << '\n';
    }

    return 0;
}
