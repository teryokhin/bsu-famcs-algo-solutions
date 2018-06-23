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


#define INF 2000000011

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
    int n;
    fin >> n;
    vector< pair<int, int> > pd(n);
    int* in_count = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> pd[i].first >> pd[i].second;
        in_count[i] = 0;
    }
    int m;
    fin >> m;

    int from, to;
    vector< vector<int> > g(n); // reverse graph

    for (int i = 0; i < m; i++) {
        fin >> from >> to;
        g[to-1].push_back(from-1);
        in_count[from-1]++;
    }

    priority_queue< pair<int, int> > q;
    for (int i = 0; i < n; i++)
        if (in_count[i] == 0)
            q.push(make_pair(pd[i].second, i));

    vector<int> res;
    for (int i = 0; i < n; i++) {
        int root = q.top().second;
        q.pop();
        res.push_back(root);
        for (int j = 0; j < g[root].size(); j++)
            if (--in_count[g[root][j]] == 0)
                q.push(make_pair(pd[g[root][j]].second, g[root][j]));
         g[root].clear();
    }

    int time = 0, max_fine = 0, max_fine_v = 0;
    for (int i = res.size()-1; i >= 0; i--){
        time += pd[res[i]].first;
        if (time-pd[res[i]].second >= max_fine) {
            max_fine = time-pd[res[i]].second;
            max_fine_v = res[i];
        }
    }
    fout << max_fine_v+1 << ' ' << max_fine << '\n';
    for (int i = res.size()-1; i >= 0; i--)
        fout << res[i]+1 << '\n';

    return 0;
}
