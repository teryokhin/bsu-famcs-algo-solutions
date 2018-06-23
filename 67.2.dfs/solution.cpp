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

#ifdef _DEBUG
    #define fin cin
    #define fout cout
#endif // _DEBUG

typedef long long ll;
using namespace std;

int n;
int k = 0;
bool* used;
int* res;
int** g;

void dfs(int v){
    used[v] = true;
    res[v] = ++k;
    for (int i = 0; i < n; i++)
        if (g[v][i] != 0 && !used[i])
            dfs(i);
}


int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        ifstream fin("input.txt");
        ofstream fout("output.txt");
    #endif // _DEBUG
    fin >> n;
    used = new bool[n];
    res = new int[n];
    g = new int*[n];
    for (int i = 0; i < n; i++){
        g[i] = new int[n];
        used[i] = false;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> g[i][j];

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);

    for (int i = 0; i < n; i++)
        fout << res[i] << ' ';




    return 0;
}
