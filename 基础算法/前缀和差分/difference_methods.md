//一维差分
//所谓差分法就是指假想原数列为前缀和数列，根据前缀和数列倒推差分数列，也就是前缀和的求逆运算。
//推导公式，这里 b 为 a 的差分数列，a 为 b 的前缀和数列（假想）
    b[l] += c;
    b[r + 1] -= c;

//示例，给定数列 a, 对其 l 到 r 范围内的数加上 c , 重复此操作 m 次，输出操作后的数列 a

```c++
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
```

//二维差分
//推导公式

```c++
 b[x1][y1] += c;
 b[x2 + 1][y1] -= c;
 b[x1][y2 + 1] -=c;
 b[x2 + 1][y2 + 1] += c;
```

//示例，对于给定 a[][], 在 x1, y1, x2, y2构成的子矩阵内全部加上 c, 重复此操作 q 次，输出操作完后的二维矩阵。

```c++
#include<iostream>

using namespace std;

const int N = 1010;

int n, m, q;
int a[N][N], b[N][N];

void insert(int x1, int y1, int x2, int y2, int c)
{
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -=c;
    b[x2 + 1][y2 + 1] += c;
}

int main()
{
    cin >> n >> m >> q;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j<= m; ++j)
            cin >> a[i][j];
    

for(int i = 1; i <= n; ++i)
    for(int j = 1; j<= m; ++j)
        //形同一维差分思想， 假想 a[][] 初始全为 ‘0’，每次在 ‘1’ 的范围内加上当前 a[][]的实际值
        insert(i,j,i,j,a[i][j]); 
        
while(q--)
{
    int x1, y1, x2, y2, c;
    cin >> x1 >> y1 >> x2 >> y2 >> c;
    //对差分矩阵做操作，从而使得O(n²)的操作降为O(1)
    insert(x1, y1, x2, y2, c);
}

for(int i = 1; i <= n; ++i)
    for(int j = 1; j<= m; ++j)
        //完成操作后根据差分矩阵求前缀和矩阵即可
        a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + b[i][j];
        
for(int i = 1; i <= n; ++i)
{
    for(int j = 1; j<= m; ++j)
    {
        cout <<a[i][j] << " ";
    }
    cout << endl;
}
return 0;

}
```