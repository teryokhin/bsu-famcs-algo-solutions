#pragma comment(linker, "/STACK:268435456")

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <ctime>
#include <queue>

#define INF 2000000011

typedef long long ll;
using namespace std;



int main()
{
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG
    int n, m, t;
    scanf("%d %d", &n, &m);
    
    vector< pair<int, int> > parts;
    parts.reserve(n);
    for (int i = 0; i < n; i++){
        scanf("%d", &t);
        parts.push_back(make_pair(t, i)); // <time, id>
    }
    int* machine_for_part = new int[n]; 
    sort(parts.rbegin(), parts.rend());
    
    priority_queue< pair<int, int> > machines; // <-time, id>
    for (int i = 0; i < m; i++)
        machines.push(make_pair(0, i));
    
    int work_time = 0;

    for (auto part: parts) {
        auto machine = machines.top();
        machines.pop();
        machine_for_part[part.second] = machine.second;
        int new_time = machine.first - part.first;
        work_time = max(work_time, -new_time);
        machines.push(make_pair(new_time, machine.second));
    }
    printf("%d\n", work_time);
    for (int i = 0; i < n; i++) {
        printf("%d ", machine_for_part[i]+1);
    }
    return 0;
}