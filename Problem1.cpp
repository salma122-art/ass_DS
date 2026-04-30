
#include <iostream>
using namespace std;

int main() {

    // ===== Problem 1: Recursive Function =====
    // T(n) = T(n-1) + T(n-2)
    // This creates exponential growth
    // Time Complexity: O(2^n)


    // ===== Problem 1: Nested Loops =====
    // Outer loop: i /= 2 → log n
    // Inner loop: j *= 2 → log n
    // Total: O(log^2 n)


    cout << "Complexity analysis is written in comments." << endl;

    return 0;
}
