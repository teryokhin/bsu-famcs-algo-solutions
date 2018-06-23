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


int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG
    int n;
    cin >> n;

    int **a = new int*[n+2];
    for (int i = 0; i <= n; i++)
        a[i] = new int[n+2];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            if (i == 0 || j == 0)
                a[i][j] = 0;
            else
                a[i][j] = INF-1;

    int k, day, risk;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> day >> risk;
            a[i][day] = risk;
        }
    }

    vector<int> u(n+2), v(n+2), p(n+2), way(n+2);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv (n+2, INF);
        vector<char> used (n+2, false);
        do {
            used[j0] = true;
            int i0 = p[j0],  delta = INF,  j1;
            for (int j = 1; j <= n; j++)
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            for (int j = 0; j <= n; j++)
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);    
    }

    int cost = -v[0];
    if (cost < INF-1)
        cout << cost;
    else
        cout << -1;

    return 0;
}
