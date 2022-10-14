#include <bits/stdc++.h>
using namespace std;

const int MAX = 2000;
int N, M;
int arr[MAX][MAX];
bool dp[MAX][MAX];

bool swapx[MAX];
bool swapy[MAX];

void input(){
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		string s;
		cin >> s;
		for(int j = 0; j < M; j++){
			if(s[j] == '.'){
				arr[i][j] = 0;
			} else if(s[j] == '#'){
				arr[i][j] = 3;
			} else if(s[j] == '@'){
				arr[i][j] = 2;
			} else {
				arr[i][j] = 1;
			}
		}
	}
}

void process(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			dp[i][j] = false;
			if(i == 0 && j == 0){
				dp[i][j] = true;
				continue;
			}
			if(arr[i][j] == 3) continue;
			if(i > 0 && dp[i - 1][j]){
				dp[i][j] = true;
			}
			if(j > 0 && dp[i][j - 1]){
				dp[i][j] = true;
			}
		}
	}
}

void swap_row(int y){
	for(int j = 0; j < M; j++){
		arr[y][j] = 3 - arr[y][j];
	}
}

void swap_col(int x){
	for(int i = 0; i < N; i++){
		arr[i][x] = 3 - arr[i][x];
	}
}

void output(){
	if(dp[N - 1][M - 1]){
		cout << "TAK\n";
		int x = M - 1;
		int y = N - 1;
		vector<char> ANS;
		for(int i = 0; i < N; i++){
			swapx[i] = false;
		}
		for(int j = 0; j < M; j++){
			swapy[j] = false;
		}
		if(arr[y][x] == 2){
			swapx[y] = true;
			swap_row(y);
		}
		while(x > 0 || y > 0){
			if(x > 0 && dp[y][x - 1]){
				ANS.push_back('P');
				x--;
				if(arr[y][x] == 2){
					swapy[x] = true;
					swap_col(x);
				}
			} else {
				ANS.push_back('D');
				y--;
				if(arr[y][x] == 2){
					swapx[y] = true;
					swap_row(y);
				}
			}
		}
		for(int i = 0; i < N; i++){
			if(swapx[i]){
				cout << 'T';
			} else {
				cout << 'N';
			}
		}
		cout << '\n';
		for(int i = 0; i < M; i++){
			if(swapy[i]){
				cout << 'T';
			} else {
				cout << 'N';
			}
		}
		cout << '\n';
		reverse(ANS.begin(), ANS.end());
		for(int i = 0; i < N + M - 2; i++){
			cout << ANS[i];
		}
		cout << '\n';
	} else {
		cout << "NIE\n";
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
