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
    int n, m, u, v;
    fin >> n >> m;
    vector< vector<int> > a(n);
    for (int i = 0; i < m; i++){
        fin >> u >> v;
        a[u-1].push_back(v-1);
        a[v-1].push_back(u-1);
    }
    for (int i = 0; i < n; i++) {
        fout << a[i].size() << ' ';
        for (int x : a[i])
            fout << x+1 << ' ';
        fout << '\n';
    }


    return 0;
}
