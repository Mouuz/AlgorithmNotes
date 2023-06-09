## 二分图定义：

二分图是指一个无向图中的所有顶点可以被分为两个互不重复的子集，使得子集内的点之间没有边相连，而子集之间的点存在边相连。也可以说，二分图是可以用两种颜色对所有顶点染色，使得相邻的顶点颜色不同的图。这两个子集可以称作二分图的“部”



## 二分图的判定

算法：染色法

思路：

1. 选择一个起点，将其染上颜色 A。
2. 将与该顶点相邻的点染上颜色 B，表示这些点与起点不在一个子集中。
3. 将这些被染上颜色 B 的点与其相邻且未被染色的点继续染色，染成颜色 A。
4. 重复步骤 2 和 3 直到所有的顶点都被染色。

在染色的过程中，如果发现相邻的两个顶点颜色相同即发生了矛盾，说明该图不是二分图。

模板：

```C++
//这里使用dfs来将一个点的所有相邻点染色

int n;      // n表示点数
int h[N], e[M], ne[M], idx;     // 邻接表存储图
int color[N]; //color[x] 表示点 x 的颜色 这里用 1 和 2分别代表不同颜色

bool dfs(int u, int c)  // u : 顶点编号  c ：u 对应的颜色
{
    color[u] = c;  // 将 u 标记上对应的颜色
    for(int i  = head[u]; ~i; i = ne[i]) //遍历点 u 所有相邻的点
    {
        int j  = e[i];
        if(!color[j]) //如果点j未被染色
        {	// 3 - c的含义：如果 c 为 1 则传递到相邻点值就是 2, 如果 c 为 2 则传递到相邻点值就为 1
            if(!dfs(j, 3 - c)) return false; //那就对其和相邻的点进行染色,dfs返回错误则直接返回
        }
        //如果点j已经染过色了，则判断 点j 的颜色和 点u 的颜色也就是值 c 是否相同,相同表明发生矛盾
        else if(color[j] == c)  return false; 
    }
    return true;
}

bool check() //判断是否为二分图
{
    bool flag = true;
    for (int i = 1; i <= n; i ++ ) //对所有点进行遍历检查
        if (!color[i]) //如果未染色就对其和相邻的点染色
        {
             if (!dfs(i, 1))
            {
                flag = false;
                break;
            }
        }   
    return flag;
}
```



## 二分图的最大匹配数

概念：

​	$二分图的匹配$：给定一个二分图 G，在 G的一个子图 M 中，M的边集 {E} 中的任意两条边都不依附于同一个顶点，则称 M是一个匹配。

​	$二分图的最大匹配$：所有匹配中包含边数最多的一组匹配被称为二分图的最大匹配，其边数即为最大匹配数。

算法：匈牙利算法

思路：（这里只是使用通俗个人理解)

1.遍历二分图的一个子集即可，这里假设为M<sub>1</sub>(另一个子集为M<sub>2</sub>)。依次遍历M<sub>1</sub>中每一个顶点。

2.对每个M<sub>1</sub>中的 点$X$ 寻找与其相邻的M<sub>2</sub>中的 点$Y$ 配对，要求该M<sub>2</sub>中的 点$Y$ 处于未配对状态，或是 点$Y$ 已配对 M<sub>1</sub>中的 点$Z$，但 点 $Z$ 能够改为与其他 M<sub>2</sub>中的点配对，使得 点$Y$ 能够被空出来和 点$X$成功配对，此时该二分图的匹配数 + 1。否则表明该 点$X$ 无法匹配上 M<sub>2</sub>中的任意一点，应当略过该点，继续检查 M<sub>1</sub>中后续的点。

模板：

```C++
int n1, n2; //n1: 第一个集合中的数 n2:第二个集合中的数

 // 邻接表存储所有边，匈牙利算法中只会用到从第一个集合指向第二个集合的边，所以这里只用存一个方向的边
int head[N], e[M], ne[M], idx;

bool status[N];	//存储第二集合中的每个点当前匹配的哪一个第一集合中的点
int match[N];

bool find(int u)
{
    //遍历所有和 u 相邻的点
    for(int i = head[u]; ~i; i = ne[i])
    {
        int j = e[i];
        //如果当前考察的相邻点 j 未被选中,则进入后续考察
        if(!status[j])
        {
            //这里status[]的作用在于在递归调用 find()时，当前递归层次中的 j 会被标记，在
            //进入下一层次递归后，上一层已选中的点 j 就不能被再次选中，避免了死递归的发生。
            
            //更通俗的说，当发生递归调用时，说明当前 u 想匹配的 j 已经被另外的点选中（假设为点 z）
            //此时就需要让 z 去寻找另外的相邻点（进入递归的下一层）。在 z 对其所有相邻点考察时，就不能
            //再考察已经匹配的点 j 了（需要把 j 空出来让给 u）,所以需要略过 j 去找寻其他的点。这里就是通过			   //status[]标记作用来实现这个算法策略
            
            //将该点 j 选中
            status[j] = true;
            //检查 j 是否配对了，如果配对了检查 j 的配对对象是否能够另寻一点配对
            if(match[j] == 0 || find(match[j]))
            {
                match[j] = u;
                return true;
            }
        }
    }
    
    return false;
}


// 求最大匹配数，依次枚举第一个集合中的每个点能否匹配第二个集合中的点
int res = 0;
for(int i = 1; i <= n1; ++i)
{
    //每轮要重置status,否则当前n1中的 点i 遇到已匹配的相邻点不会尝试 递归调用find() 而是直接返回，会影响最后结果。
    memset(status, false, sizeof status);
    if(find(i))  	
        res++;
}
```

