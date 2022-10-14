#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000000;
int N, Q;

vector<vector<pair<int, int> > > meetings; // pairs of (index of person attending meeting, index of the moment this person was in the meeting).
vector<int> people[MAX]; // indexes of meetings

vector<bool> visited;
vector<int> amount_left;

int potential[MAX];

int shift = 0;
set<int> S;

int decode(int x){
	return (x - 1 + shift)%N;
}

void caseK(){
	int amt;
	cin >> amt;
	vector<pair<int, int> > node;
	int x;
	int amount_push = 0;
	for(int i = 0; i < amt; i++){
		cin >> x;
		x = decode(x);
		if(potential[x]){
			amount_push++;
		}
		node.push_back(make_pair(x, people[x].size()));
	}
	if(amount_push > 0){
		for(int i = 0; i < amt; i++){
			int x = node[i].first;
			S.insert(x);
			potential[x] = true;
			people[x].push_back(meetings.size());
		}
		meetings.push_back(node);
		visited.push_back(false);
		amount_left.push_back(amount_push);
	}
}

void caseP(){
	int x;
	cin >> x;
	x = decode(x);
	S.erase(x);
}

void DFS(int y){
	if(visited[y]) return;
	visited[y] = true;
	for(int i = 0; i < meetings[y].size(); i++){
		pair<int, int> P = meetings[y][i];
		if(P.second == people[P.first].size() - 1){
			if(potential[P.first]){
				S.erase(P.first);
				potential[P.first] = false;
			}
		} else {
			int one_above = people[P.first][P.second + 1];
			amount_left[one_above]--;
			if(amount_left[one_above] == 0){
				DFS(one_above);
			}
		}
		if(P.second != 0){
			int one_below = people[P.first][P.second - 1];
			DFS(one_below);
		}
	}
}

void caseN(){
	int x;
	cin >> x;
	x = decode(x);
	if(potential[x]){
		S.erase(x);
		potential[x] = false;
	}
	if(people[x].size() > 0) DFS(people[x][people[x].size() - 1]);
}

void query(){
	int x;
	cin >> x;
	x = decode(x);
	if(S.size() == 0){
		cout << "TAK\n";
		shift = 0;
	} else {
        auto it = S.lower_bound(x);
        shift = *(it == S.end() ? S.begin() : it) + 1;
		cout << "NIE " << shift << '\n';
	}
}

void process(){
	shift = 0;
	amount_left.clear();
	S.clear();
	cin >> N >> Q;
	for(int i = 0; i < N; i++){
		S.insert(i);
		potential[i] = true;
		people[i].clear();
	}
	meetings.clear();
	visited.clear();
	char c;
	for(int q = 0; q < Q; q++){
		cin >> c;
		if(c == 'K'){
			caseK();
		} else if(c == 'P'){
			caseP();
		} else if(c == 'N'){
			caseN();
		} else {
			query();
		}
	}
}

int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(0);
	int T;
	cin >> T;
	for(int v = 0; v < T; v++){
		process();
	}
}
