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
//#define _DEBUG

#ifdef _DEBUG
    #define fin cin
    #define fout cout
#endif // _DEBUG

typedef long long ll;
using namespace std;

int an[101];
int am[101];
int** fMem;

int f(int i, int j)
{
    if (fMem[i][j] != -1) return fMem[i][j];
    if (i == j) return 0;
    if (i+1 == j) return fMem[i][j] = an[i]*am[i]*am[i+1];
    int mn = INF;
    for (int k = i; k < j; k++)
        mn = min(mn, f(i, k)+f(k+1, j)+an[i]*am[k]*am[j]);
    return fMem[i][j] = mn;
}

int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        ifstream fin("input.txt");
        ofstream fout("output.txt");
    #endif // _DEBUG

    int n;
    fin >> n;
    fMem = new int*[n+1];
    for (int i = 0; i < n+1; i++) {
        fMem[i] = new int[n+1];
        for (int j = 0; j < n+1; j++)
            fMem[i][j] = -1;
    }

    for (int i = 0; i < n; i++)
        fin >> an[i] >> am[i];
    fout << f(0, n-1);

    return 0;
}
