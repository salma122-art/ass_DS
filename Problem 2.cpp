#include <iostream>
#include <string>
using namespace std;
// Time Complexity:
// Best Case: O(1)
// Average Case: O(log n)
// Worst Case: O(n)

int searchRotatedArray(int arr[], int n, int target, int &comparisons) {
    int left = 0, right = n - 1;
    comparisons = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if current middle element is the target
        comparisons++;
        if (arr[mid] == target)
            return mid;

        // When duplicates exist at left, mid, and right,
        // we cannot determine which side is sorted clearly
        // so we shrink the search space
        comparisons++;
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;
            right--;
            continue;
        }

        // Check if left half is sorted
        comparisons++;
        if (arr[left] <= arr[mid]) {

            // If target lies in the sorted left half, search left side
            comparisons++;
            if (target >= arr[left] && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }

        // Otherwise, right half must be sorted
        else {

            // If target lies in the sorted right half, search right side
            comparisons++;
            if (target > arr[mid] && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    // Target not found in array
    return -1;
}

void runTest(int arr[], int n, int target, string testName) {
    cout << "\n===== " << testName << " =====" << endl;

    int comparisons = 0;
    int result = searchRotatedArray(arr, n, target, comparisons);

    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not Found" << endl;

    cout << "Comparisons: " << comparisons << endl;
}

int main() {

    int arr1[] = {5, 6, 7, 1, 2, 3, 4};
    int arr2[] = {2, 2, 2, 3, 4, 2};
    int arr3[] = {1};
    int arr4[] = {4, 5, 6, 7, 0, 1, 2};
    int arr5[] = {10, 12, 15, 18, 2, 5, 8};

    int n;

    // Test cases for different scenarios
    n = sizeof(arr1) / sizeof(arr1[0]);
    runTest(arr1, n, 2, "Target in rotated array");

    n = sizeof(arr2) / sizeof(arr2[0]);
    runTest(arr2, n, 3, "Array with duplicates");

    n = sizeof(arr3) / sizeof(arr3[0]);
    runTest(arr3, n, 1, "Single element array");

    n = sizeof(arr4) / sizeof(arr4[0]);
    runTest(arr4, n, 10, "Target not present");

    n = sizeof(arr5) / sizeof(arr5[0]);
    runTest(arr5, n, 5, "Another rotated array");

    return 0;
}
