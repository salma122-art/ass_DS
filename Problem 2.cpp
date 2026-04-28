#include <iostream>
using namespace std;

int comparisons = 0;


int search(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    comparisons = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        
        comparisons++;
        if (arr[mid] == target)
            return mid;

        comparisons++;
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;
            right--;
            continue;
        }

      
        comparisons++;
        if (arr[left] <= arr[mid]) {

            comparisons++;
            if (target >= arr[left] && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }

       
        else {
            comparisons++;
            if (target > arr[mid] && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    return -1;
}


void runTest(int arr[], int n, int target, string testName) {
    cout << "\n===== " << testName << " =====" << endl;

    int result = search(arr, n, target);

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

    // 1. Target in rotated array
    n = sizeof(arr1) / sizeof(arr1[0]);
    runTest(arr1, n, 2, "Target in rotated array");

    // 2. Duplicates case
    n = sizeof(arr2) / sizeof(arr2[0]);
    runTest(arr2, n, 3, "Array with duplicates");

    // 3. Single element case
    n = sizeof(arr3) / sizeof(arr3[0]);
    runTest(arr3, n, 1, "Single element array");

    // 4. Target not present
    n = sizeof(arr4) / sizeof(arr4[0]);
    runTest(arr4, n, 10, "Target not present");

    // 5. Another rotated array
    n = sizeof(arr5) / sizeof(arr5[0]);
    runTest(arr5, n, 5, "Another rotated array");

    return 0;
}
