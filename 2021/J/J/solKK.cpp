/* Model solution
 * O(n * m)
 * Krzysztof Kleiner
*/

#include <bits/stdc++.h>
using namespace std;

enum class Field {
    FREE,
    BLOCKED,
    ACTIVE_TRAP,
    INACTIVE_TRAP
};

using Board = vector<vector<Field>>;

enum class Move {
    DOWN,
    RIGHT
};

using Path = vector<Move>;

Field decode(char c) {
    switch (c) {
        case '.': return Field::FREE;
        case '#': return Field::BLOCKED;
        case '@': return Field::ACTIVE_TRAP;
        case 'O': return Field::INACTIVE_TRAP;
        default: assert(false);
    }
}

string encode(const vector<bool>& boolVector) {
    string res {};
    for (auto b : boolVector)
        res.push_back(b ? 'T' : 'N');
    return res;
}

string encode(const Path& path) {
    string res {};
    for (auto m : path)
        res.push_back(m == Move::DOWN ? 'D' : 'P');
    return res;
}


struct TestCase {
    int n, m;
    Board board {};

    TestCase() {
        cin >> n >> m;
        board.resize(n);
        for (int i = 0; i < n; i++) {
            string in; cin >> in;
            for (char c : in)
                board[i].push_back(decode(c));
        }
    }
};

class TrapReverser {
    vector<bool> rowReverse, colReverse;
    const TestCase& test;

    bool isActiveTrap(int row, int col) const {
        auto field = test.board[row][col];
        bool flipped = (rowReverse[row] != colReverse[col]);

        return (flipped && field == Field::INACTIVE_TRAP)
            || (!flipped && field == Field::ACTIVE_TRAP);
    }

    void reverseRowIfNeeded(int row, int col) {
        if(isActiveTrap(row, col))
            rowReverse[row] = true;
    }

    void reverseColIfNeeded(int row, int col) {
        if(isActiveTrap(row, col))
            colReverse[col] = true;
    }

    void print() const {
        cout << encode(rowReverse) << endl
             << encode(colReverse) << endl;
    }

public:
    TrapReverser(const TestCase& test) : test(test) {
        rowReverse.resize(test.n);
        colReverse.resize(test.m);
    }

    void findAndPrintReversing(const Path& path) {
        int row = 0, col = 0;

        reverseRowIfNeeded(row, col); // The first field could get either its row or its column reversed.
        for (auto move : path) {
            if(move == Move::RIGHT)
                reverseColIfNeeded(row, ++col);
            else
                reverseRowIfNeeded(++row, col);
        }

        print();
    }
};

class SolutionFinder {
    TestCase test;
    Path path {};
    vector<vector<bool>> visited {};

    bool tryPathTo(int row, int col) {
        if(row == 0 && col == 0)
            return true;

        if(row < 0 || col < 0 || visited[row][col] || test.board[row][col] == Field::BLOCKED)
            return false;

        visited[row][col] = true;

        if(tryPathTo(row - 1, col)) {
            path.push_back(Move::DOWN);
            return true;
        }

        if(tryPathTo(row, col - 1)) {
            path.push_back(Move::RIGHT);
            return true;
        }

        return false;
    }

    bool findPath() {
        return tryPathTo(test.n - 1, test.m - 1);
    }

public:
    SolutionFinder(TestCase&& test) : test(move(test)) {
        visited.resize(test.n, vector<bool>(test.m));
    }

    void solve() {
        if(!findPath())
        {
            cout << "NIE" << endl;
            return;
        }
        cout << "TAK" << endl;

        TrapReverser{test}.findAndPrintReversing(path);
        cout << encode(path) << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while (z--)
        SolutionFinder(TestCase()).solve();
    return 0;
}
