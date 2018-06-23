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

#define INF 1000000007

typedef long long ll;
using namespace std;

struct Edge {
    int from;
    int to;
    int w;
    Edge(int from = -1, int to = -1, int w = 0): from(from), to(to), w(w) {}
};

Edge** edges;
int n, m;
vector< vector< pair<int, int> > > g;

vector<int> mt;
vector<char> used;
 
bool kuhn (int v) {
	if (used[v])
        return false;
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i].first;
		if (mt[to] == -1 || kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

bool ford_bellman() {
	vector<int> d(2*n, 0);
	vector<Edge*> p(2*n);
	int x;
	for (int i = 0; i < 2*n; i++) {
		x = -1;
		for (int j = 0; j < m; j++) {
            const Edge e = *(edges[j]);
			if (d[e.from] < INF)
				if (d[e.to] > d[e.from] + e.w) {
					d[e.to] = max(-INF, d[e.from] + e.w);
					p[e.to] = edges[j];
					x = e.to;
				}
        }
	}
 
	if (x != -1) {
		int y = x;
		for (int i = 0; i < 2*n; i++)
			y = (*p[y]).from;

        bool first = true;
		for (int cur = y; ; cur = (*p[cur]).from) {
			if (cur == y && !first)  
                break;
            first = false;
            const Edge cur_e = *(p[cur]);
            if (cur_e.from >= n && cur_e.w > 0)
                 mt[cur_e.from-n] = cur_e.to;
		}
        return true;
	}
    return false;
}

void print_result() {
    int result = 0;
    for (int i = 0; i < n; i++) {
        int x = mt[i], y = i;
        for (int j = 0; j < g[x].size(); j++)
            if (g[x][j].first == y)
                result += g[x][j].second;
    }
    printf("%d", -result);
}

int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG
    scanf("%d", &n);
    g.resize(n);
    int k, day, risk;
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d %d", &day, &risk);
            g[i].push_back(make_pair(day-1, -risk));
            m++;
        }
    }

    mt.assign(n, -1);
	vector<char> used_gr(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < g[i].size(); j++)
			if (mt[g[i][j].first] == -1) {
				mt[g[i][j].first] = i;
				used_gr[i] = true;
				break;
			}
	for (int i = 0; i < n; i++) {
		if (used_gr[i])  
            continue;
		used.assign(n, false);
		kuhn(i);
	}

	for (int i = 0; i < n; i++)
		if (mt[i] == -1){
            printf("-1");
            return 0;
        }
  
    edges = new Edge*[m];
    do {
        int k = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < g[i].size(); j++) {
                int to = g[i][j].first, w = g[i][j].second; 
                if (mt[to] == i) 
                    edges[k++] = new Edge(i, n+to, w);
                else 
                    edges[k++] = new Edge(n+to, i, -w);
                
            }
    } while (ford_bellman());
    print_result();
    return 0;
}
