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

#define INF 2222200011

#ifdef _DEBUG
    #define fin cin
    #define fout cout
#endif // _DEBUG

typedef long long ll;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        ifstream fin("input.txt");
        ofstream fout("output.txt");
    #endif // _DEBUG
    int n, m;
    fin >> n >> m;
    int a, b, c;
    vector< vector< pair<int, int> > > g(n);
    for (int i = 0; i < m; i++){
        fin >> a >> b >> c;
        g[a-1].push_back(make_pair(b-1, c));
        g[b-1].push_back(make_pair(a-1, c));
    }
    vector< long long > d(n, 22222222222LL);
    priority_queue< pair<long long, int> > q;
    d[0] = 0;
    q.push(make_pair(-d[0], 0));

    while(!q.empty()) {
        int cur = q.top().second;
        long long d_cur = -q.top().first;
        q.pop();
        if (d_cur > d[cur]) continue;
        for (int i = 0; i < g[cur].size(); i++){
            int to = g[cur][i].first;
            int len = g[cur][i].second;
            if (d[cur] + len < d[to]){
                d[to] = d[cur] + len;
                q.push(make_pair(-d[to], to));
            }
        }
    }
    fout << d[n-1];



    return 0;
}
