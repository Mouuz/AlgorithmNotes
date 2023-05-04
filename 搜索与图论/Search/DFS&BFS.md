# DFS

1.数据结构

​	栈（函数栈，由系统提供，也可以改写成循环迭代版本手动压栈出栈）

2.空间复杂度

​	O(h) (h 为树的高度)

3.时间复杂度

​	完全二叉树 O(N）N：结点总数      邻接表图（V+E） V:顶点数  E：边数

### 不同于BFS的特性

​	不具有找到最短路特性

思路：

1. 从当前点出发，同时将当前点标记为已访问。
2. 依次遍历该结点的每一个相邻点，如果邻居节点未被访问，则递归遍历该邻居节点并将其标记为已访问。如果邻居节点已经被访问，则返回到当前节点。
3. 遍历完该节点的所有邻居节点后，返回上一个节点，继续遍历上一层节点未访问的邻居节点，若无则继续向上一个节点返回。（回溯）
4. 当所有节点都被访问过，遍历结束



DFS和BFS在一般情况下（待搜索对象中所有节点只访问一次），都通过一个**标记数组**来记录要访问的对象是否被访问过





例题：全排列 

```C++
#include<iostream>

using namespace std;

const int N = 10;
int path[N], n;
bool check[N];				//标记数组
void dfs(int u)
{
    if(u == n)				//递归结束条件，依据具体问题不同而不同
    {
        for(int i = 0; i < n; ++i)
            printf("%d ", path[i]);
        printf("\n");
        return;
    }
    
    for(int i = 1; i <= n; ++i)
    {
        if(!check[i])
        {
            path[u] = i;        //修改状态
            check[i] = true;	//
            
            dfs(u + 1);			//进入下一层	
            
            path[u] = 0;		//回溯并恢复现场，这是dfs要特别注意的地方
            check[i] = false;	//
        }
    }
    
    
}

int main()
{
    scanf("%d",&n);
    dfs(0);
    return 0;
}
```



## 剪枝

1.可行性剪枝

​	在dfs过程中做判断，当当前路线一定不可行或者与约束条生冲突时直接返回到上一层，也就是剪枝。

2.最优性剪枝

​	在搜索过程中，如果已经找到了一个局部最优解，那么就可以停止继续搜索，或者判断哪些状态已经不可能得到更优	  	解，进行剪枝。

3.重复状态剪枝

​	在搜索过程中，记录已访问过的状态，避免重复搜索同一状态，或者发现当前状态与已知状态相同，就可以剪枝。

4.搜索深度剪枝 

​	在搜索过程中，如果已搜索到一定深度后，发现这个分支已经不能再得到最优解，那么可以剪枝，不再进行搜索。这种	剪枝方式适用于深度不太深的情况。





# BFS

1.数据结构

​	队列，STL queue或者数组模拟都可

2.空间复杂度

​	O(W)  对于图来说，最宽层的节点数为 W，因此空间复杂度为 O(W)。对于树来说，因为树的结构比较特殊，最多只有	一层节点的数目为 W，因此空间复杂度也为 O(W)。

3.时间复杂度

​	树：O(N)      图：O(N+E)   稠密图：O(N^2)

4.思路

1. 首先选取一个未被访问过的节点作为起始节点。
2. 将起始节点放入队列（一般为先进先出的队列）中。
3. 从队列中取出队首元素（当前节点），并访问其相邻的、未被访问过的节点，并标记这些节点已被访问。
4. 将这些相邻节点放入队列尾部。
5. 重复步骤3和步骤4直到队列为空。

### 示例1

走迷宫https://www.acwing.com/problem/content/846/

```c++
#include<iostream>
#include<queue>

using namespace std;
using PII = pair<int,int>;

const int N = 110;

int g[N][N];	//存储迷宫
int d[N][N];	//标记数组，此题还用作记录当前节点到起点的距离
int n,m;

int bfs()
{
    queue<PII> q;	//开辟队列
    q.push({0,0});	//将起点放入队列中
    
    d[0][0] = 0;    //定义起点到起点自己的距离为0
    
    while(q.size())
    {
        auto temp = q.front();	//从队列中取出起点
        q.pop();
        
        int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
        
        //对当前点的下一步四个行动方向依次遍历，对合法的下一步节点对其进行标记并记录距离
        for(int i = 0; i < 4; ++i)	
        {
            int x = temp.first + dx[i], y = temp.second + dy[i];	//计算下一步结点的坐标
            if(x >= 0 && x < n && y >=0 && y < m && g[x][y] == 0 && d[x][y] == -1)
            {//下一步结点坐标在迷宫内且能通行并且未被访问过时，就是合法下一节点
                d[x][y] = d[temp.first][temp.second] + 1;
                q.push({x,y});
            }
        }
    }
    
    return d[n - 1][m - 1];  //返回目标节点到起点的距离
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            d[i][j] = -1;		//初始化标记数组，用-1表明该坐标点未被访问过
        }
        
    cout << bfs();
    return 0;
}
```



### 示例2

八数码https://www.acwing.com/problem/content/847/

```C++
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>

//这题巧妙的使用字符串来表示节点状态，方便了后续一系列操作
//使用哈希表来存储每个节点状态（字符串）相对应的距离值

using namespace std;

int bfs(string start)
{
    string end = "12345678x";       //定义终点目标状态
    
    queue<string> q;                
    unordered_map<string, int> d;   //存储每种状态所对应的距离值
    
    q.push(start);                  //初始状态放入队列中
    d[start] = 0;                   //初始状态距离初始状态的距离值为0
    
    while(q.size())
    {
        auto t = q.front();
        q.pop();
        
        int distance = d[t];
        
        //如果当前从队列中取出的状态和目标状态相同表明走到了终点，返回此时对应的距离值
        if(t == end) return distance;   
        
        int k = t.find('x');                        //找到'x'在一维字符串中的坐标
        int x = k / 3, y = k % 3;                   //转化为在矩阵中的(x,y)坐标
        int dx[4] = {0,-1,0,1}, dy[4] = {-1,0,1,0};
        for(int i = 0; i < 4; ++i)                  //向上下左右四个方向依次移动
        {
            int a = x + dx[i], b = y + dy[i];           
            if(a >= 0 && a < 3 && b >= 0 && b < 3)  //检查移动后的坐标在矩阵中是否合法未出界
            {
                swap(t[k], t[a * 3 + b]);           //合法的话就交换'x'和向某个方向移动后的坐标值
                                                    //二维坐标转换一维坐标  x * m(列的大小) + y
                
                //交换后形成新的字符串,若果该新字符串未被遍历过则放入队列中,同时更新该新字符串距原状态的距离值
                if(d.find(t) == d.end())            
                {
                    q.push(t);
                    d[t] = distance + 1;
                }
                
                //还原未移动时的状态,因为是以某个点为原点向四个方向移动,那么在向任意方向移动后需要退回原点，再向剩余未移动的方向进行尝试,才能保证正确性
                swap(t[k], t[a * 3 + b]);           
            }
        }
    }
    return -1;
}

int main()
{
    string state;
    for(int i = 0; i < 9; ++i)
    {
        char c;
        cin >> c;
        state += c;
    }
    
    cout << bfs(state) << endl;
    return 0;
}
```

