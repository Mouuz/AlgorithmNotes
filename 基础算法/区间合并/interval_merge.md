区间合并

问题描述：对于给定的多个范围区间，将其中有交叉的两两区间合并为一个区间。

模板：

```c++
using pair<int,int> PII
    ....
    ....
    
void merge(vector<PII> &segs)
{
    vector<PII> res;
    //先将所有区间按左端点从小到大排序
    sort(segs.begin(), segs.end());
    
    //最开始定义一个无穷小到无穷小的区间，以便后续更新维护的区间范围值
    //这里具体的值取决于题目所给的数据范围
    int bg = -2e9, ed = -2e9;   

    for(auto seg : segs)
    {
        //如果维护的区间最右端点和当前遍历的区间最左端点无交集，
        //则说明维护的区间不可能再和任意区间有交集，可加入结果集中。
    	if(ed < seg.first)
        {
            //注意这里要检查是否是设定的初始区间
            if(bg != -2e9)res.push_back({bg,ed});
            
            //当前维护的区间加入结果集后，更新其为当前遍历的区间范围
            bg = seg.first; ed = seg.end;
        }else{
            //
            ed = max(ed, seg.second);
        }
    }
    
    //当循环退出时，当前维护的区间还未加入结果集中
    if(bg != -2e9) res.push_back({bg,ed});
    
    //最后将结果写回原区间范围中
    segs = res;
}
```

