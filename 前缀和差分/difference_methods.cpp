//一维差分
//所谓差分法就是指假想原数列为前缀和数列，根据前缀和数列倒推差分数列，也就是前缀和的求逆运算。
//推导公式，这里 b 为 a 的差分数列
    b[l] += c;
    b[r + 1] -= c;

//示例，给定数列 a, 对其 l 到 r 范围内的数加上 c , 重复此操作 m 次，输出操作后的数列 a
#include<iostream>
using namespace std;
const int N = 100010;
int n,m;
int a[N],b[N];
void insert(int l, int r, int c)
{
    b[l] += c;
    b[r + 1] -= c;

}
int main(){
    cin >> n >> m;
    for(int i =  1;i <= n; ++i)
    {
        scanf("%d",&a[i]);

        //假想原a[]上数值全为0，则此时差分数列b[]上数值也应全为0
        //此时让 a[i] 位置上的 ‘0’ 加上 a[i] 位置上实际的值则
        //根据推导公式，通过此步骤实现在 a[]的 [i,i] 范围上加上a[i]
        //也就是 a[i]{假定此时值为0} += a[i]{实际值}，相当于通过 n 步加法实现了由全为 ‘0’ 的a[] 转变为 --> 存储实际值的a[]
        insert(i,i,a[i]);
    }

    while(m--)
    {
        int l ,r, c;
        cin >> l >> r >> c;

        //在 b 中对应位置的数加上 C
        insert(l,r,c);
    }

    for(int i =  1;i <= n; ++i)
    {
        //此时 b 中 相应位置上的数都加上或减去了 C, 再由差分数列 b 推导出前缀和数列 a
        a[i] = a[i - 1] + b[i];
        cout << a[i] << " ";
    }
    return 0;
}