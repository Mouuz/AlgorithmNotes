```C++
//快速选择算法
//整体思路和快速排序相同，只是在递归部分做选择判断
int quicksort(vector<int>& arr, int l, int r, int k) {
    if (l >= r) return arr[l];
    int i = l - 1, j = r + 1, x = arr[l + rand() % (r - l + 1)];
    while (i < j)
    {
        do i++; while (arr[i] < x);
        do j--; while (arr[j] > x);
        if (i < j) swap(arr[i], arr[j]);
    }
    //这里求划分后的左半区间的长度 sl，若 k<= sl则说明第 k 个数位于左区间，
    //此时只需继续在左区间递归寻找。否则则表明其位于右区间，需在右区间递归需
    //找。(**注**此时 k 的值为全区间范围内的第 k 个数，对于只在右区间递归时，需
    //减去左区间长度才为第 k 个数在右区间的正确坐标值）
    int sl = j - l + 1;
    if (k <= sl)
        return quicksort(arr, l, j, k);
    return quicksort(arr, j + 1, r, k - sl);
}
```

