#pragma comment(linker, "/STACK:67108864")

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <stack>
#include <ctime>
#include <queue>
#include <set>

#define INF 2000000011

typedef long long ll;
using namespace std;

int n, l = 1;

vector< vector< pair<int, int> > > g;
vector<int> d;

vector< vector<int> > p;
vector< vector<int> > me;

int max_edge(int a, int b) {
    if (a == b)
        return 0;
    if (d[a] > d[b])
        swap(a, b);

    int mx = -INF;
    for (int i = l; i >= 0; i--)
        if (d[b] - d[a] >= (1<<i)) {
            mx = max(mx, me[b][i]);
            b = p[b][i];
        }
    if (a == b)
        return mx;

    for (int i = l; i >= 0; i--) {
        if (p[a][i] != p[b][i]) {
            mx = max(mx, max(me[a][i], me[b][i]));
            a = p[a][i];
            b = p[b][i];
        }
    }
    return max(mx, max(me[a][0], me[b][0]));
}

void dfs(int v, int pv, int e = -INF, int depth = 0) {
    d[v] = depth;
	p[v][0] = pv;
	me[v][0] = e;
	for (int i = 1; i <= l; i++) {
		p[v][i] = p[ p[v][i-1] ][i-1];
        me[v][i] = max(me[v][i-1], me[ p[v][i-1] ][i-1]);
    }
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i].first;
		int c =  g[v][i].second;
		if (to != pv)
			dfs (to, v, c, depth + 1);
	}
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG

    cin >> n;
	while ((1<<l) <= n)
        l++;
    g.resize(n); 
    p.resize(n); 
    me.resize(n);
    d.resize(n); 
    int fr, to, c;
    for (int i = 0; i < n; i++) {
        p[i].assign(l+1, 0);
        me[i].assign(l+1, -INF);
    }
    for (int i = 0; i < n-1; i++){
        cin >> fr >> to >> c;
        g[fr-1].push_back(make_pair(to-1, c));
        g[to-1].push_back(make_pair(fr-1, c));
    }
    dfs(0, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> fr >> to;
        cout << max_edge(fr-1, to-1) << '\n';
    }
    
    return 0;
}
