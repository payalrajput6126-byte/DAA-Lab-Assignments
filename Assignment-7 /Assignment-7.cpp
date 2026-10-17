
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of courses: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of courses must be greater than 0.\n";
        return 1;
    }

    cout << "Enter number of conflicts: ";
    cin >> m;

    if (m < 0 || m > n * (n - 1) / 2) {
        cout << "Invalid number of conflicts.\n";
        return 1;
    }

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter conflicting course pairs (0-based):\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            cout << "Invalid course pair.\n";
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    vector<int> color(n, -1);
    vector<bool> available(n, true);

    // Greedy graph coloring
    for (int u = 0; u < n; u++) {
        fill(available.begin(), available.end(), true);

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && color[v] != -1) {
                available[color[v]] = false;
            }
        }

        int c = 0;
        while (c < n && !available[c]) {
            c++;
        }

        color[u] = c;
    }

    int slots = *max_element(color.begin(), color.end()) + 1;

    cout << "\nExam Timetable:\n";

    for (int i = 0; i < n; i++) {
        cout << "Course " << i
             << " -> Slot " << color[i] + 1 << '\n';
    }

    cout << "\nTotal exam slots required: "
         << slots << '\n';

    return 0;
}
