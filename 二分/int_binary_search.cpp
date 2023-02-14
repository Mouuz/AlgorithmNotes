//整数二分查找模版

//1.划分的范围为 [l,mid] 和 [mid + 1, r], 也即是说 mid 在左半区间
//  此时 更新策略中 mid的值无需 +1
    while(l < r)
    {
        int mid = l + (r - l >> 1);
        //check mid
        if(check mid){
            r = mid;
        }else{
            l = mid + 1;
        }
    }

//2.划分的范围为 [l,mid - 1] 和 [mid, r], 也即是说 mid 在右半区间
//  此时 更新策略中 mid的值必需 +1 否则死循环
    while(l < r)
    {
        int mid = l + (r - l + 1 >> 1);
        //check mid
        if(check mid){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
