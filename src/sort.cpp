#include "algorithm_impl_test.h"

template<typename T>
void printArray(T* arr, int n){
    cout << "[";
    for(int i=0; i<n; i++){
        cout << arr[i];
        if(i != n-1){
            cout << ",";
        }
    }
    cout << "]" << endl;
}

//选择排序
template<typename T>
static void selectsort(T* arr, int n){
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j=i+1; j<n; j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        if(min != i){
            std::swap(arr[i], arr[min]);
        }
    }
}

//冒泡排序
template<typename T>
static void bubblesort(T* arr, int n){
    for(int i=0; i<n-1; i++){
        bool flag = true;
        for(int j=n-1; j>i; j--){
            if(arr[j] < arr[j-1]){//较小数上升
                std::swap(arr[j], arr[j-1]);
                flag = false;
            }
        }
        if(flag){//没有发生交换，说明已经都有序，退出循环
            break;
        }
    }
}

template<typename T>
static inline int quick_sort_divide(T* arr, int begin, int end){
    T x = arr[begin];
    int l = begin;
    int r = end;
    while(l < r){
        while(l<r&&arr[r] >= x) r--;
        if(l < r) arr[l++] = arr[r];
        while(l<r&&arr[l] <= x) l++;
        if(l < r) arr[r--] = arr[l];
    }
    arr[l] = x;
    return l;
}

//快速排序
template<typename T>
static void quicksort(T* arr, int begin, int end){
    if(begin < end){
        int pos = quick_sort_divide(arr, begin, end);
        quicksort(arr, begin, pos-1);
        quicksort(arr, pos+1, end);
    }
}

template<typename T>
static void quicksort(T* arr, int n){
    stack<pair<int,int>> s;
    s.push(std::make_pair(0, n-1));
    while(!s.empty()){
        pair<int,int> val = s.top();
        int l = val.first;
        int r = val.second;
        s.pop();
        int pos = quick_sort_divide(arr, l, r);
        if(l < pos - 1){//左半部分
            s.push(std::make_pair(l, pos-1));
        }
        if(r > pos + 1){//右半部分
            s.push(std::make_pair(pos+1, r));
        }
    }
}

//插入排序
template<typename T>
static void insertsort(T* arr, int n){
    for(int i=1; i<n; i++){
        T x = arr[i];
        int j;
        for(j = i - 1; j>=0 && arr[j] > x; j--){
            arr[j+1] = arr[j];
        }
        j++;
        arr[j] = x;
    }
}

//shell排序
template<typename T>
static void shellsort(T* arr, int n){
    for(int step = n/2; step > 0 ; step /= 2){
        for(int i = step; i<n; i++){
            T x = arr[i];
            int j;
            for(j = i - step; j>=0 && arr[j] > x; j -= step){
                arr[j+step] = arr[j];
            }
            j += step;
            arr[j] = x;
        }
    }
}


void sortTest(){
    {
        int arr[] = {1, 2, 8, 4, 5, 6, 3, 4, 5, 6, 9, 8, 7, 9};
        insertsort<int>(arr, 14);
        printArray(arr, 14);
    }
    {
        int arr[] = {1, 2, 8, 4, 5, 6, 3, 4, 5, 6, 9, 8, 7, 9};
        shellsort<int>(arr, 14);
        printArray(arr, 14);
    }
}
