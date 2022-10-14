#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define REP(i, n) for (int (i) = 0; (i) < (n); (i)++)

pii operator+(pii a, pii b) {
	return {a.first + b.first, a.second + b.second};
}

pii operator-(pii a, pii b) {
	return {a.first - b.first, a.second - b.second};
}

const int sizeN = 10 + 1;
const int sizeQ = 100 + 1;

enum Direction {
	N, S, W, E
};

class Solution {
	int n, m, q;
	bool blocked[sizeN][sizeN]{};
	vector<pii> partB{};
	pii offset{};
	Direction steps[sizeQ]{};

public:
	Solution() {
		cin >> n >> m >> q;
		REP(i, n) {
			string s;
			cin >> s;
			REP(j, m)
				if(s[j] == 'A')
					blocked[i][j] = true;
				else if(s[j] == 'B')
					partB.emplace_back(i, j);
		}
		
		string s; cin >> s;
		REP(i, q) {
			steps[i] = decode(s[i]);
		}
	}

	static Direction decode(char c) {
		switch(c) {
			case 'N': return N;
			case 'S': return S;
			case 'W': return W;
			case 'E': return E;
			default: assert(false);
		}
	}

	static pii getDisplacement(Direction d) {
		switch(d) {
			case N: return {-1, 0};
			case S: return { 1, 0};
			case W: return { 0,-1};
			case E: return { 0, 1};
			default: assert(false);
		}
	}

	bool isBlocked(pii position) {
		int y = position.first, x = position.second;
		if(y < 0 || y >= n || x < 0 || x >= m)
			return false;
		return blocked[y][x];
	}

	bool partsInCollision() {
		for (auto b : partB) {
			auto currentPos = b + offset;
			if(isBlocked(b + offset))
				return true;
		}
		return false;
	}
	
	// Returns true if this step separates the mechanizm
	bool performStep(pii displacement) {
		for (int i = 1; i <= max(n, m); i++) {
			offset = offset + displacement;
			if(partsInCollision()) {
				offset = offset - displacement;
				return false;
			}
		}
		return true;
	}

	void solve() {
		REP(i, q) {
			auto dir = steps[i];
			if(performStep(getDisplacement(dir))) {
				cout << "TAK\n";
				return;
			}
		}
		cout << "NIE\n";
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while (z--) {
        Solution().solve();
    }
    return 0;
}

