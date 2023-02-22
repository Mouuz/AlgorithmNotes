#include <iostream>
#include <vector>

using namespace std;


void Quick_sort(vector<int> & array,  int l, int r)
{
    if(l >= r) return;
    int x = array[l + rand() % (r - l + 1)]; // rand btw [l, r]
    int i = l - 1, j = r + 1;
    while(i < j){
        do i++; while(array[i] < x);
        do j--; while(array[j] > x);
        if(i < j) swap(array[i], array[j]);
    }

    Quick_sort(array, l, j);
    Quick_sort(array, j + 1, r);
}


int main()
{
    int n;
    scanf("%d", &n);
    vector<int> array(n, 0);
    for(int i = 0; i <n; i++){
        scanf("%d", &array[i]);
    }
    Quick_sort(array, 0, n -1 );
    for(int i = 0; i <n; i++){
        cout << array[i] << " ";
    }
    return 0;
}
