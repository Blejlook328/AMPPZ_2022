// Model solution
// Time complexity: O(S), where S = total length of sticks

#include <bits/stdc++.h>


using namespace std;


struct block {
    int lenPar, value;
    array <int,2> sum;

    block(int value): lenPar(1), value(value), sum({value, 0}) {}

    bool isShort() const { return value == -1; }

    void makeShort() { value = -1; }

    void combine(const block &other) {
        for (int par = 0; par <= 1; par++) {
            sum[par] += other.sum[par ^ lenPar];
        }

        lenPar ^= other.lenPar;
    }
};


vector <int> solve(int n, vector <int> &sticks) {
    int maxLen = *max_element(sticks.begin(), sticks.end());
    vector <block> blocks;

    for (int s : sticks) {
        blocks.emplace_back(s);
    }

    vector <int> ans(maxLen);
    for (int s = 1; s <= maxLen; s++) {
        vector <block> newBlocks;
        for (auto &b : blocks) {
            if (b.value == s) {
                b.makeShort();
            }

            if (b.isShort() && !newBlocks.empty() && newBlocks.back().isShort()) {
                newBlocks.back().combine(b);
            } else {
                newBlocks.push_back(b);
            }
        }

        blocks = newBlocks;

        int ansHere = 0, currLenPar = 0;
        for (auto &b : blocks) {
            if (b.isShort()) {
                ansHere += b.sum[currLenPar];
                currLenPar ^= b.lenPar;
            } else {
                int div = b.value / s, rem = b.value % s;
                int divPar = div % 2;

                // Add every other full piece of length `s`.
                ansHere += (div + 1 - currLenPar) / 2 * s;

                // If the parity matches, add the last (incomplete) piece.
                if (divPar == currLenPar) {
                    ansHere += rem;
                }

                currLenPar ^= divPar;
                currLenPar ^= (rem > 0);
            }
        }

        ans[s - 1] = ansHere;
    }

    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector <int> sticks(n);
        for (int &stick : sticks) {
            cin >> stick;
        }

        auto ans = solve(n, sticks);
        for (int x : ans) {
            cout << x << '\n';
        }
    }

    return 0;
}
