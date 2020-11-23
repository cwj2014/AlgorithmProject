#include "algorithm_impl_test.h"
#include <functional>
#include <sstream>

//全排列最主要的方法就是采用回溯法求解， 存在不重复or重复数据的情况
//不重复进行全排列不需要考虑去重的情况， 但是存在重复数据的情况下就
//计算过程当中需要去重，题目稍做修改，解题的方法基本一样，但是去重的
//方法有很大不同。
//假设给定的数组是 "abc"，那么我们首先让 a 在第 0 位，再让 b 在第 0 位，再让 c 在第 0 位。
//a 在第 0 位，那么还剩 bc。我们先放 b 在第 1 位，再让 c 在第 1 位。
//b 在第 1 位，那么还剩 c。最终结果：abc。
//c 在第 1 位，那么还剩 b。最终结果：acb。
//b 在第 0 位，那么还剩 ac。我们先放 a 在第 1 位，再让 c 在第 1 位。
//a 在第 1 位，那么还剩 c。最终结果：bac。
//c 在第 1 位，那么还剩 a。最终结果：bca。
//c 在第 0 位，那么还剩 ba。我们先放 b 在第 1 位，再让 a 在第 1 位。
//b 在第 1 位，那么还剩 c。最终结果：cba。
//a 在第 1 位，那么还剩 a。最终结果：cab。

template<typename T>
static bool isNeedSwap(T& arr, int start, int end){
    for(int i = start; i < end; i++){
        if(arr[i] == arr[end]){
            return false;
        }
    }
    return true;
}

template<typename T>
static void allRangeCore(T& arr, vector<T>& ret, int start, int end, bool removeRepet){
    if(start == end){
        ret.push_back(arr);
        return;
    }
    for(int i = start; i < end; i++){
        if(removeRepet && !isNeedSwap(arr, start, i)){
           continue;
        }
        std::swap(arr[start], arr[i]);//与所有的元素进行交换，使其成为第start个元素
        allRangeCore(arr, ret, start+1, end, removeRepet); //对start＋1后面的的元素全排列
        std::swap(arr[i], arr[start]);//还原start和i位置上的元素 
    }
}


//给定一个没有重复string的序列，返回其所有可能的全排列。
static vector<string> allRangeNoRepet(string& s){
    vector<string> ret;

    allRangeCore<string>(s, ret, 0, s.length(), false);

    return ret;
}

//给定一个重复string的序列，返回其所有可能的全排列,但不能存在重复排列。
static vector<string> allRange(string& s){
    vector<string> ret;

    allRangeCore<string>(s, ret, 0, s.length(), true);

    return ret;
}

//给定一个 没有重复 数字的序列，返回其所有可能的全排列。
static vector<vector<int>> allRangeNoRepet(vector<int>& nums){
    vector<vector<int>> ret;

    allRangeCore<vector<int>>(nums, ret, 0, nums.size(), false);

    return ret;
}

//给定一个 有重复 数字的序列，返回其所有可能的全排列, 但不能存在重复排列。
static vector<vector<int>> allRange(vector<int>& nums){
    vector<vector<int>> ret;

    allRangeCore<vector<int>>(nums, ret, 0, nums.size(), true);

    return ret;
}


/*给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
"123"
"132"
"213"
"231"
"312"
"321"
给定 n 和 k，返回第 k 个排列。

给定 n 的范围是 [1, 9]。
给定 k 的范围是[1,  n!]。
示例 1:
输入: n = 3, k = 3
输出: "213"
示例 2:
输入: n = 4, k = 9
输出: "2314"
典型的求第k个字典序的排列， 这里如何保证求出来的全排列有序是个问题，因为我们前边求全排列是没有按字典序输出的？？？
*/
//求第k个排序工具
class KRangeTool{
public:
    static string getPermutationMinK(int n, int k){
        vector<int> factorial(n);
        factorial[0] = 1;
        for(int i=1; i<n; i++){
            factorial[i] = i * factorial[i-1];
        }
        vector<bool> visited(n+1, false);
        string s = "";
        //求第k个排列，即求[k－1]的排列， 
        //如“1234”第1个排列，即“1234”，
        //如“1234”第2个排列，即“1243”，
        //第6个排列，“1432”，第7个2134
        k--; 
        for(int i=n-1; i>=0; i--){
            int m = k / factorial[i];
            for(int j=1; j<=n; j++){
                if(visited[j]) continue;
                if(m-- == 0){
                    visited[j] = true;
                    s += (j+'0');
                    break;
                }
            }
            k %= factorial[i];
        }
        return s;
    }
    static string getPermutationMinK2(int n, int k){
        vector<bool> visited(n+1, false);
        vector<int> cur;
        function<void(int)> getPermutationMinK2Core = [&](int step){
            if(step == n){
                k--;
                return;
            }
            for(int i=1; i<=n; i++){
                if(visited[i]) continue;
                visited[i] = true;
                cur.push_back(i);
                getPermutationMinK2Core(step+1);
                if(k == 0){
                    break;
                }
                cur.pop_back();
                visited[i] = false;
            }
        };
        getPermutationMinK2Core(0);
        
        stringstream ss;
        for(auto& v: cur){
            ss<<v;
        }
        return ss.str();
    }
};




void allRangeTest(){
    cout << "allRangeNoRepet(\"abc\")" << endl;
    string s1 = "abc";
    printStrings(allRangeNoRepet(s1));
    cout << "allRange(\"acad\")" << endl;
    string s2 = "acad";
    printStrings(allRange(s2));

    cout << "allRangeNoRepet(vector<int>{1,2,3})" << endl;
    vector<int> v1{1,2,3};
    printArray(allRangeNoRepet(v1));
    cout << "allRange(vector<int>{1, 2, 1, 3})" << endl;
    vector<int> v2{1, 2, 1, 3};
    printArray(allRange(v2));

    cout<< "KRangeTool::getPermutationMinK(4, 9)" << KRangeTool::getPermutationMinK(4, 9) << endl;
    cout<< "KRangeTool::getPermutationMinK(4, 6)" << KRangeTool::getPermutationMinK(4, 6) << endl;
    cout<< "KRangeTool::getPermutationMinK(4, 7)" << KRangeTool::getPermutationMinK(4, 7) << endl;
    cout<< "KRangeTool::getPermutationMinK(3, 3)" << KRangeTool::getPermutationMinK(3, 3) << endl;

    cout<< "KRangeTool::getPermutationMinK2(4, 9)" << KRangeTool::getPermutationMinK2(4, 9) << endl;
    cout<< "KRangeTool::getPermutationMinK2(4, 6)" << KRangeTool::getPermutationMinK2(4, 6) << endl;
    cout<< "KRangeTool::getPermutationMinK2(4, 7)" << KRangeTool::getPermutationMinK2(4, 7) << endl;
    cout<< "KRangeTool::getPermutationMinK2(3, 3)" << KRangeTool::getPermutationMinK2(3, 3) << endl;
}