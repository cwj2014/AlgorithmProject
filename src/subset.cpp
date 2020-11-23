#include "algorithm_impl_test.h"

//求子集其实和组合差不多，也是在一堆数据里求满足条件的真子集


/*给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例:

输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/
static vector<vector<int>> subsets(int n, int k){
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int start, int end)> subsetsCore = [&](int start, int end){
        if(cur.size() == k){
            ret.push_back(cur);
            return;
        }
        for(int i=start; i<=end; i++){
            cur.push_back(i);
            subsetsCore(i+1, end);
            cur.pop_back();
        }
    };
    subsetsCore(1, n);
    
    return ret;
}

/*给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]*/
static vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int, int, int)> subsetCore = [&](int start, int end, int l){//求子集中包含l个元素的子集
        if(cur.size() == l){
            ret.push_back(cur);
            return;
        }
        for(int i=start; i<end; i++){
            cur.push_back(nums[i]);
            subsetCore(i+1, end, l);
            cur.pop_back();
        }
    };
    for(int l = 0; l <= nums.size(); l++){//集合里的数据个数
       subsetCore(0, nums.size(), l);
    }
    return ret;
}

/*给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。
输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]*/

static vector<vector<int>> subsetsWithRepet(vector<int>& nums) {
    //sort except repet
    sort(nums.begin(), nums.end());
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int, int, int)> subsetCore = [&](int start, int end, int l){//求子集中包含l个元素的子集
        if(cur.size() == l){
            ret.push_back(cur);
            return;
        }
        for(int i=start; i<end; i++){
            if(i > start && nums[i-1] == nums[i]) continue;
            cur.push_back(nums[i]);
            subsetCore(i+1, end, l);
            cur.pop_back();
        }
    };
    for(int l = 0; l <= nums.size(); l++){//集合里的数据个数
       subsetCore(0, nums.size(), l);
    }
    return ret;
}


void findSubSetsTest(){
    cout << "subsets(4, 2)" << endl;
    printArray(subsets(4, 2));

    cout << "subsets([1,2,3])" << endl;
    vector<int> v1{1, 2, 3};
    printArray(subsets(v1));

    cout << "subsets([1, 2, 2])" << endl;
    vector<int> v2{1, 2, 2};
    printArray(subsetsWithRepet(v2));
}


