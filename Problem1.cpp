#include <iostream>
using namespace std;

/*
========================================
Problem 1 - Complexity Analysis
========================================

1) Recursive Function:

int hello_recursive(int n) {
    if (n <= 1) return 1;
    return hello_recursive(n-1) + hello_recursive(n-2);
}

Analysis:
- The function makes two recursive calls at each step:
    T(n) = T(n-1) + T(n-2)
- This leads to exponential growth similar to Fibonacci recursion.
- The recursion tree expands rapidly.

Time Complexity:
O(2^n)

----------------------------------------

2) Nested Loops:

void test(int n) {
    int i = n;
    while (i > 1) {
        int j = 1;
        while (j < i) {
            j *= 2;
        }
        i /= 2;
    }
}

Analysis:
- Outer loop:
    i is divided by 2 each iteration → runs O(log n)

- Inner loop:
    j doubles each time until it reaches i → O(log i)
    which is approximately O(log n)

Total Complexity:
O(log n * log n) = O((log n)^2)

========================================
*/

int main() {
    cout << "Problem 1: Complexity Analysis completed (see comments)." << endl;
    return 0;
}
