#include <bits/stdc++.h>
using namespace std;

const int MAX = 500000;
const int P = 1000000007;
int N;

int ta[2][MAX];
int tb[2][MAX];
long long ha[MAX];
long long hb[MAX];

int perm[MAX];
int helper[MAX];

long long ANS;

long long make_hash(long long x, long long y){
	return x + P * y;
}

void input(){
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> ta[0][i];
	}
	for(int i = 0; i < N; i++){
		cin >> ta[1][i];
	}
	for(int i = 0; i < N; i++){
		cin >> tb[0][i];
	}
	for(int i = 0; i < N; i++){
		cin >> tb[1][i];
	}

	for(int i = 1; i < N; i += 2){
		swap(ta[0][i], ta[1][i]);
		swap(tb[0][i], tb[1][i]);
	}
	
	for(int i = 0; i < N; i++){
		ha[i] = make_hash(ta[0][i], ta[1][i]);
		hb[i] = make_hash(tb[0][i], tb[1][i]);
	}
}

bool make_perm(){
	unordered_map<long long, vector<int> > MAP;
	unordered_map<long long, int> INDEXES;

	for(int i = 0; i < N; i++){
		if(MAP.find(hb[i]) == MAP.end()){
			MAP[hb[i]] = vector<int>(1, i);
			INDEXES[hb[i]] = 0;
		} else {
			(MAP[hb[i]]).push_back(i);
		}
	}

	bool WORKS = true;

	for(int i = 0; i < N; i++){
		if(MAP.find(ha[i]) == MAP.end()){
			WORKS = false;
			break;
		} else if((MAP[ha[i]]).size() <= INDEXES[ha[i]]){
			WORKS = false;
			break;
		} else {
			perm[i] = MAP[ha[i]][INDEXES[ha[i]]];
			INDEXES[ha[i]]++;
		}
	}

	return WORKS;
}

void sortt(int a, int b){
	if(a + 1 == b) return;
	if(a + 2 == b){
		if(perm[a] > perm[a + 1]){
			swap(perm[a], perm[a + 1]);
			ANS++;
		}
		return;
	}

	int h = (a + b + 1)/2;
	int ind0 = a;
	int ind1 = h;
	int ind2 = a;

	sortt(a, h);
	sortt(h, b);

	while(ind2 < b){
		if(ind0 == h){
			helper[ind2] = perm[ind1];
			ind1++;
		} else if(ind1 == b){
			helper[ind2] = perm[ind0];
			ANS += (long long) (ind1 - h);
			ind0++;
		} else {
			if(perm[ind0] < perm[ind1]){
				helper[ind2] = perm[ind0];
				ANS += (long long) (ind1 - h);
				ind0++;
			} else {
				helper[ind2] = perm[ind1];
				ind1++;
			}
		}
		ind2++;
	}

	for(int i = a; i < b; i++){
		perm[i] = helper[i];
	}
}

void process(){
	bool WORKS = make_perm();
	if(WORKS){
		ANS = 0;
		sortt(0, N);
		cout << ANS << '\n';
	} else {
		cout << -1 << '\n';
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
	}
}
