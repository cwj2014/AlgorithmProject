#include "algorithm_impl_test.h"
#include <functional>

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
}