## 树与图的存储

树是一种特殊的图，与图的存储方式相同。
对于无向图中的边ab，存储两条有向边a->b, b->a。
因此我们可以只考虑有向图的存储。

(1) 邻接矩阵：g [a] [b] 存储边 a->b

(2) 邻接表：

​	邻接表不用管执行顺序，只需要知道每个节点能够访问的所有结点就行，链表内的顺序并不重要

```C++
// 对于每个点i，开一个单链表，存储i所有可以走到的点。
int h[N],  	 //h[i]存储是 i的所有邻点组成的单链表的头结点下标。
	e[N],	//i是边编号，e[i]的值是i这条边终点的结点编号
	ne[N],	//i是边编号，ne[i]的值是i这条边同一起点的下一条边的编号
	idx;	//边的编号

// 添加一条边a->b
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

// 初始化
idx = 0;
memset(h, -1, sizeof h);
```



## 树的DFS遍历

```C++
bool check[N];    //标记数组，用于标记已经访问过的节点

void dfs(int u)
{
    check[u] = true; // check[u] 表示点u已经被遍历过

    for (int i = h[u]; i != -1; i = ne[i]) //dfs以u为根节点的所有子树
    {
        int j = e[i];	
        if (!check[j]) 
        {
            dfs(j);
        }
    }
}
```



### 示例题   ☆☆☆重点☆☆☆

树的重心https://www.acwing.com/problem/content/848/

```C++
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010, M = N * 2; //注意这里是无向图， 边的数量为点的两倍

int head[N], e[M], ne[M], idx;
bool check[N];

int n, ans = N;

void add(int a, int b){
    e[idx] = b;
    ne[idx] = head[a];
    head[a] = idx++;
}

int dfs(int u)
{
    check[u] = true;
    int sum = 1, res = 0;
    for(int i = head[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(!check[j])
        {
            int s = dfs(j);
            sum += s;
            res = max(res, s);
        }
    }
    res = max(res, n - sum);
    ans = min(ans, res);
    return sum;
}

int main()
{
    cin >> n;
    memset(head, -1, sizeof head);
    for(int i = 0; i < n - 1; ++i)
    {
        int a,b;
        cin >> a >> b;
        add(a,b), add(b,a);
    }
    dfs(1);
    cout << ans << endl;
}
```

