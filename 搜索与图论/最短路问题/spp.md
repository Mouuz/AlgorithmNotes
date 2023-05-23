

<img src=".\最短路问题.png" alt="最短路问题"/>

## 朴素Dijkstra算法  主要用于稠密图

​	思路： 

1. 定义一个最短距离数组`dist`，用于记录从起点到每个顶点的距离，初值为无穷大。
2. 选择一个起点，将起点的距离设为0，加入已访问集合。
3. 对于起点可直接到达的所有顶点，更新它们的距离，如果新的距离比原来的距离更小，则更新`dist[v]`的值。
4. 在所有未访问的顶点中，找到距离起点距离最小的顶点，加入已访问集合。
5. 重复步骤3和步骤4，直到所有顶点都被访问过。

### 时间复杂度：

​	查找距离最近且未确定最短距离的顶点：O(n²)
​	加入集合S：O(n)
​	更新距离：O(m)
​	所以总的时间复杂度为: O(n²)

### 模板:

```C++
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=510;
int n,m;
int g[N][N];//g[ 1 ][ 2 ]是指从1节点指向2节点的距离，特大值可以表示不存在
int dist[N];//distance（距离）的缩写，代表每一个点到源点的距离
bool st[N];//state(状态)的缩写,当st[n]为true时说明这个点到源点的距离最小值就已经确定了
int dijkstra(){
    memset(dist,0x3f,sizeof(dist));//存储每一个点到源点的距离
    dist[1]=0;//源点到自己的距离为0
    for(int i=0;i<n-1;i++){
    //其实这条语句唯一的作用就是循环n-1次（优化了）
    //所以写成for(int i=0;i<n;i++)也可以，因为如果下面的语句循环了n-1次的话，那么所有点都能得到最小值了
    //可以这么理解，每次循环都会确定一个最小值，还会再创造一个最小值（留给下一次循环去确定）
    //当循环n-1次时，情况是已经确定了n-1个点的最小值了，还创造了一个最小值(此时还有1个点等着下一次去确定)
    //那么就不需要下一次循环了，毕竟剩下的就一个点，在1个点的集合中知道有一个点是最小值，顺理成章了
    //当然你想写成for(int i=0;i<n;i++)也能AC
        int t=-1;	//t就是要找的距离最近且未在st中点的下标，这里初始为-1方便后续比较无特殊意义
        for(int j=1;j<=n;j++){
            if(!st[j] && (t==-1 || dist[t]>dist[j])){
                t=j;//!st[j]指的是最近距离还没有确定的点，&& 后面就是找符合！st[j]条件的距离最小的点
                //这一个操作就是找到未确定最小值的 `点集`中的最小点,t==-1是当第一次遇到未确定~的点时能够被初始化
            }
        }
        
        //(1)
        
        for(int j=1;j<=n;j++){
        //现在找到t了，遍历一遍所有点，有一下几种情况
        //1.j点和t点之间无连接，那么g[t][j]=0x3f3f3f3f,特别大，会被pass
        //2.dist[j]<=dist[t]+g[t][j],源点到j点的距离,如果经过t后距离更长或相同了,那么不考虑
        //3.dist[j]>dist[t]+g[t][j], ... 经过t点距离更短了,那么修改dist[j]的值
            dist[j]=min(dist[j],dist[t]+g[t][j]);
        }
        st[t]=true;//当前t点已经把其余点全部遍历了一遍，此点变成确定距离为最小的点了,这条语句放在（1）处也能AC
    }
    if(dist[n]==0x3f3f3f3f){//当前点n没被修改，说明到不了点n，输出-1
        return -1;
    }else{
        return dist[n];//易证
    }
}
int main(){
    cin>>n>>m;//n存点数，m存边数
    memset(g,0x3f,sizeof(g));//将点之间的距离的每一个值设置成很大的数，此知识点之前讲过
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b]=min(g[a][b],c);//有效解决多条边的问题，保留最短边
    }
    cout<<dijkstra()<<endl;
    return 0;
}
```



## 堆优化Dijkstra算法      主要用于稀疏图

思路：
	由于朴素Dij算法中的第4部反应在代码中是：每次从头到尾遍历Dist数组来找出距离起点最近的顶点，复杂度为O(n)。该操作非常的耗时。由于只是每次取出距离最短的（权重最小）点，此时考虑小根堆来存储，即可用O(1)完成此操作。

### 时间复杂度：

​	查找距离最近且未确定最短距离的顶点：O(mlogn)
​	加入集合S：O(n)
​	更新距离：O(m)
​	所以总的时间复杂度为: O(mlogn)

### 模板

