## 树与图的存储

树是一种特殊的图，与图的存储方式相同。
对于无向图中的边ab，存储两条有向边a->b, b->a。
因此我们可以只考虑有向图的存储。

(1) 邻接矩阵：g [a] [b] 存储边 a->b

(2) 邻接表：

```C++
// 对于每个点i，开一个单链表，存储i所有可以走到的点。
int h[N],  	 //h[i]存储这个单链表的头结点的下标
	e[N],	//表示
	ne[N],
	idx;

// 添加一条边a->b
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
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
        int j = e[i];	//
        if (!check[j])  //
        {
            dfs(j);
        }
    }
}
```

