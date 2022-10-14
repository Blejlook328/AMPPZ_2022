#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000000;

int N;
long long C;
long long amt[MAX];
long long desired_amt[MAX];
int prev_ind[MAX];
int next_ind[MAX];
bool visited[MAX];

vector<int> up;
vector<int> down;

long long ANS_VAL = 0;
queue<pair<int, int> > ANS;

void input(){
	cin >> N >> C;
	for(int i = 0; i < N; i++){
		cin >> amt[i];
		cin >> desired_amt[i];
		visited[i] = false;
	}
	up.clear();
	down.clear();
	ANS_VAL = 0;
}

void make_ind(){
	map<int, int> M;
	for(int i = 0; i < N; i++){
		M[amt[i]] = i;
	}
	for(int i = 0; i < N; i++){
		next_ind[i] = M[desired_amt[i]];
	}
	for(int i = 0; i < N; i++){
		prev_ind[next_ind[i]] = i;
	}
}

void remove_stairs(int front, int back, vector<int> &vec1, vector<int> &vec2){
	ANS.push(make_pair(front, back));
	ANS_VAL += abs(amt[back] - amt[next_ind[back]]) + C;
	amt[front] = amt[back];
	vec1.pop_back();
	int x = prev_ind[front];

	next_ind[prev_ind[back]] = front;
	prev_ind[front] = prev_ind[back];

	while(x != back){
		ANS.push(make_pair(x, back));
		ANS_VAL += C;
		vec2.pop_back();
		x = prev_ind[x];
	}
}

void remove_cycle(int ind){
	int next;
	while(true){
		next = next_ind[ind];
		bool STOP = true;
		if(!up.empty() && amt[up[up.size() - 1]] <= amt[next]){
			remove_stairs(ind, up[up.size() - 1], up, down);
			STOP = false;
		}
		if(!down.empty() && amt[down[down.size() - 1]] >= amt[next]){
			remove_stairs(ind, down[down.size() - 1], down, up);
			STOP = false;
		}
		if(STOP) break;
	}
	if(ind != next){
		if(amt[next] < amt[ind]){
			up.push_back(ind);
		} else {
			down.push_back(ind);
		}
		remove_cycle(next);
	}
}

void process(){
	for(int i = 0; i < N; i++){
		if(!visited[i]){
			visited[i] = true;
			int x = next_ind[i];
			while(i != x){
				visited[x] = true;
				x = next_ind[x];
			}
			remove_cycle(i);
		}
	}
}

void output(){
	cout << ANS_VAL << " " << ANS.size() << '\n';
	while(!ANS.empty()){
		cout << (ANS.front()).first + 1 << " " << (ANS.front()).second + 1 << '\n';
		ANS.pop();
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
		make_ind();
		process();
		output();
	}
}
