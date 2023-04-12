# 堆 heap

​	这里指手写堆通过数组 heap[N] 模拟一颗完全二叉树，非STL中的堆。

​	这里只需记住**核心操作上调和下调**即可。

## 主要操作

​	 1.插入一个数

​	 2.求集合当中的最小值

​	 3.删除最小值

​	 4.删除任意一个元素

​	 5.修改任意一个元素



堆排示例代码

```C++
//这里建立的是小根堆,也就是父结点小于左右孩子，整颗树根结点为最小值
//大根堆则相反
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010;

int heap[N], Size;

void down(int idx)        
{
    int t = idx;
    if(2 * idx <= Size && heap[2 * idx] < heap[t]) 
        t = 2 * idx;   	  //左孩子存在且值比父节点小
    if(2 * idx + 1 <= Size && heap[2 * idx + 1] < heap[t]) 
        t = 2 * idx + 1;  //右孩子存在且值比当前最小节点小
    if(t != idx)		 //父节点是否为最小节点
    {
        swap(heap[t], heap[idx]);    //父节点和最小孩子节点交换值
        down(t);				   //递归此过程直到父节点的值位于正确位置	
    }
}

int main()
{
    int m,n;
    scanf("%d%d", &n, &m);
    Size = n;
    for(int i = 1; i <= n; ++i)
        scanf("%d", &heap[i]);
    for(int i = n/2; i; i--) down(i);   // 建堆
    while(m--)					      // 打印前m个最小元素	
    {
        printf("%d ", heap[1]);
        heap[1] = heap[Size--];
        down(1);
    }
    return 0;
}
```

 

模拟堆

```C++
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010;

int heap[N], Size;

void down(int idx)    // 核心操作上调
{
    int t = idx;
    if(2 * idx <= Size && heap[2 * idx] < heap[t]) t = 2 * idx;
    if(2 * idx + 1 <= Size && heap[2 * idx + 1] < heap[t]) t = 2 * idx + 1;
    if(t != idx)
    {
        swap(heap[t], heap[idx]);
        down(t);
    }
}

void up(int idx)       //核心操作上调
{
    while(idx / 2 && heap[idx] < heap[idx / 2])
    {
        swap(heap[idx], heap[idx / 2]);
        idx >> 1;
    }
}

int main()
{
    int m,n;
    scanf("%d%d", &n, &m);
    Size = n;
    for(int i = 1; i <= n; ++i)
        scanf("%d", &heap[i]);
    for(int i = n/2; i; i--) down(i);
    while(m--)
    {
        printf("%d ", heap[1]);
        heap[1] = heap[Size--];
        down(1);
    }
    return 0;
}
```

