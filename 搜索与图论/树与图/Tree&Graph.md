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



## 树与图的DFS遍历   O(m+n)  n:节点数   m:边数

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





## 树与图的BFS遍历  O(m+n)

```C++
queue<int> q;
check[1] = true; // 表示1号点已经被遍历过
q.push(1);

while (q.size())
{
    int t = q.front();
    q.pop();

    for (int i = h[t]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            check[j] = true; // 表示点j已经被遍历过
            q.push(j);
        }
    }
}
```



## 拓扑排序   O(n+m)

```C++
int e[N], ne[N], idx;//邻接表存储图
int h[N];
int q[N], hh = 0, tt = -1;//队列保存入度为0的点，也就是能够输出的点，
int n, m;//保存图的点数和边数
int d[N];////保存各个点的入度

void topsort(){
    for(int i = 1; i <= n; i++){//遍历一遍顶点的入度。
        if(d[i] == 0)//如果入度为 0, 则可以入队列
            q[++tt] = i;
    }
    while(tt >= hh){//循环处理队列中点的
        int a = q[hh++];
        for(int i = h[a]; i != -1; i = ne[i]){//循环删除 a 发出的边
            int b = e[i];//a 有一条边指向b
            d[b]--;//删除边后，b的入度减1
            if(d[b] == 0)//如果b的入度减为 0,则 b 可以输出，入队列
                q[++tt] = b;
        }
    }
    if(tt == n - 1){//如果队列中的点的个数与图中点的个数相同，则可以进行拓扑排序
        for(int i = 0; i < n; i++){//队列中保存了所有入度为0的点，依次输出
            cout << q[i] << " ";
        }
    }
    else//如果队列中的点的个数与图中点的个数不相同，则可以进行拓扑排序
        cout << -1;//输出-1，代表错误
}
```

