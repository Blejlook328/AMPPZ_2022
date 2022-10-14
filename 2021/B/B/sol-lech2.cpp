// O(N log^2 N), sety mniejszy-do-większego, ale bez map. Chyba powinno wchodzić.

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>

using namespace std;

typedef map<int,int> MI;
typedef pair<int,int> PI;

void one()
{
    MI rev;
    vector<int> ledger;
    int N, C;
    vector<PI> ans;
    cin >> N >> C;
    vector<int> fwd(N),bck(N),where(N),visited(N,0);
    vector<set<int>> cycles(N);
    vector<PI> in(N);
    int s = 0;
    long long total = 0;
    for(int i=0; i<N; i++)
    {
        cin >> in[i].first >> in[i].second;
        int x = in[i].first-in[i].second;
        if (x<0)
            x = -x;
        total += x;
        ledger.push_back(in[i].first);
    }
    total /= 2;
    sort(ledger.begin(),ledger.end());
    for(int i=0; i<N; i++)
        rev[ledger[i]] = i;
    for(int i=0; i<N; i++)
    {
        int a = rev[in[i].first];
        int b = rev[in[i].second];
        fwd[b] = a;
        bck[a] = b;
        where[a] = i+1;
        visited[i] = 0;
    }
    total += N*(long long)C;
    for(int a=0; a<N; a++)
        if (!visited[a])
        {
            total -= C;
            int x = a;
            while(!visited[x])
            {
                visited[x] = 1;
                cycles[s].insert(x);
                x = fwd[x];
            }
            s++;
        }
    int j = 0;
    while(j<(int)cycles.size())
    {
        while(cycles[j].size()>1)
        {
            int hi = *prev(cycles[j].end());
            int tr = fwd[hi];
            int q = *cycles[j].begin();
            int r = hi;
            while (q<=tr && r>tr)
            {
                q = fwd[q];
                r = bck[r];
            }
            int lo = bck[q];
            if (r<=tr)
                lo = r;
            swap(fwd[lo],fwd[hi]);
            swap(where[fwd[lo]],where[fwd[hi]]);
            ans.push_back(PI(where[fwd[lo]],where[fwd[hi]]));
            bck[fwd[lo]] = lo;
            bck[fwd[hi]] = hi;
            int il = lo;
            int ih = hi;
            do
            {
                il = fwd[il];
                ih = fwd[ih];
            } while(il!=lo && ih!=hi);
            if (ih==hi)
                swap(lo,hi);
            int i = lo;
            do
            {
                cycles[s].insert(i);
                cycles[j].erase(i);
                i = fwd[i];
            } while(i!=lo);
            s++;
        }
        j++;
    }
    cout << total << " " << ans.size() << endl;
    for(auto & p : ans)
        cout << p.first << " " << p.second << endl;
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
