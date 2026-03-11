#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool isNum(string& token){
        return !(token=="+"||token=="-"||token=="*"||token=="/");
    }
    int calculate(int num1,int num2,string token){
        int result=0;
        switch(token[0]){
            case '+':
                result=num1+num2;
                break;
            case '-':
                result=num1-num2;
                break;
            case '*':
                result=num1*num2;
                break;
            case '/':
                result=num1/num2;
                break;
        }
        return result;
    }

    int evalRPN(vector<string>& tokens) {
        stack<int>stk;
        int n=tokens.size();
        for(int i=0;i<n;i++){
            string token=tokens[i];
            if(isNum(token)){
                stk.push(atoi(token.c_str()));
            }else{
                int num2=stk.top();
                stk.pop();
                int num1=stk.top();
                stk.pop();
                int result=calculate(num1,num2,token);
                stk.push(result);
            }
        }
        return stk.top();
    }
};