```C++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 1e6+10;

using namespace std;
using PII = pair<int, int>;

int n,m;
int head[N], e[N], w[N], ne[N], idx;	//邻接表存稀疏图
int dist[N];							
bool status[N];

void add(int a, int b, int c)			//c 为 a->b 的边的权重
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = head[a];
    head[a] = idx++;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII> > heap;  //定义一个小根堆
    
    heap.push({0, 1});  // first表示起点到当前点的距离  second表示当前点的编号， 源点加入堆中
    dist[1] = 0;	    // 初始化源点到自己的距离为 0
    
    while(heap.size())
    {
        auto t = heap.top();  // 拿到距离最近且未确认最小距离的点
        
        heap.pop();
        
        int ver = t.second, distance = t.first;
        
        if(status[ver]) continue;	//由于存在重边，会存在重复判断，此操作可以省去判断已确认了最短距离的点
        status[ver] = true;			//当前点加入确认最小距离集合
        
        for(int i = head[ver]; ~i; i = ne[i])	//用当前点跟新所有能到达的点距源点的距离
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});		//节点j的距离被更新了，说明当前j到源点的距离需要加入堆中来考察，可能堆中已有了j到源点的距离值但是比当前值大，如果当前值在后续中不被更新了，那说明当前值就是最小值，那就一定会被取出（小根堆特性）使用。旧值则成为冗余数据。由于每个点到源点的初始距离都是"正无穷"，若一个点到源点的距离始终没有被更小的值更新，也就不需要加入堆中考察。
            }
        }
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}


int main()
{
    cin >> n >> m;
    memset(head, -1, sizeof head);
    while(m--)
    {
        int a,b,c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    
    cout << dijkstra() << endl;
    
    return 0;
}
```





## Bellman-Ford算法 用于带负权或是有负环的图

思路：

 Bellman-Ford 算法的核心思想是利用动态规划的思想，从源点出发进行多轮松弛操作，每次操作遍历所有边，更新从源点到其它节点的最短距离。当进行 V-1 轮松弛之后，最终得到了从源点到其它节点的最短距离。

时间复杂度：

​	O(mn)

模板代码：

```c++
//通用模板，只求到点n的最短路

//n:点数  m:边数
int n, m;

//dist[i] 存储 起点->点i 的最短距离
int  dist[N];

//bellman每轮要遍历所有边，所以任意存储方式都可,这里采用最简单的存边方式
struct Edge{			
    // 点a 指向 点b 的边权重为 w
    int a, b, w;
}

// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
int bellman_ford()
{
    //初始化
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 如果第n次迭代仍然会松弛三角不等式，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < m; j ++ )
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if (dist[b] > dist[a] + w)
            {	
                dist[b] = dist[a] + w;
             
                if(i == n - 1)
                {
                    cout << "有负权回路" << endl;
                }
            }
        }
    }
    
    //除特殊说明,否则在mian中做值判断更为保险 if(dist[n] > 0x3f3f3f3f / 2)  bellman中 正无穷值会改变，判断		时用同一数量级数即可
    return dist[n];
}


//当限定最多通过 k 条边到达点 n 的最短路径时
....
int backup[N];   //定义备份数组
...
    
     for (int i = 0; i < n; i ++ )
    {
     //在每轮松弛所有边前保存上一轮松弛完的状态，在接下来的松弛操作中始终通过原始状态判断，避免了
     //在松弛操作单次循环内部发生状态改变后，其改变后的状态传递到下一轮循环中，影响最终结果。也就是
     //避免了串联的情况发生
        memcpy(backup, dist, sizeof dist); 
        
        for (int j = 0; j < m; j ++ )
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if (dist[b] > backup[a] + w)
            {	
                dist[b] = backup[a] + w;
                if(i == n - 1)
                {
                    cout << "有负权回路" << endl;
                    return ...;
                }
            }
        }
    }

....
      
```





## SPFA  对bellman算法的优化，避免了对所有边的遍历

思路：

引用BFS思想，当队列不为空一直循环，每轮将路径值改变的点放入队列中，因为只有某点的值改变，其出度的所有点的值才可能会发生改变。避免了bellman中每轮对所有边的遍历。

复杂度:

一般：O(m)  最坏: O(nm)

```C++
const int N = ...;  //依题意
int n;      // 总点数
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储每个点到1号点的最短距离
bool st[N];     // 存储每个点是否在队列中

// 求1号点到n号点的最短路距离，如果从1号点无法走到n号点则输出impossible
int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true;

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        st[t] = false;	//取出后取消标记

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q.push(j);
                    st[j] = true;	//加入队列后，打上标记
                }
            }
        }
    }

    
   	// 这句留在 mian函数中判断更为保险 if (dist[n] == 0x3f3f3f3f) ....;
    return dist[n];
}

//判断负环回路版本
const int N = ...;  //依题意
int n;      // 总点数
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储每个点到1号点的最短距离
int 
bool st[N];     // 存储每个点是否在队列中

// 求1号点到n号点的最短路距离，如果从1号点无法走到n号点则输出impossible
int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true;

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        st[t] = false;	//取出后取消标记

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q.push(j);
                    st[j] = true;	//加入队列后，打上标记
                }
            }
        }
    }

    
   	// 这句留在 mian函数中判断更为保险 if (dist[n] == 0x3f3f3f3f) ....;
    return dist[n];
}

```

