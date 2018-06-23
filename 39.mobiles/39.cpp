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
#include <map>

#define INF 2000000011

#ifdef _DEBUG
    #define fin cin
    #define fout cout
#endif // _DEBUG

typedef long long ll;
using namespace std;

struct yNode {
    int sum;
    yNode* left;
    yNode* right;
    yNode(int sum): sum(sum), left(nullptr), right(nullptr) {}
};

struct xyNode {
    yNode* subtree;
    xyNode* left;
    xyNode* right;
    xyNode(int sum): subtree(new yNode(sum)), left(nullptr), right(nullptr) {}
};

int n;

int yGetSum(yNode* t) {
    return (t)?t->sum:0;
}


void yInc(yNode* t, int l, int r, int y, int delta){
    if(l == r) {
        t->sum += delta;
        return;
    }
    int m = (l+r)/2;
    if (y <= m) {
        if (!t->left) t->left = new yNode(0);
        yInc(t->left, l, m, y, delta);
    } else {
        if (!t->right) t->right = new yNode(0);
        yInc(t->right, m+1, r, y, delta);
    }
    t->sum = yGetSum(t->left) + yGetSum(t->right);
}

int ySum(yNode* t, int l, int r, int from, int to) {
    if (from > to) return 0;
    if (l == from && r == to) return t->sum;
    int m = (l+r)/2;
    int sum_left = t->left? ySum(t->left, l, m, from, min(to, m)) : 0;
    int sum_right = t->right? ySum(t->right, m+1, r, max(from, m+1), to) : 0;
    return sum_left + sum_right;
}

void xyInc(xyNode *t, int l, int r, int x, int y, int delta)
{
    if(l == r) {
        yInc(t->subtree, 0, n-1, y, delta);
        return;
    }
    int m = (l+r)/2;
    if (x <= m) {
        if (!t->left) t->left = new xyNode(0);
        xyInc(t->left, l, m, x, y, delta);
    } else {
        if (!t->right) t->right = new xyNode(0);
        xyInc(t->right, m+1, r, x, y, delta);
    }
    yInc(t->subtree, 0, n-1, y, delta);
}


int xySum(xyNode* t, int l, int r, int xfrom, int xto, int yfrom, int yto) {
    if (xfrom > xto) return 0;
    if (l == xfrom && r == xto) return ySum(t->subtree, 0, n-1, yfrom, yto);
    int m = (l+r)/2;
    int sum_left = t->left? xySum(t->left, l, m, xfrom, min(xto, m), yfrom, yto) : 0;
    int sum_right = t->right? xySum(t->right, m+1, r, max(xfrom, m+1), xto, yfrom, yto) : 0;
    return sum_left + sum_right;
}

int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        ifstream fin("input.txt");
        ofstream fout("output.txt");
    #endif // _DEBUG
    int cmd;
    fin >> cmd >> n;

    int x1, y1, x2, y2, d;
    xyNode* root = new xyNode(0);

    while (fin >> cmd) {
        if (cmd == 3) break;
        if (cmd == 1) {
            fin >> x1 >> y1 >> d;
            xyInc(root, 0, n-1, x1, y1, d);
        }
        if (cmd == 2) {
            fin >> x1 >> y1 >> x2 >> y2;
            fout << xySum(root, 0, n-1, x1, x2, y1, y2) << '\n';
        }
    }

    return 0;
}
