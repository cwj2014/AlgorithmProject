#include "algorithm_impl_test.h"

//组合这类型的算法就是从数组中，找出等于目标值，首先让数组有序，数组中的数据有重复和非重复两种情况
//也能要求结果数组能否重复使用原数组中的值要求，任何条件一变，则实现的算法都有所不同
//还有明确要求几个数之和等于／最接近目标值，原数据有重复需要去重复，这类组合题型需要先排序再做首尾指针移动法
//并在计算过程中直接去重复

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
    function<void(int,int, int)> dfs = [&](int start, int end, int target){
        if(target <= 0){
            if(0 == target){
                ret.push_back(cur);
            }
            return;
        }
        for(int i=start; i<end; i++){
            cur.push_back(candidates[i]);
            //能重复使用数字
            dfs(i, end, target - candidates[i]);
            cur.pop_back();
        }
    };
    dfs(0, candidates.size(), target);

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
/*给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在三个元素 a，b，c，
使得 a + b + c 的值与 target 相等？找出所有满足条件且不重复的三元组。
先确定一个a， 再对b、c做首尾指针移动
*/
static vector<vector<int>> threeeSum(vector<int>& nums, int target){
    int n = nums.size();
    vector<vector<int>> ret;
    if(n < 3){
        return ret;
    }
    std::sort(nums.begin(), nums.end());
    for(int i=0; i<n-2; i++){
        if(i>0 && nums[i] == nums[i-1]) continue;
        int j = i+1;
        int k = n-1;
        int sum = target - nums[i];
        while(j < k){
            int temp = nums[j] + nums[k];
            if(temp == sum){
                ret.push_back(vector<int>{nums[i], nums[j], nums[k]});
                while(j+1<k && nums[j+1] == nums[j]){
                    j++;
                }
                j++;
                while(j<k-1 && nums[k-1] == nums[k]){
                    k--;
                }
                k--;
            }else if(temp > sum){
                while(j<k-1 && nums[k-1] == nums[k]){
                    k--;
                }
                k--;
            }else{
                while(j+1<k && nums[j+1] == nums[j]){
                    j++;
                }
                j++;
            }
        }
    }
    return ret;
}

/*给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，
使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
先确定a，b 再对c、d做首尾指针移动
*/
static vector<vector<int>> fourSum(vector<int>& nums, int target){
    int n = nums.size();
    vector<vector<int>> ret;
    if(n < 4){
        return ret;
    }
    std::sort(nums.begin(), nums.end());
    for(int i=0; i<n-3; i++){
        if(i>0 && nums[i] == nums[i-1]) continue;
        for(int j=i+1; j<n-2; j++){
            if(j>i+1&&nums[j] == nums[j-1]) continue;
            int m = j+1;
            int k = n-1;
            int sum = target - nums[i] - nums[j];
            while(m < k){
                int temp = nums[m] + nums[k];
                if(temp == sum){
                    ret.push_back(vector<int>{nums[i], nums[j], nums[m], nums[k]});
                    while(m+1<k && nums[m+1] == nums[m]){
                        m++;
                    }
                    m++;
                    while(m<k-1 && nums[k-1] == nums[k]){
                        k--;
                    }
                    k--;
                }else if(temp > sum){
                    while(m<k-1 && nums[k-1] == nums[k]){
                        k--;
                    }
                    k--;
                }else{
                    while(m+1<k && nums[m+1] == nums[m]){
                        m++;
                    }
                    m++;
                }
            }
        }
    }
    return ret;
}

/*给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，
使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。*/

static int threeSumClosest(vector<int>& nums, int target){
    int n = nums.size();
    if(n < 3){
        return INT32_MAX;
    }
    std::sort(nums.begin(), nums.end());
    int closest = nums[n-1] + nums[n-2] + nums[n-3];
    for(int i=0; i<n-2;  i++){
        if(i>0&&nums[i] == nums[i-1]) continue;
        int m = i+1;
        int k = n-1;
        int sum = target - nums[i];
        while(m < k){
            int temp = nums[m] + nums[k];
            if(temp == sum){
                closest = target;
                goto end;
            }else{
                int dif1 = std::abs(closest - target);
                int dif2 = std::abs(temp - sum);
                if(dif2 < dif1){
                    closest = temp + nums[i];
                }
                if(temp > sum){
                    while(m<k-1 && nums[k-1] == nums[k]){
                        k--;
                    }
                    k--;
                }else{
                    while(m+1<k && nums[m+1] == nums[m]){
                        m++;
                    }
                    m++;
                }
            }
        }
    }
end:
    return closest;
}


void combinationTest(){
    cout << "combinationSum([2,3,6,7], 7)" << endl;
    vector<int> v1{2,3,6,7};
    printArray(combinationSum(v1, 7));

    cout << "combinationSum2([10,1,2,7,6,1,5], 8)" << endl;
    vector<int> v2{10,1,2,7,6,1,5};
    printArray(combinationSum2(v2, 8));
}
