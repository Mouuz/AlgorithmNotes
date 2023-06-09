# Trie字典树

## 是什么

​	用于高效的存储和查找字符串集合的数据结构，是一种多叉树

​	在OJ上一般使用二维数组来表示Trie，一般为 **son [parent] [son] **

​	实际工程中用哈希表实现。

## 示例代码

```C++
题目： 输入N个字符串，求某个字符串出现次数 	

#include <iostream>
using namespace std;
const int N = 100010

int son[N][26]; // 存放Trie树
int cnt[N]; // 以结点 cnt[i] 结尾的字符串的个数
int idx; // 结点标记计数

//建树
void insert(char str[])
{
    int p = 0;
    for(int i = 0; str[i]; ++i)
    {
        int u = str[i] - 'a';  //求出str[i]对应的son的二维下标
        if(!son[p][u]) son[p][u] = ++idx; //若不存在则建立该结点，值通过idx分配而来，全局唯一
        p = son[p][u]; // "指针p"移动至下一结点
    }
    cnt[p]++;  //此时p已移动至字符串最后一节点位置，对以该结点结束字符串次数+1
}

//查树中是否有str
int query(char str[])
{
    int p = 0;
    for(int i = 0; str[i]; ++i)
    {
        int u = str[i] - 'a';
        if(!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}
    
int main()
{
    /.../
    return 0;
}
```



## 怎么理解son [parent] [son] 

Tire树本质上一个多叉树，最多可以分多少叉呢？因为此题存的都是小写字母，所以是26叉；

这里就解释了son这个二维数组的第二维的含义，就是他最多有26个孩子，那么他是谁呢，他当然是结点了，那结点之间怎么区分，或者这些孩子的爸爸叫啥，爸爸们用下标来区别，所以第一维就是爸爸们的id，son[0] [1]含义就是0号爸爸有个儿子b ，那son[0] [1] = 2，就是0号爸爸有个儿子b，儿子的id是2； 这些id就是由idx` 来赋值的；

idx可以理解为计划生育的管理局的给上户口的，生一个孩子，给孩子上身份证，证件上ID 为++idx ，而孩子叫啥，其实就是26个小写字母中的其中一个了；

对于每个结点而言，可以知道他有没有这个孩子，有的话叫啥，在哪里；

对于查询，从根节点一路查下来，就可以找到某个字符串在不在；

对于插入字符串，也是一路下来，看有没有这个儿子，没有了给你生个儿子，有了继续给下面找，所以只插入该字符串中原来不存在的字符即可； 也就是利用了公共前缀来降低查询时间的开销以达到提高效率的目的;

“Trie这个名字取自“retrieval”，检索，因为Trie可以只用一个前缀便可以在一部字典中找到想要的单词。”



```c++
题目：N个数中任取2个数进行异或运算，求最大异或值。
    
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010, M = 31 * N;

int a[N], son[M][2], idx;

void insert(int x) //建树
{
    int p = 0;
    for(int i = 30; ~i; --i) 
    {   //对x的二进制串从高到低放入树中
        if(!son[p][x>>i&1])  
            son[p][x>>i&1] = ++idx;
        p = son[p][x>>i&1];
    }
}

int query(int x)
{
    int p = 0, res = 0;
    for(int i = 30; ~i; --i)
    {
        int t = x>>i&1;
        if(son[p][!t]) //判断x的第i位"!t"是否存在，若存在则向"!t"方向走
        {
            res += 1 << i; //此时结果的第i位则可以取1
            p = son[p][!t];
        }else
        {
            p = son[p][t]; //此时结果的第i位则只能取0,故省略 
        }
    }
    return res;
}

int main()
{
    int n, x, res = 0;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        insert(a[i]);
    }
    
    for(int i = 0; i <n; ++i)
    {
        res = max(res, query(a[i]));
    }
    cout << res;
    return 0;
}
```

