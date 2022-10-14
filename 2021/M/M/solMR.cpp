// Mateusz Radecki
// O(n*log^2(n)+q^5+q^3*log^2(n))

//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
//~ #pragma GCC target ("avx2")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define shandom_ruffle random_shuffle

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
const int nax=1000*1007;
const ll mod=1000*1000*1000+7;
const int kax=107;

int n;
ll m;

ll tab[nax];

vll ciecia;

int k;
vector<pair<pii,pair<int,ll>>> opc[nax];

int daj()
{
	k++;
	opc[k].clear();
	opc[k].reserve(1007);
	return k;
}

void dod(ll &a, ll b)
{
	a=(a+b)%mod;
}

ll fast[kax][kax][kax];

map<pii,int> prerun_map;
map<pii,vi> prerun_set;

vector<pair<pii,pair<int,ll>>> tmp;

int scal(vector<pair<pii,pair<int,ll>>> &wek)
{
	int ret=daj();
	int ma=nax;
	int mb=nax;
	int mc=nax;
	for (auto i : wek)
	{
		ma=min(ma, i.first.first);
		mb=min(mb, i.first.second);
		mc=min(mc, i.second.first);
	}
	for (auto i : wek)
		fast[i.first.first-ma][i.first.second-mb][i.second.first-mc]=0;
	for (auto i : wek)
		fast[i.first.first-ma][i.first.second-mb][i.second.first-mc]+=i.second.second;
	for (auto i : wek)
	{
		if (fast[i.first.first-ma][i.first.second-mb][i.second.first-mc])
		{
			i.second.second=fast[i.first.first-ma][i.first.second-mb][i.second.first-mc]%mod;
			fast[i.first.first-ma][i.first.second-mb][i.second.first-mc]=0;
			opc[ret].push_back(i);
		}
	}
	return ret;
}

int znak(ll a, ll b)
{
	if (a<b)
		return -1;
	if (a>b)
		return 1;
	return 0;
}

int mediana(int a, int b, int c)
{
	vi wek{a, b, c};
	sort(wek.begin(), wek.end());
	if (wek[0]==-1)
		return -1;
	return wek[1];
}

int prerun(int a, int b)
{
	if (a==b)
	{
		if (tab[a]==-1)
			return -1;
		prerun_set[{a, b}]={tab[a]};
		return prerun_map[{a, b}]=tab[a];
	}
	if (a+1==b)
	{
		prerun(a, a);
		prerun(b, b);
		vi wek{tab[a], tab[b]};
		if (wek[0]>wek[1])
			swap(wek[0], wek[1]);
		if (wek[0]==-1)
			return -1;
		prerun_set[{a, b}]=wek;
		return prerun_map[{a, b}]=wek[0];
	}
	int dlu=b-a+1;
	int d1=(dlu+2)/3;
	int d2=(dlu+1)/3;
	int d3=(dlu+0)/3;
	int x=prerun(a, a+d1-1);
	int y=prerun(a+d1, a+d1+d2-1);
	int z=prerun(a+d1+d2, a+d1+d2+d3-1);
	int w=mediana(x, y, z);
	if (w==-1)
		return -1;
	vi wsz;
	for (int i=a; i<=b; i++)
		wsz.push_back(tab[i]);
	sort(wsz.begin(), wsz.end());
	prerun_set[{a, b}]=wsz;
	return prerun_map[{a, b}]=w;
}

int mniejsze(vi &wek, int w)
{
	return lower_bound(wek.begin(), wek.end(), w)-wek.begin();
}

int rek(int a, int b, ll w)
{
	int v=daj();
	if (prerun_map.count({a, b}))
	{
		int x=prerun_map[{a, b}];
		vi &wek=prerun_set[{a, b}];
		int lew=mniejsze(wek, w);
		int row=mniejsze(wek, w+1);
		int pra=wek.size();
		pra-=row;
		row-=lew;
		opc[v].push_back({{pra-lew, row}, {znak(x, w), 1}});
		return v;
	}
	if (a==b)
	{
		opc[v].push_back({{-1, 0}, {-1, 1}});
		opc[v].push_back({{0, 1}, {0, 1}});
		opc[v].push_back({{1, 0}, {1, 1}});
		return v;
	}
	if (a+1==b)
	{
		int x=rek(a, a, w);
		int y=rek(b, b, w);
		for (auto i : opc[x])
			for (auto j : opc[y])
				opc[v].push_back({{i.first.first+j.first.first, i.first.second+j.first.second}, {min(i.second.first, j.second.first), i.second.second*j.second.second%mod}});
		return scal(opc[v]);
	}
	int dlu=b-a+1;
	int d1=(dlu+2)/3;
	int d2=(dlu+1)/3;
	int d3=(dlu+0)/3;
	int x=rek(a, a+d1-1, w);
	int y=rek(a+d1, a+d1+d2-1, w);
	int z=rek(a+d1+d2, a+d1+d2+d3-1, w);
	tmp.clear();
	for (auto i : opc[x])
		for (auto j : opc[y])
			tmp.push_back({{i.first.first+j.first.first, i.first.second+j.first.second}, {(i.second.first==-1)+(j.second.first==-1)+4*(i.second.first==1)+4*(j.second.first==1), i.second.second*j.second.second%mod}});
	v=scal(tmp);
	int u=daj();
	tmp.clear();
	for (auto i : opc[v])
	{
		for (auto j : opc[z])
		{
			int wez=i.second.first+(j.second.first==-1)+4*(j.second.first==1);
			int war=0;
			if ((wez%4)>=2)
				war=-1;
			if ((wez/4)>=2)
				war=1;
			tmp.push_back({{i.first.first+j.first.first, i.first.second+j.first.second}, {war, i.second.second*j.second.second%mod}});
		}
	}
	return scal(tmp);
}

