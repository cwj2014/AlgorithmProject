#include "algorithm_impl_test.h"

//组合这类型的算法就是从数组中，找出等于目标值，首先让数组有序，数组中的数据有重复和非重复两种情况
//也能要求结果数组能否重复使用原数组中的值要求，任何条件一变，则实现的算法都有所不同

/*给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
示例 1：

输入：candidates = [2,3,6,7], target = 7,
所求解集为：
[
  [7],
  [2,2,3]
]*/
static vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    std::sort(candidates.begin(), candidates.end());
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int,int, int)> combinationSumCore = [&](int start, int end, int sum){
        if(sum >= target){
            if(sum == target){
                ret.push_back(cur);
            }
            return;
        }
        for(int i=start; i<end; i++){
            cur.push_back(candidates[i]);
            //能重复使用数字
            combinationSumCore(i, end, sum+candidates[i]);
            cur.pop_back();
        }
    };
    combinationSumCore(0, candidates.size(), 0);

    return ret;
}


/*给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。

所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 
示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]*/

static vector<vector<int>> combinationSum2(vector<int>& candidates, int target){
    std::sort(candidates.begin(), candidates.end());
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int,int, int)> combinationSumCore = [&](int start, int end, int sum){
        if(sum >= target){
            if(sum == target){
                ret.push_back(cur);
            }
            return;
        }
        for(int i=start; i<end; i++){
            //去除相同的数字，因为如果前边已经有这个数字满足条件，不去重会有重复组合
            if(i > start && candidates[i] == candidates[i-1]) continue;
            cur.push_back(candidates[i]);
            //不能重复使用数字
            combinationSumCore(i+1, end, sum+candidates[i]);
            cur.pop_back();
        }
    };
    combinationSumCore(0, candidates.size(), 0);

    return ret;
}


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
static vector<vector<int>> combine(int n, int k){
    vector<vector<int>> ret;
    vector<int> cur;
    function<void(int start, int end)> combineCore = [&](int start, int end){
        if(cur.size() == k){
            ret.push_back(cur);
            return;
        }
        for(int i=start; i<=end; i++){
            cur.push_back(i);
            combineCore(i+1, end);
            cur.pop_back();
        }
    };
    combineCore(1, n);
    
    return ret;
}



void combinationTest(){
    cout << "combinationSum([2,3,6,7], 7)" << endl;
    vector<int> v1{2,3,6,7};
    printArray(combinationSum(v1, 7));

    cout << "combinationSum2([10,1,2,7,6,1,5], 8)" << endl;
    vector<int> v2{10,1,2,7,6,1,5};
    printArray(combinationSum2(v2, 8));

    cout << "combine(4, 2)" << endl;
    printArray(combine(4, 2));
}
