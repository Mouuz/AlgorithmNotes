# Hash

拉链法

```C++
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
    int k = (x % N + N) % N;
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

```

