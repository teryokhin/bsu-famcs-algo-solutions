#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>

using namespace std;

int main()
{
    ofstream fout("tst.in");
    srand(time(NULL));
    int n = 1+rand()%500;
    for (int i = 0; i < n; i++)
        fout << rand()%1000 << endl;
    return 0;
}
