// a completely brutal approach. Yet, it's a solution.
#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;
int N, M, Q;

int tab[3*MAX][3*MAX];
int rotation = 0;
vector<int> moves;

void rotate_single(){
	// rotates anticlockwise.
	int C = 3*MAX - 1;
	for(int i = 0; i < (3*MAX)/2; i++){
		for(int j = 0; j < (3*MAX)/2; j++){
			int temp = tab[i][j];
			tab[i][j] = tab[j][C - i];
			tab[j][C - i] = tab[C - i][C - j];
			tab[C - i][C - j] = tab[C - j][i];
			tab[C - j][i] = temp;
		}
	}
	rotation++;
	if(rotation == 4){
		rotation = 0;
	}
}

void rotate(int x){
	while(rotation != x){
		rotate_single();
	}
}

void input(){
	for(int i = 0; i < 3*MAX; i++){
		for(int j = 0; j < 3*MAX; j++){
			tab[i][j] = 0;
		}
	}
	moves.clear();
	cin >> N >> M >> Q;
	string s;
	for(int i = 0; i < N; i++){
		cin >> s;
		for(int j = 0; j < M; j++){
			if(s[j] == '.'){
				tab[MAX + i][MAX + j] = 0;
			} else if(s[j] == 'A'){
				tab[MAX + i][MAX + j] = 1;
			} else {
				tab[MAX + i][MAX + j] = 2;
			}
		}
	}
	cin >> s;
	for(int i = 0; i < Q; i++){
		char c = s[i];
		if(c == 'N'){
			moves.push_back(0);
		} else if(c == 'S'){
			moves.push_back(2);
		} else if(c == 'E'){
			moves.push_back(1);
		} else {
			moves.push_back(3);
		}
	}
}

// void output(){
// 	int minx = 1000;
// 	int maxx = -1;
// 	int miny = 1000;
// 	int maxy = -1;
// 	for(int i = 0; i < 3*MAX; i++){
// 		for(int j = 0; j < 3*MAX; j++){
// 			if(tab[i][j] != 0){
// 				miny = min(miny, i);
// 				maxy = max(maxy, i);
// 				minx = min(minx, j);
// 				maxx = max(maxx, j);
// 			}
// 		}
// 	}
// 	for(int i = miny; i <= maxy; i++){
// 		for(int j = minx; j <= maxx; j++){
// 			if(tab[i][j] == 0){
// 				cout << '.';
// 			} else if(tab[i][j] == 1){
// 				cout << 'A';
// 			} else {
// 				cout << 'B';
// 			}
// 		}
// 		cout << '\n';
// 	}
// }

bool far_move(){
	while(true){
		for(int j = 0; j < 3*MAX; j++){
			if(tab[0][j] != 0) return true;
		}
		for(int i = 0; i < 3*MAX - 1; i++){
			for(int j = 0; j < 3*MAX; j++){
				if(tab[i + 1][j] == 2 && tab[i][j] == 1){
					return false;
				}
			}
		}
		for(int i = 0; i < 3*MAX - 1; i++){
			for(int j = 0; j < 3*MAX; j++){
				if(tab[i + 1][j] == 2){
					tab[i][j] = 2;
				} else if(tab[i][j] == 2 && tab[i + 1][j] != 2){
					tab[i][j] = 0;
				}
			}
		}
	}
}

void process(){
	rotation = 0;
	bool ANS = false;
	for(int q = 0; q < Q; q++){
		rotate(moves[q]);
		if(far_move()){
			ANS = true;
			break;
		}
	}	
	if(ANS){
		cout << "TAK" << endl;
	} else {
		cout << "NIE" << endl;
		rotate(0);
		// output();
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
