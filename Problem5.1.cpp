#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Calculator {
private:
    stack<int> st;

    bool isDigit(char ch) {
        return (ch >= '0' && ch <= '9');
    }

public:
    int evaluate(string s) {
        int result = 0;
        int number = 0;
        int sign = 1;

        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];

         
            if (ch == ' ')
                continue;

          
            if (isDigit(ch)) {
                number = number * 10 + (ch - '0');
            }

            else if (ch == '+' || ch == '-') {

    if (i == 0 || s[i - 1] == '(') {
        sign = (ch == '-') ? -1 : 1;
        continue;
    }

    result += sign * number;
    number = 0;

    sign = (ch == '+') ? 1 : -1;
}
            else if (ch == '(') {
                st.push(result);
                st.push(sign);

                result = 0;
                number = 0;
                sign = 1;
            }

            else if (ch == ')') {
                result += sign * number;
                number = 0;

                result *= st.top();
                st.pop();

                result += st.top();
                st.pop();
            }
        }

        result += sign * number;
        return result;
    }
};

int main() {
    Calculator calc;
    string expression;

    cout << "Enter expression: ";
    getline(cin, expression);

    cout << "Result = " << calc.evaluate(expression) << endl;

    return 0;
}