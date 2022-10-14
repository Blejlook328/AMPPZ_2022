#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000;
int tab[MAX][MAX];
int N, M, K;

struct element{
	int x, y, s;
};

queue<element> Q;

void input(){
	cin >> N >> M >> K;
	
	string s;
	for(int i = 0; i < N; i++){
		cin >> s;
		for(int j = 0; j < M; j++){
			if(s[j] == '.'){
				tab[i][j] = 0;
			} else {
				tab[i][j] = 1;
			}
		}
	}
}

void QUE(int v){
	// puts all of the coordinates with value v on queue.
	while(!Q.empty()) Q.pop();

	element E;
	E.s = 0;

	for(E.y = 0; E.y < N; E.y++){
		for(E.x = 0; E.x < M; E.x++){
			if(tab[E.y][E.x] == v){
				Q.push(E);
			}
		}
	}
}

void BFS(int iterations, int v1, int v2){
	// runs BFS and changes values form v1 to v2.

	while(!Q.empty()){
		element t = Q.front();
		Q.pop();
		
		if(t.s == iterations) continue;
		t.s++;

		t.y--;
		if(t.y >= 0 && tab[t.y][t.x] == v1){
			tab[t.y][t.x] = v2;
			Q.push(t);
		}
		t.y++;

		t.y++;
		if(t.y < N && tab[t.y][t.x] == v1){
			tab[t.y][t.x] = v2;
			Q.push(t);
		}
		t.y--;

		t.x--;
		if(t.x >= 0 && tab[t.y][t.x] == v1){
			tab[t.y][t.x] = v2;
			Q.push(t);
		}
		t.x++;

		t.x++;
		if(t.x < M && tab[t.y][t.x] == v1){
			tab[t.y][t.x] = v2;
			Q.push(t);
		}
		t.x--;
	}
}

bool process(){
	QUE(0);
	BFS(K, 1, 2);
	
	QUE(1);
	BFS(K, 2, 3);

	for(int y = 0; y < N; y++){
		for(int x = 0; x < M; x++){
			if(tab[y][x] == 2){
				return false;
			}
		}
	}

	return true;
}

int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(0);

	int T;
	cin >> T;
	for(int v = 0; v < T; v++){
		input();

		if(process()){
			cout << "TAK\n";
		} else {
			cout << "NIE\n";
		}
	}
}
