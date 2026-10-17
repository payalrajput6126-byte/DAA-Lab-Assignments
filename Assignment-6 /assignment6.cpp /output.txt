
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    if (n < 1 || n > 100) {
        cout << "Invalid number of items. Enter 1 to 100.\n";
        return 1;
    }

    int weight[100], value[100];

    cout << "Enter weight and utility value of each item:\n";

    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];

        if (weight[i] <= 0 || value[i] < 0) {
            cout << "Invalid weight or utility value.\n";
            return 1;
        }
    }

    cout << "Enter truck capacity: ";
    cin >> W;

    if (W < 0 || W > 1000) {
        cout << "Capacity must be between 0 and 1000.\n";
        return 1;
    }

    int dp[101][1001] = {0};

    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum utility value: " << dp[n][W] << endl;

    // Find selected items
    int selected[100];
    int count = 0;
    int w = W;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected[count++] = i;
            w -= weight[i - 1];
        }
    }

    cout << "Selected items: ";

    if (count == 0) {
        cout << "None";
    } else {
        for (int i = count - 1; i >= 0; i--) {
            cout << selected[i] << " ";
        }
    }

    cout << endl;
    return 0;
}
