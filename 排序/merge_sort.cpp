#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int n;
vector<int> temp(n, 0);

void Merge_sort(vector<int> & arr, int l, int r)
{
    if(l >= r) return;
    int mid = l + (r - l >> 1);
    Merge_sort(arr, l, mid);
    Merge_sort(arr, mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r){
        if(arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while(i <= mid) temp[k++] = arr[i++];
    while(j <= r) temp[k++] = arr[j++];

    for(i = l, j = 0; i <= r; ++i, ++j) arr[i] = temp[j]
}


int main()
{
    scanf("%d", &n);
    vector<int> arr(n, 0);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    Quick_sort(arr, 0 , n-1);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    return 0;
}