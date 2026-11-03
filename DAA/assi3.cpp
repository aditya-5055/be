// dp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, W;

    // Input number of items
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> value(n);

    // Input weights
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    // Input values
    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    // Input knapsack capacity
    cout << "Enter knapsack capacity: ";
    cin >> W;

    // Create DP table
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {

            // Check if current item fits in the knapsack
            if (weight[i - 1] <= w) {

                // Maximum of taking or not taking the item
                dp[i][w] = max(
                    dp[i - 1][w],
                    value[i - 1] + dp[i - 1][w - weight[i - 1]]
                );
            }
            else {
                // Item does not fit
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print maximum value
    cout << "\nMaximum value in Knapsack = " << dp[n][W];

    return 0;
}

// Time Complexity: O(n × w)
// Space Complexity: O(n × w)


// branch and bound

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;
};

struct Node {
    int level;
    int profit;
    int weight;
    double bound;
};

// Sort items by value/weight ratio
bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Calculate upper bound
double calculateBound(Node u, int n, int W, vector<Item>& items) {

    // If weight exceeds capacity
    if (u.weight >= W)
        return 0;

    double profitBound = u.profit;
    int totalWeight = u.weight;
    int j = u.level + 1;

    // Add complete items
    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    // Add fraction of the next item for calculating bound
    if (j < n) {
        profitBound += (W - totalWeight) * items[j].ratio;
    }

    return profitBound;
}

int knapsack(int W, vector<Item>& items) {

    int n = items.size();

    // Sort according to value/weight ratio
    sort(items.begin(), items.end(), compareItems);

    queue<Node> q;

    // Create root node
    Node root = {-1, 0, 0, 0};
    root.bound = calculateBound(root, n, W, items);

    q.push(root);

    int maxProfit = 0;

    while (!q.empty()) {

        Node current = q.front();
        q.pop();

        // All items are processed
        if (current.level == n - 1)
            continue;

        // Next item index
        int nextLevel = current.level + 1;

        // -------- TAKE the item --------
        Node take;
        take.level = nextLevel;
        take.weight = current.weight + items[nextLevel].weight;
        take.profit = current.profit + items[nextLevel].value;

        if (take.weight <= W && take.profit > maxProfit)
            maxProfit = take.profit;

        take.bound = calculateBound(take, n, W, items);

        if (take.bound > maxProfit)
            q.push(take);

        // -------- DON'T TAKE the item --------
        Node notTake;
        notTake.level = nextLevel;
        notTake.weight = current.weight;
        notTake.profit = current.profit;
        notTake.bound = calculateBound(notTake, n, W, items);

        if (notTake.bound > maxProfit)
            q.push(notTake);
    }

    return maxProfit;
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter weight and value:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;

        // Calculate value/weight ratio
        items[i].ratio =
            (double)items[i].value / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    cout << "Maximum value: "
         << knapsack(W, items);

    return 0;
}