#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
const int nax=1007;

int n, m, k;

char wcz[nax];
int tab[nax][nax];

int odl[nax][nax];

void test()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i=1; i<=n; i++)
	{
		scanf("%s", wcz+1);
		for (int j=1; j<=m; j++)
		{
			tab[i][j]=(wcz[j]=='x');
			if (!tab[i][j])
				odl[i][j]=0;
			else
				odl[i][j]=k+1;
		}
	}
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			if (i>1)
				odl[i][j]=min(odl[i][j], odl[i-1][j]+1);
			if (j>1)
				odl[i][j]=min(odl[i][j], odl[i][j-1]+1);
		}
	}
	for (int i=n; i; i--)
	{
		for (int j=m; j; j--)
		{
			if (i<n)
				odl[i][j]=min(odl[i][j], odl[i+1][j]+1);
			if (j<m)
				odl[i][j]=min(odl[i][j], odl[i][j+1]+1);
		}
	}
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			if (odl[i][j]>k)
				odl[i][j]=k+1;
			else
				odl[i][j]=0;
		}
	}
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			if (i>1)
				odl[i][j]=max(odl[i][j], odl[i-1][j]-1);
			if (j>1)
				odl[i][j]=max(odl[i][j], odl[i][j-1]-1);
		}
	}
	for (int i=n; i; i--)
	{
		for (int j=m; j; j--)
		{
			if (i<n)
				odl[i][j]=max(odl[i][j], odl[i+1][j]-1);
			if (j<m)
				odl[i][j]=max(odl[i][j], odl[i][j+1]-1);
		}
	}
	
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			if ((odl[i][j]>0)!=tab[i][j])
			{
				printf("NIE\n");
				return;
			}
		}
	}
	
	printf("TAK\n");
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
		test();
	return 0;
}
