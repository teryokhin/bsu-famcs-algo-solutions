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
#include <iomanip>


typedef long long ll;
typedef unsigned long long ull;
using namespace std;

#define INF 2000000011
//#define _DEBUG

#ifdef _DEBUG
    #define fin cin
    #define fout cout
#else
    ifstream fin("littera.in");
    ofstream fout("littera.out");
#endif // _DEBUG

vector<int> p;

void prefix_func(string s)
{
    int n = s.size();
    p.resize(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = p[i-1];
        while (j > 0 && s[i] != s[j])
            j = p[j-1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
}

int readSpecialStr(char* s, int n) {
    int k = 0; char c;
    for (int i = 0; i < n; i++){
        do {
            fin >> noskipws >> c;
        } while (c == '\n');
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
            s[k++] = c;
    }
    return k; // on empty
}



string minShift(string s) {
    int n = s.size();
    s = s+s;
    const ll MOD1 = 1e9+7;
    //const ll MOD2 = 1e9+9;
    const ll HASH_KEY = 31;
    //const ll HASH_KEY2 = 37;
    ll *h = new ll[s.size()+1];
    //ll *h2 = new ll[s.size()+1];
    ll *pow = new ll[n+1];
    //ll *pow2 = new ll[n+1];
    h[0] = 0;
    //h2[0] = 0;
    pow[0] = 1;
    //pow2[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        h[i] = (HASH_KEY * h[i-1] + s[i-1])%MOD1;
        //h2[i] = (HASH_KEY2 * h2[i-1] + s[i-1])%MOD2;
        if (i <= n) pow[i] = (pow[i-1]*HASH_KEY)%MOD1;
        //if (i <= n) pow2[i] = (pow2[i-1]*HASH_KEY2)%MOD2;
    }

    int first = 0;
    for (int k = 1; k < n; k++) {
        int l = 0, r = n-1;
        int res = 0;
        while (l <= r) {
            int len = (l + r) / 2;
            ll h_res = (h[first + len] - h[first] * pow[len])%MOD1;
            //ll h_res2 = (h2[first + len] - h2[first] * pow2[len])%MOD2;
            ll h_cur = (h[k + len] - h[k] * pow[len])%MOD1;
            //ll h_cur2 = (h2[k + len] - h2[k] * pow2[len])%MOD2;
            if (h_res < 0) h_res += MOD1;
            //if (h_res2 < 0) h_res2 += MOD2;
            if (h_cur < 0) h_cur += MOD1;
            //if (h_cur2 < 0) h_cur2 += MOD2;
            if (h_res == h_cur ) {
                res = len;
                l = len + 1;
            }
            else {
                r = len - 1;
            }
        }
        if (s[first + res] > s[k + res])
            first = k;
    }
    return s.substr(first, n);
}


int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    fin >> n;
    char* s1 = new char[n+1];
    char* s2 = new char[n+1];
    int k = readSpecialStr(s1, n);
    readSpecialStr(s2, n);
    string keyString(k, 0);
    for (int i = 0; i < k; i++) {
        int diff = s2[i]-s1[i];
        if (diff <= 0) diff += 26;
        keyString[i] = 'a'-1 + (char)diff;
    }
    prefix_func(keyString);
    string key = keyString.substr(0, keyString.size()-p[keyString.size()-1]);
    fout << minShift(key);


    return 0;
}