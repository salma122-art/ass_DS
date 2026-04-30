
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
    // ===== OOP / Clean Code Notes =====
    // 1. Code is well structured and easy to read
    // 2. Meaningful comments explain logic
   // 3. Simple naming used for clarity
  // 4. No unnecessary complexity or duplication


    cout << "Complexity analysis is written in comments." << endl;

    return 0;
}
