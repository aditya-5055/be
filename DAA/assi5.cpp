// partation Quick Sort Code

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int st, int end, vector<int> &ans) {
    
    int idx = st - 1;
    int ele = ans[end];  // Pivot

    for (int j = st; j < end; j++) {
        if (ans[j] <= ele) {
            idx++;
            swap(ans[j], ans[idx]);
        }
    }

    // Put pivot in its correct position
    swap(ans[idx + 1], ans[end]);

    return idx + 1;
}

void quick(int st, int end, vector<int> &ans) {
    if (st < end) {
        int pivotidx = solve(st, end, ans);
        quick(st, pivotidx - 1, ans);
        quick(pivotidx + 1, end, ans);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> ans;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans.push_back(x);
    }

    quick(0, n - 1, ans);

    for (auto it : ans) {
        cout << it << " ";
    }

    return 0;
}

// Randomized Quick Sort Code

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Partition function
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];

    int idx = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            idx++;
            swap(arr[idx], arr[j]);
        }
    }

    swap(arr[idx + 1], arr[high]);

    return idx + 1;
}

// Randomized partition
int randomizedPartition(vector<int>& arr, int low, int high) {

    // Select a random index
    int randomIndex = low + rand() % (high - low + 1);

    // Move random pivot to the end
    swap(arr[randomIndex], arr[high]);

    // Use normal partition
    return partition(arr, low, high);
}

// Randomized Quick Sort
void randomizedQuickSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int pivotIndex = randomizedPartition(arr, low, high);

        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Initialize random number generator
    srand(time(0));

    randomizedQuickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}