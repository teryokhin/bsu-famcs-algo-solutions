#include <iostream>
#include <fstream>

using namespace std;

bool isHeap(int* arr, int n, int idx = 1) {
    if (idx > n)
        return true;
    else
        return arr[idx/2] <= arr[idx] && isHeap(arr, n, idx*2) && isHeap(arr, n, idx*2+1);
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;
    int* arr = new int[n+1];
    for (int i = 1; i <= n; i++)
        fin >> arr[i];
    arr[0] = arr[1];
    if (isHeap(arr, n))
        fout << "Yes\n";
    else
        fout << "No\n";
    return 0;
}
