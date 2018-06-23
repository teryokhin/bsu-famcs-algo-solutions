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
    int n, u, v;
    fin >> n;
    vector<int> res(n, 0);
    for (int i = 0; i < n-1; i++){
        fin >> u >> v;
        res[v-1] = u;
    }

    for (int x : res)
        fout << x << ' ';



    return 0;
}
