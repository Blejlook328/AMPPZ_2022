#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

typedef pair<int,int> PI;

const vector<PI> diff = {PI(0,-1),PI(0,1),PI(1,0),PI(-1,0)};

int n, m;

void BFS(queue<PI> &Q, vector<vector<int>> &D)
{
    while(!Q.empty())
    {
        PI p = Q.front();
        Q.pop();
        int x = p.first;
        int y = p.second;
        for(auto &q : diff)
        {
            int u = x+q.first;
            int v = y+q.second;
            if (u>=0 && u<n && v>=0 && v<m && D[u][v]==-1)
            {
                D[u][v] = D[x][y]+1;
                Q.push(PI(u,v));
            }
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int TT;
    cin >> TT;
    while(TT--)
    {
        int k;
        cin >> n >> m >> k;
        vector<string> A(n);
        vector<vector<int>> D(n, vector<int>(m,-1));
        vector<vector<int>> E(n, vector<int>(m,-1));
        queue<PI> Q;
        for(int i=0; i<n; i++)
        {
            cin >> A[i];
            for(int j=0; j<m; j++)
                if (A[i][j]=='.')
                {
                    D[i][j] = 0;
                    Q.push(PI(i,j));
                }
        }
        if (Q.empty() || Q.size()==n*m)
        {
            cout << "TAK\n";
            continue;
        }
        BFS(Q,D);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                if (D[i][j]<=k && A[i][j]=='x')
                    A[i][j]='o';
                if (A[i][j]=='x')
                {
                    E[i][j] = 0;
                    Q.push(PI(i,j));
                }
            }
//        for(int i=0; i<n; i++)
//            cerr << A[i] << endl;
        bool ok = true;
        if (Q.empty())
            ok = false;
        BFS(Q,E);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                ok &= (A[i][j]=='.' || E[i][j]<=k);
        cout << (ok ? "TAK\n" : "NIE\n");
    }
}