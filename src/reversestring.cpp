#include "algorithm_impl_test.h"

static void reverse(string& s, int begin, int end){
    for(int l = begin, r = end-1; l < r; l++, r--){
        char c = s[l];
        s[l] = s[r];
        s[r] = c;
    }
}
//翻转句子，并删除多余空格
//I am a student.=> student. a am I
string reverseWords(string s){
    int len = s.length();
    reverse(s, 0, len);
    int index = 0;
    for(int start = 0; start < len; start++){
        if(s[start] != ' '){
            if(index != 0){
                s[index++] = ' ';
            }
            int end = start;
            while(end < len && s[end] != ' '){
                s[index++] = s[end++];
            }
            reverse(s, index - (end - start), index);
            start = end;
        }
    }
    s.erase(s.begin() + index, s.end());
    return s;
}
//翻转句子,句子中没有多空格
//I am a student.=> I ma a .tneduts
string reverseWords2(string s){
    int len = s.length();
    for(int start = 0; start < len; start++){
        if(s[start] != ' '){
            int end = start;
            while(end < len && s[end] != ' '){
                end++;
            }
            //s.substr(start, end-start) 就是定位到的单词
            reverse(s, start, end);
            start = end;
        }
    }
    return s;
}

/**
 * 给定一个字符串，要求把字符串前面的若干个字符移动到字符串的尾部，如把字符串“abcdef”前面的2个字符'a'和'b'移动到字符串的尾部，
 * 使得原字符串变成字符串“cdefab”。请写一个函数完成此功能，要求对长度为n的字符串操作的时间复杂度为 O(n)，空间复杂度为 O(1)。
 */ 
string reverseString(string s, int k){
    //abc => cba, first part reverse
    //def => fed, sencode part reverse
    //cbafed => defabc, all reverse reach the need result
    int len = s.length();
    reverse(s, 0, k);
    reverse(s, k, len);
    reverse(s, 0, len);
    return s;
}

/**
 * 长度小于k，全部翻转
 * 长度小于等于2k，翻转前边k个字符，剩余的字符顺利保持不变
 * 如： abcdefghijklmn，k ＝ 2
 * bacdfeghjiklnm
 */ 
string reverseString2(string s, int k){
    int len = s.length();
    for(int i = 0; i < len; i+=2*k){
        if(len - i < k){
            reverse(s, i, len);
        }else{
            reverse(s, i, i+k);
        }
    }
    return s;
}


void stringReverseTest(){
    cout << "reverseWords(\"I am a student.\")" << reverseWords("I am a student.") << endl;
    cout << "reverseWords2(\"aakk is a middleschool student.\")" << reverseWords2("aakk is a middleschool student.") << endl;
    cout << "reverseString(\"abcdefg\", 2)" << reverseString("abcdefg", 2) << endl;
    cout << "reverseString2(\"abcdefghijklmn\", 2)" << reverseString2("abcdefghijklmn", 2) << endl;
}
