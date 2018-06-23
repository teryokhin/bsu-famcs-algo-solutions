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
#define NOT_CALCULATED -2000000077


typedef long long ll;
using namespace std;

int total_colors;
int *a;
int *col_count;

int dp_mem[111][111][111];

int dp(int cur, int j, int t) {
    if (cur > total_colors)
        return 0;
    if (dp_mem[cur][j][t] != NOT_CALCULATED)
        return dp_mem[cur][j][t];
    int res = -INF;
    for (int i = 0; i <= j; i++) {
        //if (t <= total_colors - cur)
        res = max(res,
                  -a[col_count[cur] + i] + dp(cur+1, j-i, t)); // don't choose cur color
        if (t > 0)
           res = max(res,
                     a[col_count[cur] + i] + dp(cur+1, j-i, t-1)); // choose cur color
    }
    return dp_mem[cur][j][t] = res;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        freopen("jokers.in", "r", stdin);
        freopen("jokers.out", "w", stdout); 
    #endif // _DEBUG

    for (int i = 0; i < 111; i++)
        for (int i2 = 0; i2 < 111; i2++)
            for (int i3 = 0; i3 < 111; i3++)
                dp_mem[i][i2][i3] = NOT_CALCULATED;

    int c, j, t;
    cin >> total_colors >> c >> j >> t;
    a = new int[c+j+2];
    col_count = new int[total_colors+2];
    for (int i = 0; i < c+j+1; i++)
        cin >> a[i];

    int n, color;
    cin >> n;
    for (int i = 0; i < total_colors+2; i++)
        col_count[i]=0;
    for (int i = 0; i < n; i++){
        cin >> color;
        col_count[color]++;
    }

    cout << dp(1, col_count[0], t);
    
    return 0;
}

