
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

int n, cost[10][10];
int bestCost = INT_MAX;
vector<int> bestPath;

struct Node {
    int city;
    int visited[10];
    vector<int> path;
    int totalCost;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.totalCost > b.totalCost;
    }
};

void tsp() {
    priority_queue<Node, vector<Node>, Compare> pq;

    Node start{};
    start.city = 0;
    start.totalCost = 0;
    start.path.push_back(0);

    for (int i = 0; i < n; i++)
        start.visited[i] = 0;

    start.visited[0] = 1;
    pq.push(start);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.totalCost >= bestCost)
            continue;

        if (current.path.size() == n) {
            // Check whether the last city can return to city 0
            if (cost[current.city][0] > 0) {
                int finalCost =
                    current.totalCost + cost[current.city][0];

                if (finalCost < bestCost) {
                    bestCost = finalCost;
                    bestPath = current.path;
                    bestPath.push_back(0);
                }
            }
            continue;
        }

        for (int next = 0; next < n; next++) {
            if (!current.visited[next] &&
                cost[current.city][next] > 0) {

                Node child = current;
                child.city = next;
                child.visited[next] = 1;
                child.totalCost += cost[current.city][next];
                child.path.push_back(next);

                if (child.totalCost < bestCost)
                    pq.push(child);
            }
        }
    }
}

int main() {
    cout << "Enter number of cities (max 10): ";
    cin >> n;

    if (n < 2 || n > 10) {
        cout << "Number of cities must be between 2 and 10.\n";
        return 1;
    }

    cout << "Enter cost matrix (0 if no route):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];

            if (cost[i][j] < 0) {
                cout << "Costs must be non-negative.\n";
                return 1;
            }
        }
    }

    tsp();

    if (bestCost == INT_MAX) {
        cout << "No complete tour exists.\n";
    } else {
        cout << "\nMinimum travel cost: " << bestCost;
        cout << "\nOptimal route: ";

        for (int city : bestPath)
            cout << city << " ";

        cout << endl;
    }

    return 0;
}
