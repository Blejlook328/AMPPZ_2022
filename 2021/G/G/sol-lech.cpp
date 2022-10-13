#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const LL infty = 2e18+1;

struct node
{
    LL A;  // < A: zgon
    LL B;  // <= B: B-M
    LL M;  // => B: x-M
    LL D;  // na końcu nie może być >D
    node() : A(1),B(1),M(0),D(infty) {};
    node(LL _A, LL _B, LL _M, LL _D) : A(_A), B(_B), M(_M), D(_D) {};
    node(char c, LL x)
    {
        A = B = 1;
        M = 0;
        D = infty;
        switch (c)
        {
            case 'B' : M = x; break;
            case 'C' : B = x; break;
            case 'K' : A = x; D = x; break;
        }
    }
};

node operator*(node u, node v)
{
    node x;
    LL _M = u.M+v.M;
    LL _A = u.A;
    if (v.A+u.M>u.B)
        _A = max(_A,v.A+u.M);
    LL _B = max(u.B,v.B+u.M);
    LL _D = u.D;
    if (u.D<v.A)
        _A = infty;
    if (u.D<v.B)
        _D = v.B;
    _D -= v.M;
    _D = min(_D,v.D);
    return node(_A,_B,_M,_D);
}


void one()
{
    int n, q;
    LL H;
    cin >> n >> q >> H;
    int K = 1;
    while(K<=n)
        K *= 2;
    vector<node> T(2*K);
    for(int i=0; i<n; i++)
    {
        char station;
        LL x;
        cin >> station >> x;
        T[K+i] = node(station,x);
    }
    T[K+n] = node(infty,infty,0,0);
    for(int i=K-1; i>=1; i--)
        T[i] = T[2*i]*T[2*i+1];
    for(int i=0; i<q; i++)
    {
        char command;
        cin >> command;
        if (command=='Z')
        {
            char station;
            int change;
            LL x;
            cin >> change >> station >> x;
            change--;
            T[K+change] = node(station,x);
            int y = (K+change)/2;
            while(y>0)
            {
                T[y] = T[2*y]*T[2*y+1];
                y = y/2;
            } 
        } else
        {
            int start;
            cin >> start;
            start--;
            int s = start;
            int v = K+start;
            int k = 1;
            bool rise = true;
            node pref;
            while(k>0)
            {
                if (rise && s%(2*k)==0 && s+2*k<=K)
                {
                    k = 2*k;
                    v = v/2;
                    continue;
                }
                node test = pref*T[v];
                if (H<test.A || max(H,test.B)<=test.M || test.D<=0)
                    rise = false;
                else
                {
                    pref = test;
                    v++;
                    s += k;
                }
                if (!rise)
                {
                    k = k/2;
                    v = 2*v;
                }
            }
            if (s==start)
                cout << -1 << endl;
            else
                cout << s << endl;
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int TT;
    cin >> TT;
    while(TT--)
        one();
}
