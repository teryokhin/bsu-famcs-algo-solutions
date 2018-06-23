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


struct Tree {
    Tree* next;
    Tree* prev;
    int x, y;
    Tree(int x, int y, Tree* prev, Tree* next): x(x), y(y), prev(prev), next(next) {}
};

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    //#ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    //#endif // _DEBUG
    int n, x, y, parkX, parkY;
    cin >> n >> parkX >> parkY;

    vector< pair<int, int> > trees;
    trees.reserve(n);

    set<int> yCoords;
    yCoords.insert(0); yCoords.insert(parkY); 

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        trees.push_back(make_pair(x, y));
        yCoords.insert(y);
    }
    sort(trees.begin(), trees.end());

    int maxRect = 0;

    Tree* lastTree;
    map<int, vector<Tree*> > treesByY; 

    for (auto y1=yCoords.begin(); y1 != yCoords.end(); y1++){
        int maxDeltaX = 0;
        treesByY.clear();
        lastTree = new Tree(0, *y1, nullptr, nullptr);
        for (auto tree: trees)
            if (tree.second > *y1){
                maxDeltaX = max(maxDeltaX, tree.first-lastTree->x);
                lastTree->next = new Tree(tree.first, tree.second, lastTree, nullptr);
                treesByY[tree.second].push_back(lastTree->next);
                lastTree = lastTree->next;
            }
        maxDeltaX = max(maxDeltaX, parkX-lastTree->x);
        lastTree->next = new Tree(parkX, *y1, lastTree, nullptr);
        lastTree = lastTree->next;
        maxRect = max(maxRect, (parkY-*y1)*maxDeltaX);

        for (auto y2=yCoords.rbegin(); *y2 != *y1; y2++){
            for (Tree* tree_ptr : treesByY[*y2]) {
                Tree* prev = tree_ptr->prev;
                Tree* next = tree_ptr->next;
                maxDeltaX = max(maxDeltaX, next->x - prev->x);
                prev->next = next;
                next->prev = prev;
                delete tree_ptr;   
            }
            maxRect = max(maxRect, (*y2-*y1)*maxDeltaX);
        }
    }
    cout << maxRect;
    return 0;
}