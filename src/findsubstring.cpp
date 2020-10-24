#include "algorithm_impl_test.h"


class FindPrefixCommonTool{
public:
    //深度优先遍历
    static string find_prefix_common_depth_first(vector<string> v){
        int size = v.size();
        if(size < 1){
            return "";
        }
        string common = v[0];
        for(int i=1; i<size; i++){
            common = prefix_common(common, v[i]);
            if(common.length() == 0){
                break;
            }
        }
        return common;
    }
    //分治法
    static string find_prefix_common_devide(vector<string> v){
        int size = v.size();
        if(size < 1){
            return "";
        }
        return find_prefix_common_devide_core(v, 0, size-1);
    }
private:
    static string find_prefix_common_devide_core(vector<string> v, int begin, int end){
        if(begin == end){
            return v[begin];
        }else{
            int mid = (begin + end) / 2;
            string firstHalf = find_prefix_common_devide_core(v, begin, mid);
            string secondHalf = find_prefix_common_devide_core(v, mid+1, end);
            return prefix_common(firstHalf, secondHalf);
        }
    }
    static string prefix_common(string& s1, string& s2){
        int len = std::min(s1.length(), s2.length());
        int i;
        for(i=0; i<len; i++){
            if(s1[i] != s2[i]){
                break;
            }
        }
        return s1.substr(0, i);
    }
};

class PalindromTool{
public:
    static string find_longest_palindrom(string s){
        int start = 0;
        int end = 0;
        //获取palindrom， 如果比之前的palindrom长，更新start和end
        auto f = [&](string s, int left, int right){
            while(left >= 0 && right < s.length() && s[left] == s[right]){
               left--;
               right++;
            }
            left += 1;
            right -= 1;
            if(right - left > end - start){
                end = right;
                start = left;
            }
        };
        for(size_t i=0; i<s.length(); i++){
             f(s, i, i);//奇数扩展
             f(s, i, i+1);//偶数扩展
        }
        return s.substr(start, end - start + 1);//[start, end]区间
    }
    static string find_longest_palindrom_dynamic(string s){
        std::size_t  n = s.length();
        vector<vector<int>> dp(n, vector<int>(n)); //dp[n][n], dp[i][j] 表示s.substr(i, j-i+1)是不是回文
        int start = 0;
        int end = 0;
        for(std::size_t l=0; l<n; l++){
            for(std::size_t i=0, j=i+l; j<n; i++, j++){
                if(l == 0){//
                    dp[i][j] = 1;
                }else if(l == 1){
                    dp[i][j] = (s[i] == s[j]);
                }else{
                    dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);
                }
                if(dp[i][j] && j - i> end - start){
                    start = i;
                    end = j;
                }
            }
        }
        return s.substr(start, end - start + 1);//[start, end]区间
    }
private:
    static pair<int, int> findpalindrom(string& s, size_t left, size_t right){
        while(left >= 0 && right < s.length() && s[left] == s[right]){
            left--;
            right++;
        }
        return make_pair<int, int>(left+1, right-1);
    }
};


void findSubStringTest(){
    cout << "FindPrefixCommonTool::find_prefix_common_depth_first(vector<string>{\"flower\",\"flow\",\"flight\"})" 
         << FindPrefixCommonTool::find_prefix_common_depth_first(vector<string>{"flower","flow","flight"}) << endl;
    cout << "FindPrefixCommonTool::find_prefix_common_devide(vector<string>{\"flower\",\"flow\",\"flight\"})" 
         << FindPrefixCommonTool::find_prefix_common_devide(vector<string>{"flower","flow","flight"}) << endl;

    cout << "FindPrefixCommonTool::find_prefix_common_depth_first(vector<string>{\"dog\",\"racecar\",\"car\"})" 
         << FindPrefixCommonTool::find_prefix_common_depth_first(vector<string>{"dog","racecar","car"}) << endl;
    cout << "FindPrefixCommonTool::find_prefix_common_devide(vector<string>{\"dog\",\"racecar\",\"car\"})" 
         << FindPrefixCommonTool::find_prefix_common_devide(vector<string>{"dog","racecar","car"}) << endl;

    cout << "PalindromTool::find_longest_palindrom(\"babaddsafaafdebada\")"<< PalindromTool::find_longest_palindrom("babaddsafaafdebada") <<endl;
    cout << "PalindromTool::find_longest_palindrom_dynamic(\"babaddsafaafdebada\")"<< PalindromTool::find_longest_palindrom_dynamic("babaddsafaafdebada")<<endl;
}