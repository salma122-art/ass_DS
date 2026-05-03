#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class NextGreaterElement {
private:
    vector<int> nums;

public:
    NextGreaterElement(vector<int> arr) {
        nums = arr;
    }

    vector<int> solve() {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st;

        for (int i = 2 * n - 1; i >= 0; i--) {
            int index = i % n;

            while (!st.empty() && nums[st.top()] <= nums[index]) {
                st.pop();
            }

            if (i < n) {
                if (!st.empty())
                    result[index] = nums[st.top()];
                else
                    result[index] = -1;
            }

            st.push(index);
        }

        return result;
    }

    void printResult() {
        vector<int> ans = solve();

        cout << "[";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
            if (i != ans.size() - 1)
                cout << ", ";
        }
        cout << "]";
    }
};

int main() {
    int n;
    cout<<"Enter the size of the Array:";
    cin >> n;

    vector<int> nums(n);
    cout<<"Enter the elemenets:";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    NextGreaterElement obj(nums);
    obj.printResult();

    return 0;
}