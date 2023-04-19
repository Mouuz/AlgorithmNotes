# Hash

拉链法

```C++
const int N = x;  //x为给定数据范围即可

int Hash[N],     //hash数组 
	e[N],		//存储链表节点
	ne[N], 		//存储链表节点的下一节点的下标
	idx;		//记录当前已经用到了数组的哪个位置的下标来存储新加入的链表节点

void insert(int x)
{
    int k = (x % N + N) % N;
    e[idx] = x;
    ne[idx] = Hash[k];
    Hash[k] = idx++;
}

bool query(int x)
{
    int k = (x % N + N) % N;    //简易哈希函数，可改为其他
    for(int i = Hash[k]; ~i; i = ne[i])
    {
        if(e[i] == x)
            return true;
    }
    return false;
}

memset(Hash, -1, sizeof(Hash)); //初始化哈希数组内所有元素值为 -1 作为链表的末尾
```



开放寻址法

```C++
const int N = x;  //x为给定数据范围即可

int Hash[N],   //hash数组 
	NULL = 0x3f3f3f3f;   //初始化hash数组的值，大于给定数据范围即可

//函数返回 x 映射在 Hash数组上的位置值。若 x 存在，则表示其在Hash数组中所在的位置
//若 x 不存在，则表示 x 应该存储在Hash数组中的位置
int find(int x)  
{
    int k = (x % N + N) % N;
    while(Hash[k] != NULL && Hash[k] != x)
    {
        k++;
        if(k == N) k = 0;
    }
    return k;
}

memset(Hash, 0x3f, sizeof(Hash)); //注：该函数按字节赋值
```



## 字符串哈希（字符串前缀哈希）

思路：

​	1.将字符串看做 **P** 进制的数。

​	eg:   ABCD 可以看作为 **(1234)p** 也就是 **P** **进制**下的数字 **1234**，那么 **(1234)p** 对应的十进制数为：
$$
1*p^3 + 2*p^2 + 3*p^1 + 4*p^0
$$

 2. 由于字符串长度可能会很长，这会导致转换的数字过大不方便存储，所以对其进行**mod**运算，所以为：
    $$
    (1*p^3 + 2*p^2 + 3*p^1 + 4*p^0)\ mod \ Q
    $$
     通过上述操作可将字符串映射到 **0 ~ Q-1** 范围内某个数上。

    

    ### 注：

    ​		不能将字符映射为 **0**，这会导致 "A"  "AA" "AAA" 无法区分

    ​		这里不考虑发生哈希冲突的情况 。这里按照 y总的经验， 将 **p = 131 或 13331、 Q = 2^64** 时，哈希冲突情况很小。

    

 3. 维护一个 Hash 数组 Hash[N], Hash[i] 表示从第 1 个字符到第 i 个字符所构成的子串的Hash值,也就是**1~ i 的前缀的hash值**

    eg: 对于字符串 "ABCDE"

    ​	  Hash[0] = 0 (默认值，一般从 1 开始使用)  

    ​	  Hash[1] = "A"的 hash值

    ​	  Hash[2] = "AB"的 hash值 ....

    对于给定的下标L、R，其 Hash[L]、Hash[R]的值都是已知的，如何求 L~ R 之间子串的 hash值呢？公式为：
    $$
    Hash[R]-Hash[L-1]*p^{R\,-\,L\,+\,1}
    $$
    前缀hash递推公式为：
    $$
    Hash[i]=Hash[i-1]*p+str[i]
    $$
    其逻辑与10进制数往新增最小位相同 

​    题目：https://www.acwing.com/problem/content/843/

```C++
#include<iostream>

using namespace std;
using ULL = unsigned long long;

const int N = 100010, P = 131;
char str[N];
ULL Hash[N], p[N];    //这里通过 UUL来存储相当于 mod 2^64,溢出部分被忽略了

ULL get(int l, int r)
{
    return Hash[r] - Hash[l - 1] * p[r - l + 1];  //求子串hash值的递推公式
}

int main()
{
    int n,m;
    scanf("%d%d%s", &n, &m, str + 1);   //从下标1位置开始存储字符串
    p[0] = 1;    // P^0 值为 1
    for(int i = 1; i <= n; ++i)
    {
        p[i] = p[i - 1] * P;   //这里预处理 P^0 ~ P^n 的值方便后续直接运算
        Hash[i] = Hash[i - 1] * P + str[i]; //通过递推公式得到前缀1~i子串的Hash值
    }
    while(m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if(get(l1,r1) == get(l2,r2)) puts("Yes");  //直接判断两段字符串的Hash值是否相同即可
        else puts("No");
    }
    return 0;
}
```
