#include <iostream>
#include <algorithm>
using namespace std;
// Time Complexity:
//
// Sorting Phase:
// Left Half (Bubble Sort):
// Worst/Average Case: O(n^2)
// Because bubble sort compares adjacent elements repeatedly
//
// Right Half (Selection Sort):
// O(n^2)
// Because we scan remaining elements to find maximum each time
//
// Overall Sorting Complexity: O(n^2)
//
// Searching Phase:
// Linear Search: O(n)
// Because we may scan all elements in worst case
//
// Final Complexity:
// Dominated by sorting → O(n^2)

int comparisons = 0;
int swaps = 0;

// Bubble Sort (ascending) for left half
// Used to arrange first half in increasing order
void bubbleSort(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        for (int j = start; j < end - (i - start); j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

// Selection Sort (descending) for right half
// Used to arrange second half in decreasing order
void selectionSortDesc(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        int maxIdx = i;

        for (int j = i + 1; j <= end; j++) {
            comparisons++;
            if (arr[j] > arr[maxIdx]) {
                maxIdx = j;
            }
        }

        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
            swaps++;
        }
    }
}

// Linear search to find target in full array
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// Main process: sort halves then search
void process(int arr[], int n, int target, string testName) {

    comparisons = 0;
    swaps = 0;

    cout << "\n===== " << testName << " =====" << endl;

    int mid = n / 2;

    // Sort left half (ascending)
    bubbleSort(arr, 0, mid - 1);

    // Sort right half (descending)
    selectionSortDesc(arr, mid, n - 1);

    // Search for target
    int result = linearSearch(arr, n, target);

    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not Found" << endl;

    cout << "Comparisons: " << comparisons << endl;
    cout << "Swaps: " << swaps << endl;
}

int main() {

    int arr1[] = {5, 1, 8, 3, 10, 2, 6};
    int arr2[] = {7, 2, 9, 1, 6, 4, 3};
    int arr3[] = {4, 10, 2, 8, 1, 6, 3};
    int arr4[] = {9, 2, 7, 1, 5, 3, 6};
    int arr5[] = {2, 2, 5, 5, 1, 1, 3};

    int n = 7;

    process(arr1, n, 10, "Target at bitonic point");
    process(arr2, n, 6, "Target in left half");
    process(arr3, n, 6, "Target in right half");
    process(arr4, n, 100, "Target not present");
    process(arr5, n, 5, "Array with duplicates");

    return 0;
