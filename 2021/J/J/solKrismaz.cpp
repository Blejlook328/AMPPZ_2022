// Model solution

#include <bits/stdc++.h>

#define x first
#define y second


using namespace std;


enum FieldType {
    EMPTY, BLOCKED, INACTIVE, ACTIVE
};

string convertToYesNo(vector <int> &vec) {
    string s;
    for (int x : vec) {
        s.push_back("NT"[x]);
    }

    return s;
}

vector <string> solve(int n, int m, vector <vector<FieldType>> &board) {
    vector <vector<bool>> reachable(n, vector <bool> (m, false));
    reachable[0][0] = true;

    for (int x = 0; x < n; x++) for (int y = 0; y < m; y++) if ((x || y) && board[x][y] != BLOCKED) {
        reachable[x][y] = (x > 0 && reachable[x-1][y]) || (y > 0 && reachable[x][y-1]);
    }

    if (!reachable[n-1][m-1]) {
        return {};
    }

    vector <pair<int,int>> path;
    string pathSteps;

    int x = n - 1, y = m - 1;

    while (x || y) {
        path.push_back({x, y});

        if (x > 0 && reachable[x-1][y]) {
            pathSteps.push_back('D');
            x--;
        } else {
            pathSteps.push_back('P');
            y--;
        }
    }

    path.push_back({0, 0});
    reverse(path.begin(), path.end());
    reverse(pathSteps.begin(), pathSteps.end());

    vector <int> flipRow(n, 0), flipCol(m, 0);
    for (int i = 0; i < (int) path.size(); i++) {
        auto p = path[i];
        if ((board[p.x][p.y] == ACTIVE) ^ flipRow[p.x] ^ flipCol[p.y]) {
            if (i == 0 || p.x == path[i - 1].x) {
                flipCol[p.y] ^= 1;
            } else {
                flipRow[p.x] ^= 1;
            }
        }
    }

    return {convertToYesNo(flipRow), convertToYesNo(flipCol), pathSteps};
}

map <char,FieldType> charToFieldType = {
    {'.', EMPTY},
    {'#', BLOCKED},
    {'O', INACTIVE},
    {'@', ACTIVE}
};

int main() {
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector <vector<FieldType>> board(n, vector <FieldType> (m));
        for (int x = 0; x < n; x++) {
            string s;
            cin >> s;

            for (int y = 0; y < m; y++) {
                board[x][y] = charToFieldType[s[y]];
            }
        }

        auto ans = solve(n, m, board);
        if (ans.empty()) {
            cout << "NIE\n";
        } else {
            cout << "TAK\n";

            for (auto &s : ans) {
                cout << s << '\n';
            }
        }
    }

    return 0;
}
