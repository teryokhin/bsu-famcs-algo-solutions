#pragma comment(linker, "/STACK:268435456")

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>
#include <ctime>

#define INF 2000000011

typedef long long ll;
using namespace std;

int TOTAL_COUNT;
int TOTAL_ALIVE;
int ROW_COUNT;
int COL_COUNT;
int DIAG_COUNT;

vector<char> rowEven;
vector<char> colEven;
vector<char> d1Even;
vector<char> d2Even;

vector<int> rowFree;
vector<int> colFree;
vector<int> d1Free;
vector<int> d2Free;


int rowEvenCount;
int colEvenCount;
int d1EvenCount;
int d2EvenCount;

struct Cell {
    const int rowN;
    const int colN;
    const int d1N;
    const int d2N;
    bool value;
    const bool dead;
    Cell(bool value, int rowN, int colN, int d1N, int d2N, bool dead): 
        value(value), rowN(rowN), colN(colN), d1N(d1N), d2N(d2N), dead(dead) {
            if (!dead){
                TOTAL_ALIVE++;
                rowFree[rowN]++;
                colFree[colN]++;
                d1Free[d1N]++;
                d2Free[d2N]++;
            } 

        }
    void set(bool val){
        if (val != value){
            value = val;
            rowEven[rowN] = !rowEven[rowN];
            if (rowEven[rowN]) rowEvenCount++;
            else rowEvenCount--;

            colEven[colN] = !colEven[colN];
            if (colEven[colN]) colEvenCount++;
            else colEvenCount--;

            d1Even[d1N] = !d1Even[d1N];
            if (d1Even[d1N]) d1EvenCount++;
            else d1EvenCount--;

            d2Even[d2N] = !d2Even[d2N];
            if (d2Even[d2N]) d2EvenCount++;
            else d2EvenCount--;
        }
    }
    void setUsed(bool val) {
        int d = val?-1:1;
        rowFree[rowN] += d;
        colFree[colN] += d;
        d1Free[d1N] += d;
        d2Free[d2N] += d;
    }
};

vector<Cell> cells;

vector<char> cell_order_used;
vector<Cell*> cell_order;


void print_current_state() {
    int t = 0;
    for (int i = 0; i < ROW_COUNT; i++){
        for (int j = 0; j < COL_COUNT; j++){
            if (cells[t].dead) {
                printf("-1 ");
            } else {
                (cells[t].value)?printf("1 "):printf("0 ");
            }
            t++;
        }
        printf("\n");
    }
    printf("\n");
}

bool check_possible(Cell* curCell) {
    if ((rowFree[curCell->rowN] == 0 && !rowEven[curCell->rowN]) ||
        (colFree[curCell->colN] == 0 && !colEven[curCell->colN]) ||
        (d1Free[curCell->d1N] == 0 && !d1Even[curCell->d1N]) ||
        (d2Free[curCell->d2N] == 0 && !d2Even[curCell->d2N])    
    )   return false;
    return true;
}

void check_timelimit() {
    if (clock() * 1000.0 / CLOCKS_PER_SEC > 950)
        exit(0);
}

void brute_force(int cur, int alive_left)
{
    if (cur == TOTAL_COUNT){
        if (rowEvenCount == ROW_COUNT &&
            colEvenCount == COL_COUNT &&
            d1EvenCount == DIAG_COUNT &&
            d2EvenCount == DIAG_COUNT) 
            print_current_state();
        check_timelimit();
    }
    else {
        if (ROW_COUNT - rowEvenCount > alive_left ||
            COL_COUNT - colEvenCount > alive_left ||
            DIAG_COUNT - d1EvenCount > alive_left ||
            DIAG_COUNT - d2EvenCount > alive_left)
                return; 

        if (cell_order[cur]->dead)
            brute_force(cur+1, alive_left);
        else {
            bool old_value = cell_order[cur]->value;
            cell_order[cur]->setUsed(true);
            
            if (check_possible(cell_order[cur]))
                brute_force(cur+1, alive_left-1);
            
            cell_order[cur]->set(!old_value);
            if (check_possible(cell_order[cur]))
                brute_force(cur+1, alive_left-1);
            
            cell_order[cur]->set(old_value);
            cell_order[cur]->setUsed(false);
        }
    }
}

void add_to_order(int x, int y) {
    if (!(0 <= x && x < ROW_COUNT) || !(0 <= y && y < COL_COUNT))
        return;
    if(!cell_order_used[x*COL_COUNT+y]){
        //printf("=== %d %d\n", x, y);
        cell_order.push_back(&cells[x*COL_COUNT+y]);
        cell_order_used[x*COL_COUNT+y] = true;
    }
}


int main()
{
    #ifndef _DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout); 
    #endif // _DEBUG
    int n, m, t;
    scanf("%d %d", &n, &m);
    
    TOTAL_COUNT = n*m;
    TOTAL_ALIVE = 0;
    ROW_COUNT = n;
    COL_COUNT = m;
    DIAG_COUNT = n+m-1;

    rowEven.assign(ROW_COUNT, true); rowEvenCount = ROW_COUNT;
    colEven.assign(COL_COUNT, true); colEvenCount = COL_COUNT;
    d1Even.assign(DIAG_COUNT, true); d1EvenCount = DIAG_COUNT;
    d2Even.assign(DIAG_COUNT, true); d2EvenCount = DIAG_COUNT;

    rowFree.assign(ROW_COUNT, 0);
    colFree.assign(COL_COUNT, 0);
    d1Free.assign(DIAG_COUNT, 0);
    d2Free.assign(DIAG_COUNT, 0);

    cells.reserve(TOTAL_COUNT);
    cell_order_used.assign(TOTAL_COUNT, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &t);
            cells.push_back(Cell(
                false,
                i, j, i+j, m-1+i-j,
                (t == -1)
            ));
        }
    
    for(int k = 0; k <= DIAG_COUNT/2; k++) {
        for(int i = 0; i <= k; i++) {
            add_to_order(i, k-i);
            add_to_order(i, m-1-(k-i));
            add_to_order(n-1-i, m-1-(k-i));
            add_to_order(n-1-i, k-i);
        }
    }
    brute_force(0, TOTAL_ALIVE);       
    return 0;
}