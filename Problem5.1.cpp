#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Calculator {
private:
    stack<int> st;

    // Check if character is a digit
    bool isDigit(char ch) {
        return (ch >= '0' && ch <= '9');
    }

public:
    int evaluate(string s) {
        int result = 0;   // current computed result
        int number = 0;   // current number being built
        int sign = 1;     // current sign (+1 or -1)

        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];

            // ignore spaces
            if (ch == ' ')
                continue;

            // build multi-digit numbers
            if (isDigit(ch)) {
                number = number * 10 + (ch - '0');
            }

            // handle + and -
            else if (ch == '+' || ch == '-') {

                // handle unary operator (like -(2+3))
                if (i == 0 || s[i - 1] == '(') {
                    sign = (ch == '-') ? -1 : 1;
                    continue;
                }

                // add previous number to result
                result += sign * number;
                number = 0;

                // update sign
                sign = (ch == '+') ? 1 : -1;
            }

            // opening bracket: save current state
            else if (ch == '(') {
                st.push(result);
                st.push(sign);

                result = 0;
                number = 0;
                sign = 1;
            }

            // closing bracket: resolve sub-expression
            else if (ch == ')') {
                result += sign * number;
                number = 0;

                // restore sign and previous result
                result *= st.top();
                st.pop();

                result += st.top();
                st.pop();
            }
        }

        // add last pending number
        result += sign * number;

        return result;
    }
};

// Main function to test calculator
int main() {
    Calculator calc;
    string expression;

    cout << "Enter expression: ";
    getline(cin, expression);

    cout << "Result = " << calc.evaluate(expression) << endl;

    return 0;
}