ll inv(ll v)
{
	if (v<=1)
		return v;
	return inv(mod%v)*(mod-mod/v)%mod;
}

ll interpoluj(vll &wek, ll a, ll b)
{
	int r=wek.size();
	ll ret=0;
	for (int i=a; i<a+r; i++)
	{
		ll li=wek[i-a];
		ll mi=1;
		for (int j=a; j<a+r; j++)
		{
			if (i==j)
				continue;
			li=(li*(b-j))%mod;
			mi=(mi*(i-j+mod))%mod;
		}
		dod(ret, li*inv(mi));
	}
	return ret;
}

ll pom[kax][kax];
ll potmni[kax];
ll potwie[kax];

void test()
{
	scanf("%d%lld", &n, &m);
	for (int i=1; i<=n; i++)
		scanf("%lld", &tab[i]);
	ciecia={-1, m-1};
	for (int i=1; i<=n; i++)
	{
		if (tab[i]>=0)
		{
			ciecia.push_back(tab[i]-1);
			ciecia.push_back(tab[i]);
		}
	}
	sort(ciecia.begin(), ciecia.end());
	ciecia.resize(unique(ciecia.begin(), ciecia.end())-ciecia.begin());
	vll dos;
	for (int i=1; i<=n; i++)
		if (tab[i]>=0)
			dos.push_back(tab[i]);
	sort(dos.begin(), dos.end());
	int nieznam=n-(int)dos.size();
	ll sr=0;
	if (!dos.empty())
		sr=dos[dos.size()/2];
	int g=0;
	while(g+1<(int)ciecia.size() && abs(ciecia[g+1]-sr)<abs(ciecia[g]-sr))
		g++;
	ll wyn=0;
	prerun_map.clear();
	prerun_set.clear();
	prerun(1, n);
	tmp.reserve((nieznam+1)*(nieznam+1)*(nieznam+1)*(nieznam+1));
	for (int i=max(1, g-2*nieznam-3); i<=g+nieznam*2+3 && i<(int)ciecia.size(); i++)
	{
		ll a=ciecia[i-1]+1;
		ll b=ciecia[i];
		vll licz;
		k=0;
		ll shoot=a;
		if (!a && b)
			shoot++;
		int g=rek(1, n, shoot);
		for (int x=0; x<=nieznam; x++)
			for (int y=0; y<=nieznam; y++)
				pom[x][y]=0;
		for (auto l : opc[g])
		{
			if (!l.second.first && l.first.second>=l.first.first && l.first.second>-l.first.first)
			{
				ll w=l.second.second;
				int mni=lower_bound(dos.begin(), dos.end(), a)-dos.begin();
				int row=lower_bound(dos.begin(), dos.end(), a+1)-dos.begin();
				int wie=dos.size();
				wie-=row;
				row-=mni;
				
				int wzrow=l.first.second-row;
				int wzmni=(nieznam-wzrow-l.first.first+wie-mni)/2;
				int wzwie=(nieznam-wzrow+l.first.first-wie+mni)/2;
				dod(pom[wzmni][wzwie], w);
			}
		}
		for (ll j=a; j<=b && j<=a+nieznam+3; j++)
		{
			ll w=0;
			potmni[0]=potwie[0]=1;
			for (int l=1; l<=nieznam; l++)
			{
				potmni[l]=(potmni[l-1]*j)%mod;
				potwie[l]=(potwie[l-1]*(m-1-j))%mod;
			}
			for (int x=0; x<=nieznam; x++)
				for (int y=0; y<=nieznam; y++)
					dod(w, potmni[x]*potwie[y]%mod*pom[x][y]);
			licz.push_back(w);
		}
		if (a-1+(int)licz.size()==b)
		{
			for (int j : licz)
				dod(wyn, j);
		}
		else
		{
			int s=0;
			vll daj;
			for (int j : licz)
			{
				s=(s+j)%mod;
				daj.push_back(s);
			}
			dod(wyn, interpoluj(daj, a, b));
		}
	}
	printf("%lld\n", wyn);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
		test();
	return 0;
}
