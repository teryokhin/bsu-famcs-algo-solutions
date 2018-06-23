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
#include <map>

#define INF 2000000011

typedef long long ll;
using namespace std;



int main()
{
    srand(time(0));
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "w", stdout);
    int n = rand()%10;
    int x = 1+rand()%10, y = 1+rand()%10;
    cout << n << " " << x <<  " " << y << "\n";
    for (int i = 0; i < n; i++)
        cout << rand()%(x+1) << " " << rand()%(y+1) << "\n";
    return 0;
}
