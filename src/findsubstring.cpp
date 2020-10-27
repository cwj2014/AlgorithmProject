#include "algorithm_impl_test.h"
 #include <math.h>


class FindCommonTool{
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
    static string find_suffix_common_depth_first(vector<string> v){
        int size = v.size();
        if(size < 1){
            return "";
        }
        string common = v[0];
        for(int i=1; i<size; i++){
            common = suffix_common(common, v[i]);
            if(common.length() == 0){
                break;
            }
        }
        return common;
    }
    static string find_suffix_common_devide(vector<string> v){
        int size = v.size();
        if(size < 1){
            return "";
        }
        return find_suffix_common_devide_core(v, 0, size-1);
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
    static string find_suffix_common_devide_core(vector<string> v, int begin, int end){
        if(begin == end){
            return v[begin];
        }else{
            int mid = (begin + end) / 2;
            string firstHalf = find_suffix_common_devide_core(v, begin, mid);
            string secondHalf = find_suffix_common_devide_core(v, mid+1, end);
            return suffix_common(firstHalf, secondHalf);
        }
    }
    static string suffix_common(string& s1, string& s2){
        int commonSuffixLen = 0;
        int m = s1.length();
        int n = s2.length();
        for(int i = m - 1, j = n - 1 ; i >= 0 && j >= 0; i--, j--){
            if(s1[i] != s2[j]){
                break;
            }
            commonSuffixLen++;
        }
        return s1.substr(m - commonSuffixLen, commonSuffixLen);
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
                if(l == 0){//一个字符肯定是回文
                    dp[i][j] = 1;
                }else if(l == 1){//两个字符两同则是回文
                    dp[i][j] = (s[i] == s[j]);
                }else{//两个以上是回文则dp[i+1][j-1]是回文且扩展后的两个字符相等
                    dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);
                }
                //更新开始和结束索引
                if(dp[i][j] && j - i > end - start){
                    start = i;
                    end = j;
                }
            }
        }
        return s.substr(start, end - start + 1);//[start, end]区间，end - start + 1表示长度
    }
    static bool isPalindromHeadTailMethod(string s){
        int n = s.length();
        int l= 0;
        int r = n - 1;
        bool result = true;
        while(l < r && s[l] == s[r]){
            l++;
            r--;
        }
        return (l >= r);
    }
    static bool isPalindromCenterExtend(string s){
        int n = s.length();
        bool isOdd = (n % 2 > 0);
        int l = n / 2 - 1;
        int r = n / 2;
        if(isOdd){
            l = r;
        }
        while(l>=0 && r<n && s[l] == s[r]){
            l--;
            r++;
        }
        if(l>=0 && r<n){
            return false;
        }
        return true;
    }
    static bool isPalindromNumberToString(int x){
        if(x < 0){
            return false;
        }
        return isPalindromHeadTailMethod(std::to_string(x));
    }
    static bool isPalindromNumberReverseNumber(int x){
        if(x < 0){
            return false;
        }
        int m = x;
        int result = 0;
        while(m) {
            int n = m % 10;
            if(INT32_MAX/10 < result || (INT32_MAX/10 == result &&  n > INT32_MAX % 10)){
                break;
            }
            result = result * 10 + n;
            m /= 10;
        }
        return (x == result);
    }
    static bool isPalindromNumber(int x){
        if(x < 0){
            return false;
        }
        const vector<int> sizeTable{9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, INT32_MAX};
        int len = 0;
        for(int i=0; i<sizeTable.size(); i++){
            if(x <= sizeTable[i]){
                len = i + 1;
                break;
            }
        }
        int m = x;
        while(m && len > 1){
            int n = m % 10;
            int d = (int)pow(10, len - 1);
            int k = m / d;
            if(n != k){
                break;
            }
            m = m % d;
            m /= 10;
            len -= 2;
        }
        if(m && len>1){
            return false;
        }
        return true;
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
    cout << "FindCommonTool::find_prefix_common_depth_first(vector<string>{\"flower\",\"flow\",\"flight\"})" 
         << FindCommonTool::find_prefix_common_depth_first(vector<string>{"flower","flow","flight"}) << endl;
    cout << "FindCommonTool::find_prefix_common_devide(vector<string>{\"flower\",\"flow\",\"flight\"})" 
         << FindCommonTool::find_prefix_common_devide(vector<string>{"flower","flow","flight"}) << endl;

    cout << "FindCommonTool::find_suffix_common_depth_first(vector<string>{\"flower\",\"flower\",\"flighter\"})" 
         << FindCommonTool::find_suffix_common_depth_first(vector<string>{"flower","flower","flighter"}) << endl;
    cout << "FindCommonTool::find_suffix_common_devide(vector<string>{\"flower\",\"flow\",\"flight\"})" 
         << FindCommonTool::find_suffix_common_devide(vector<string>{"flower","flow","flight"}) << endl;

    cout << "FindCommonTool::find_prefix_common_depth_first(vector<string>{\"dog\",\"racecar\",\"car\"})" 
         << FindCommonTool::find_prefix_common_depth_first(vector<string>{"dog","racecar","car"}) << endl;
    cout << "FindCommonTool::find_prefix_common_devide(vector<string>{\"dog\",\"racecar\",\"car\"})" 
         << FindCommonTool::find_prefix_common_devide(vector<string>{"dog","racecar","car"}) << endl;

    cout << "PalindromTool::find_longest_palindrom(\"babaddsafaafdebada\")"<< PalindromTool::find_longest_palindrom("babaddsafaafdebada") <<endl;
    cout << "PalindromTool::find_longest_palindrom_dynamic(\"babaddsafaafdebada\")"<< PalindromTool::find_longest_palindrom_dynamic("babaddsafaafdebada")<<endl;

    cout << "PalindromTool::isPalindromHeadTailMethod(\"abba\")" << PalindromTool::isPalindromHeadTailMethod("abba") << endl;
    cout << "PalindromTool::isPalindromHeadTailMethod(\"aba\")" << PalindromTool::isPalindromHeadTailMethod("aba") << endl;
    cout << "PalindromTool::isPalindromHeadTailMethod(\"abaddaae\")" << PalindromTool::isPalindromHeadTailMethod("abaddaae") << endl;

    cout << "PalindromTool::isPalindromCenterExtend(\"abba\")" << PalindromTool::isPalindromCenterExtend("abba") << endl;
    cout << "PalindromTool::isPalindromCenterExtend(\"aba\")" << PalindromTool::isPalindromCenterExtend("aba") << endl;
    cout << "PalindromTool::isPalindromCenterExtend(\"abaddaae\")" << PalindromTool::isPalindromCenterExtend("abaddaae") << endl;

    cout << "PalindromTool::isPalindromNumberReverseNumber(12)" << PalindromTool::isPalindromNumberReverseNumber(12) << endl;
    cout << "PalindromTool::isPalindromNumberReverseNumber(121)" << PalindromTool::isPalindromNumberReverseNumber(121) << endl;
    cout << "PalindromTool::isPalindromNumberReverseNumber(1221)" << PalindromTool::isPalindromNumberReverseNumber(1221) << endl;
    cout << "PalindromTool::isPalindromNumberReverseNumber(-1221)" << PalindromTool::isPalindromNumberReverseNumber(-1221) << endl;

    cout << "PalindromTool::isPalindromNumber(12)" << PalindromTool::isPalindromNumber(12) << endl;
    cout << "PalindromTool::isPalindromNumber(121)" << PalindromTool::isPalindromNumber(121) << endl;
    cout << "PalindromTool::isPalindromNumber(1221)" << PalindromTool::isPalindromNumber(1221) << endl;
    cout << "PalindromTool::isPalindromNumber(-1221)" << PalindromTool::isPalindromNumber(-1221) << endl;
}