```C++
//����ѡ���㷨
//����˼·�Ϳ���������ͬ��ֻ���ڵݹ鲿����ѡ���ж�
int quicksort(vector<int>& arr, int l, int r, int k) {
    if (l >= r) return arr[l];
    int i = l - 1, j = r + 1, x = arr[l + rand() % (r - l + 1)];
    while (i < j)
    {
        do i++; while (arr[i] < x);
        do j--; while (arr[j] > x);
        if (i < j) swap(arr[i], arr[j]);
    }
    //�����󻮷ֺ���������ĳ��� sl���� k<= sl��˵���� k ����λ�������䣬
    //��ʱֻ�������������ݹ�Ѱ�ҡ������������λ�������䣬����������ݹ���
    //�ҡ�(**ע**��ʱ k ��ֵΪȫ���䷶Χ�ڵĵ� k ����������ֻ��������ݹ�ʱ����
    //��ȥ�����䳤�Ȳ�Ϊ�� k ���������������ȷ����ֵ��
    int sl = j - l + 1;
    if (k <= sl)
        return quicksort(arr, l, j, k);
    return quicksort(arr, j + 1, r, k - sl);
}
```

