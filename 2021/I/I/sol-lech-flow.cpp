// Wzorcówka: algorytm Dinica.
// O((n log n + k)^(3/2))

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct edge
{
    int target;
    int cap;
    int flow;
};

vector<int> P, Q;
vector<vector<int>> G;
vector<edge> E;
vector<bool> visited;
vector<int> dist;
int k, B;
const int infty = 4e6+10;

void add(int x, int y, int w)
{
    edge u;
    u.target = y;
    u.cap = w;
    u.flow = 0;
    E.push_back(u);
    edge v;
    v.target = x;
    v.cap = 0;
    v.flow = 0;
    E.push_back(v);
    G[x].push_back(E.size()-2);
    G[y].push_back(E.size()-1);
}

void bfs(int s)
{
    queue<int> Q;
    dist[s] = 0;
    Q.push(s);
    while(!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for(int z : G[x])
        {
            int y = E[z].target;
            if (E[z].flow<E[z].cap && dist[y]==-1)
            {
                dist[y] = dist[x]+1;
                Q.push(y);
            }
        }
    }
}

bool dfs(int x, int s, int t)
{
    if (x==t)
        return true;
    if (x!=s && visited[x])
        return false;
    if (dist[x]>=dist[t])
        return false;
    for(int z : G[x])
    {
        if (E[z].flow<E[z].cap && !visited[E[z].target] && dist[E[z].target]==dist[x]+1 && dfs(E[z].target,s,t))
        {
            E[z].flow++;
            E[z^1].flow--;
            return true;
        }
    }
    visited[x] = true;
    return false;
}

int go()
{
    int p = P.size();
    int q = Q.size();
    G.clear();
    G.resize(p+3);
    int ssource = p;
    int starget = p+1;
    vector<int> vertex(2*B+1,-1);
    vertex[0] = p+2;
    for(int y : Q)
    {
        int v = G.size();
        int s = y+B;
        int r = -1;
        bool stop = false;
        if (vertex[s]==-1)
        do
        {
            if (vertex[s]!=-1)
                stop = true;
            else
            {
                vertex[s] = v;
                G.push_back(vector<int>());
                v++;
            }
            if (r!=-1)
                add(vertex[s],vertex[r],infty);
            r = s;
            s = s/2;
        } while (!stop);
        add(vertex[y+B],starget,1);
    }
    for(int i=0; i<p; i++)
    {
        add(ssource,i,1);
        int x = P[i]+B;
        int f = k;
        while(f>0)
        {
            if (f%2==0)
            {
                int y = x^(f+1);
                if (vertex[y]!=-1)
                    add(i,vertex[y],1);
            }
            x = x/2;
            f = f/2;
        }
    }
    int total = 0;
    bool any = true;
    do
    {
        any = false;
        visited.clear();
        visited.resize(G.size(),false);
        dist.clear();
        dist.resize(G.size(),-1);
        bfs(ssource);
        int found;
        do
        {
            found = dfs(ssource, ssource, starget);
            total += found;
            any |= found;
        } while(found);
    }
    while(any);
    return p+q-total;
}

void one()
{
    int N;
    cin >> N >> k;
    vector<int> A(N);
    for(int i=0; i<N; i++)
        cin >> A[i];
    sort(A.begin(),A.end());
    int b = 0;
    while((1<<b)<=k)
        b++;
    B = 1<<b;
    int ans = 0;
    for(int i=0; i<N; i++)
    {
        if ((A[i]>>(b-1))%2)
            P.push_back(A[i]%B);
        else
            Q.push_back(A[i]%B);
        if (i==N-1 || ((A[i+1]>>b) > (A[i]>>b)))
        {
            ans = max(ans,go());
            P.clear();
            Q.clear();
        }
    }
    cout << ans << endl;
}

int main()
{
    int TT;
    cin >> TT;
    while(TT--)
        one();
}
