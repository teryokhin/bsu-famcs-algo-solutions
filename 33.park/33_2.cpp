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
#include <list>

#define INF 2000000011

typedef long long ll;
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG
    int n, x, y, parkX, parkY;
    scanf("%d %d %d", &n, &parkX, &parkY);

    vector< pair<int, int> > trees;
    trees.reserve(n);

    set<int> yCoords;
    yCoords.insert(0); yCoords.insert(parkY); 

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        trees.push_back(make_pair(x, y));
        yCoords.insert(y);
    }
    trees.push_back(make_pair(0,0));
    trees.push_back(make_pair(parkX,0));
    trees.push_back(make_pair(0,parkY));
    trees.push_back(make_pair(parkX,parkY));
    sort(trees.begin(), trees.end(), [](const pair<int, int>& l, const pair<int, int>& r){
        if (l.first == r.first)
            return l.second > r.second;
        return l.first < r.first;
    });

    int maxRect = 0;

    vector<int> lBound; 
    vector<int> rBound;
    list< pair<int, int> > curTrees(trees.begin(), trees.end());
    stack< pair<int, int> > st;


    for (auto y1: yCoords){
        if ((parkY-y1)*parkX <= maxRect)
            break;
        for (auto tree_it = curTrees.begin(); tree_it != curTrees.end();) {
            if ((*tree_it).second <= y1)
                tree_it = curTrees.erase(tree_it);
            else
                tree_it++;
        }
        lBound.resize(curTrees.size());
        rBound.resize(curTrees.size());

        int idx = 0;
        while(!st.empty()) st.pop();
        st.push(make_pair(0, -1));
        for (auto tree: curTrees) {
                while (st.top().second >= tree.second)
                    st.pop();
                lBound[idx++] = st.top().first;
                st.push(tree);
            }
        
        idx--;
        while(!st.empty()) st.pop();
        st.push(make_pair(parkX, -1));
        for (auto tree_it = curTrees.rbegin(); tree_it != curTrees.rend(); tree_it++) {
            auto tree = *tree_it;
            while (st.top().second >= tree.second)
                st.pop();
            rBound[idx--] = st.top().first; 
            st.push(tree);
        }

        idx = 0;
        auto prev_tree = curTrees.begin();
        for (auto tree_it = curTrees.begin(); tree_it != curTrees.end(); tree_it++) {
            auto tree = *tree_it;
            maxRect = max(maxRect, (parkY-y1)*(tree.first-(*prev_tree).first));
            maxRect = max(maxRect, (tree.second-y1)*(rBound[idx]-lBound[idx]));
            idx++;
            prev_tree = tree_it;
        }
    }
    printf("%d", maxRect);
    //cerr << "\n\n" << clock() * 1000.0 / CLOCKS_PER_SEC;
    return 0;
}
