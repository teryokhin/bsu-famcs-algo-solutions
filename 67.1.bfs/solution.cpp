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

int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        ifstream fin("input.txt");
        ofstream fout("output.txt");
    #endif // _DEBUG
    int n;
    fin >> n;
    bool* used = new bool[n];
    int* res = new int[n];
    int** g = new int*[n];
    for (int i = 0; i < n; i++){
        g[i] = new int[n];
        used[i] = false;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fin >> g[i][j];

    int k = 0;
    queue<int> q;
    while (k < n){
        for (int i = 0; i < n; i++)
            if (!used[i]) {
                q.push(i);
                used[i] = true;
                break;
            }

        while (!q.empty()){
            int cur = q.front();
            q.pop();
            res[cur] = ++k;
            for (int i = 0; i < n; i++)
                if (g[cur][i] != 0 && !used[i]){
                    q.push(i);
                    used[i] = true;
                }
        }
    }
    for (int i = 0; i < n; i++)
        fout << res[i] << ' ';




    return 0;
}
