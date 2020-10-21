#include "algorithm_impl_test.h"
#include <vector>

/*
* 基础版本二分查找，数组中的数据升序且没有重复
* 存在则返回目标数组下标，不存在返回－1
*/
static int binarySearch(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){//当right<left退出，即：right ＝ left － 1
        int mid = left + (right - left)/2;
        if(v[mid] == target){
            return mid;
        }else if(v[mid] > target){
            right = mid - 1;
        }else{//v[mid] < target
            left = mid + 1;
        }
    }
    return -1;
}
/*
* 基础版本二分查找升级，数组中的数据升序且存在重复
* 存在则返回目标数组满足条件最小下标，不存在返回－1
*/
static int binarySearchMin(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){//当right<left退出，即：right ＝ left － 1
        int mid = left + (right - left)/2;
        if(v[mid] >= target){
            right = mid - 1;
        }else{//v[mid] < target
            left = mid + 1;
        }
    }
    if(left < n && v[left] == target){
        return left;
    }else{
        return -1;
    }
}
/*
* 基础版本二分查找升级，数组中的数据升序且存在重复
* 存在则返回目标数组满足条件最大下标，不存在返回－1
*/
static int binarySearchMax(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){//当right<left退出，即：right ＝ left － 1
        int mid = left + (right - left)/2;
        if(v[mid] <= target){
            left = mid + 1;
        }else{//v[mid] > target
            right = mid - 1;
        }
    }
    if(right >= 0 && v[right] == target){
        return right;
    }else{
        return -1;
    }
}
/**
 * 基础版本二分查找变异，数组中的数据升序且存在重复
 * 查找第一个大于等于目标数据的位置，如果不存在返回－1
 */ 
static int binarySearchFirstEqualLargerThanTarget(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(v[mid] >= target){//第一个等于大于的，使right不断后退
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    //这里为什么返回left呢，退出循环的条件是right<left，所以v[right] < v[left], 
    //第一个大于等于目标数据则是v[left]
    if(left < n && v[left] >= target){
        return left;
    }else{
        return -1;
    }
}
/**
 * 基础版本二分查找变异，数组中的数据升序且存在重复
 * 查找最后一个小于等于目标数据的位置，如果不存在返回－1
 */ 
static int binarySearchLastEqualSmallerThanTarget(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(v[mid] <= target){//最后一个等于小于的，使left不断前进
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    //这里为什么返回right呢，退出循环的条件是right<left，所以v[right] < v[left], 
    //最后一个小于等于目标数据则是v[right]
    if(right >= 0 && v[right] <= target){
        return right;
    }else{
        return -1;
    }
}

/**
 * 基础版本二分查找变异，数组中的数据升序且存在重复
 * 查找第一个大于目标数据的位置，如果不存在返回－1
 */ 
static int binarySearchFirstLargerThanTarget(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(v[mid] <= target){//小于等于都收缩left
            left = mid + 1; 
        }else{
            right = mid - 1;
        }
    }
    //这里为什么返回left呢，退出循环的条件是right<left，所以v[right] < v[left], 
    //第一个大于目标数据则是v[left]
    if(left < n && v[left] > target){
        return left;
    }else{
        return -1;
    }
}

/**
 * 基础版本二分查找变异，数组中的数据升序且存在重复
 * 查找最后一个小于目标数据的位置，如果不存在返回－1
 */ 
static int binarySearchLastSmallerThanTarget(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(v[mid] >= target){//大于等于都收缩right
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
     //这里为什么返回right呢，退出循环的条件是right<left，所以v[right] < v[left], 
    //最后一个小于目标数据则是v[right]
    if(right >= 0 && v[right] < target){
        return right;
    }else{
        return -1;
    }
}

/**
 * 基础版本二分查找有序旋转数组，数组中的数据升序但是被通过未知点旋转且存在重复
 * 查找目标数据是否存在，如果不存在返回－1
 */ 
static bool binarySearchRotateArray(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(v[mid] == target){
            return true;
        }else if(v[mid] == v[left] && v[mid] == v[right]){
            left += 1;
            right -= 1;
        }else if(v[mid] < v[right]){//right part has order
            if(v[mid] < target && target <= v[right]){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }else{//left part has order
            if(v[mid] > target && target >= v[left]){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
    }
    return false;
}

/**
 * 基础版本二分查找有序旋转数组，数组中的数据升序但是被通过未知点旋转且不存在重复
 * 查找目标数据index，如果不存在返回－1
 */ 
static int binarySearchRotateNoRepetArray(std::vector<int> v, int target){
    int n = v.size();
    int left = 0;
    int right = n - 1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(v[mid] == target){
            return mid;
        }else if(v[mid] < v[right]){//right part has order
            if(v[mid] < target && target <= v[right]){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }else{//left part has order
            if(v[mid] > target && target >= v[left]){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
    }
    return -1;
}

void binarySearchTest(){
    std::cout << "//////////begin binarySearchTest/////////"<<std::endl;

    std::cout << "binarySearch(std::vector<int>{1, 3, 5, 6, 7, 9}, 3) = " << binarySearch(std::vector<int>{1, 3, 5, 6,7, 9}, 3) << std::endl;

    std::cout << "binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;
    std::cout << "binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;

    std::cout << "binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) = " << binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) << std::endl;
    std::cout << "binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) = " << binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) << std::endl;

    std::cout << "binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 5) = " << binarySearchMin(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 5) << std::endl;
    std::cout << "binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 5) = " << binarySearchMax(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 5) << std::endl;

    std::cout << "binarySearchFirstEqualLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchFirstEqualLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;
    std::cout << "binarySearchFirstEqualLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) = " << binarySearchFirstEqualLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) << std::endl;
    
    std::cout << "binarySearchLastEqualSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchLastEqualSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;
    std::cout << "binarySearchLastEqualSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) = " << binarySearchLastEqualSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) << std::endl;

    std::cout << "binarySearchFirstLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) = " << binarySearchFirstLargerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 6, 6, 6, 7, 9}, 6) << std::endl;
    
    std::cout << "binarySearchLastSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchLastSmallerThanTarget(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;

    std::cout << "binarySearchRotateArray(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) = " << binarySearchRotateArray(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 4) << std::endl;
    std::cout << "binarySearchRotateArray(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) = " << binarySearchRotateArray(std::vector<int>{1, 3, 3, 3, 5, 6, 7, 9}, 3) << std::endl;

    std::cout << "binarySearchRotateNoRepetArray(std::vector<int>{10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 9}, 5) = " << binarySearchRotateNoRepetArray(std::vector<int>{10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 9}, 5) << std::endl;
    std::cout << "binarySearchRotateNoRepetArray(std::vector<int>{10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 9}, 8) = " << binarySearchRotateNoRepetArray(std::vector<int>{10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 9}, 8) << std::endl;
    
    std::cout << "//////////end binarySearchTest/////////"<<std::endl;
}