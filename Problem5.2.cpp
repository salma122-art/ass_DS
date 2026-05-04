#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class NextGreaterCircular {
private:
    vector<int> nums;

public:
    NextGreaterCircular(const vector<int>& arr) {
        nums = arr;
    }

    vector<int> solve() {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st; // store indices of potential next greater elements

        for (int i = 2 * n - 1; i >= 0; i--) {
            int index = i % n;

            // Remove all smaller or equal elements
            // because they cannot be "next greater"
            while (!st.empty() && nums[st.top()] <= nums[index]) {
                st.pop();
            }

            // Only fill result during first pass (i < n)
            if (i < n) {
                result[index] = st.empty() ? -1 : nums[st.top()];
            }

            // Push current index for future comparisons
            st.push(index);
        }

        return result;
    }
};

// Main function to test solution
int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    NextGreaterCircular solver(nums);
    vector<int> result = solver.solve();

    cout << "Output: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i != result.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
