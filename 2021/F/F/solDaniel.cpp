// solution O(S)
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000000;
int N, S;

int a[MAX + 1];
vector<int> activate[MAX + 1];

struct node {
	int s, e, left, right;
	int black, white;
};

node nodes[MAX];
int STARTING;

int ANS[MAX + 1];

void input(){
	cin >> N;
	S = 0;
	for(int i = 0; i < N; i++){
		cin >> a[i];
		S = max(S, a[i]);
	}
}

void make_nodes(){
	vector<int> V;
	a[N] = S + 100;
	for(int i = 0; i <= N; i++){
		nodes[i].left = -1;
		nodes[i].right = -1;
	}
	for(int i = 0; i <= N; i++){
		while(!V.empty() && a[i] >= a[V[V.size() - 1]]){
			if(V.size() >= 2 && a[i] >= a[V[V.size() - 2]]){
				nodes[V[V.size() - 2]].right = V[V.size() - 1];
			} else {
				nodes[i].left = V[V.size() - 1];
			}
			nodes[V[V.size() - 1]].e = i;
			V.pop_back();
		}
		nodes[i].s = 0;
		if(!V.empty()){
			nodes[i].s = V[V.size() - 1] + 1;
		}
		V.push_back(i);
	}
	STARTING = nodes[N].left;
}

void make_activations(){
	for(int i = 0; i <= S; i++){
		activate[i].clear();
	}
	for(int i = 0; i < N; i++){
		activate[a[i]].push_back(i);
	}
}

void make_amts(){
	for(int s = 1; s <= S; s++){
		for(int j = 0; j < activate[s].size(); j++){
			int i = activate[s][j];
			nodes[i].white = 0;
			nodes[i].black = 0;
			int mode = 0;
			if(nodes[i].left != -1){
				int ind = nodes[i].left;
				nodes[i].white += nodes[ind].white;
				nodes[i].black += nodes[ind].black;
				if((nodes[ind].e - nodes[ind].s) % 2 == 1){
					mode = 1 - mode;
				}
			}
			if(mode == 0){
				nodes[i].white += a[i];
			} else {
				nodes[i].black += a[i];
			}
			mode = 1 - mode;
			if(nodes[i].right != -1){
				int ind = nodes[i].right;
				if(mode == 0){
					nodes[i].white += nodes[ind].white;
					nodes[i].black += nodes[ind].black;
				} else {
					nodes[i].white += nodes[ind].black;
					nodes[i].black += nodes[ind].white;
				}
			}
		}
	}
}

pair<int, int> DFS(int x, int val, int mode){
	if(a[x] <= val){
		int m = -1;
		int r = -1;
		if(mode == 0){
			r = nodes[x].white;
		} else {
			r = nodes[x].black;
		}
		if((nodes[x].e - nodes[x].s) % 2 == 0){
			m = mode;
		} else {
			m = 1 - mode;
		}
		// cout << "x = " << x << "   val = " << val << "   mode = " << mode << endl;
		// cout << r << " " << m << endl; 
		return make_pair(r, m);
	}
	pair<int, int> res;
	int amt = 0;
	if(nodes[x].left != -1){
		int ind = nodes[x].left;
		res = DFS(ind, val, mode);
		amt += res.first;
		mode = res.second;
	}
	int quotient = (a[x] - 1) / val;
	int q2 = quotient/2;
	int residue = (a[x] - 1) % val + 1;
	if(quotient % 2 == 0){
		if(mode == 0){
			amt += val * q2 + residue;
		} else {
			amt += val * q2;
		}
		mode = 1 - mode;
	} else {
		if(mode == 0){
			amt += q2 * val + val;
		} else {
			amt += q2 * val + residue;
		}
	}
	if(nodes[x].right != -1){
		int ind = nodes[x].right;
		res = DFS(ind, val, mode);
		amt += res.first;
		mode = res.second;
	}
	// cout << "x = " << x << "   val = " << val << "   mode = " << mode << endl;
	// cout << amt << "  " << mode << endl;
	return make_pair(amt, mode);
}

void process(){
	make_nodes();
	make_activations();
	make_amts();

	// for(int i = 0; i < N; i++){
	// 	cout << "=========  i = " << i << "  ===========\n";
	// 	cout << nodes[i].s << "   " << nodes[i].e << '\n';
	// 	cout << nodes[i].white << "  " << nodes[i].black << '\n';
	// 	cout << nodes[i].left << endl;
	// 	cout << nodes[i].right << endl;   
	// }

	// cout << "STARTING:   " << STARTING << endl;
	for(int val = S; val >= 1; val--){
		ANS[val] = DFS(STARTING, val, 0).first;
	}
}

void output(){
	for(int i = 1; i <= S; i++){
		cout << ANS[i] << '\n';
	}
}

int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(0);
	int T;
	cin >> T;
	for(int v = 0; v < T; v++){
		input();
		process();
		output();
	}
}
