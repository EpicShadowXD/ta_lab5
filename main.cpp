#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

double buffonNeedle(int num_trials, double needle_length, double line_distance) {
    int hits = 0;
    for (int i = 0; i < num_trials; ++i) {
        double d = (rand() / (double)RAND_MAX) * (line_distance / 2);
        double theta = (rand() / (double)RAND_MAX) * M_PI / 2;
        if (d <= (needle_length / 2) * sin(theta)) {
            hits++;
        }
    }
    return (2.0 * needle_length * num_trials) / (line_distance * hits);
}

double targetSquareCircle(int num_trials, double radius) {
    int hits = 0;
    for (int i = 0; i < num_trials; ++i) {
        double x = (rand() / (double)RAND_MAX) * radius;
        double y = (rand() / (double)RAND_MAX) * radius;
        if (x * x + y * y <= radius * radius) {
            hits++;
        }
    }
    return (double)hits / num_trials;
}

double monteCarloIntegration(int num_trials, double a, double b, double (*func)(double)) {
    double sum = 0.0;
    for (int i = 0; i < num_trials; ++i) {
        double x = a + (rand() / (double)RAND_MAX) * (b - a);
        sum += func(x);
    }
    return ((b - a) / num_trials) * sum;
}

double f(double x) {
    return sin(x);
}

bool findElementGreaterThanMean(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    double mean = (double)sum / arr.size();

    srand(time(0));
    for (int i = 0; i < arr.size(); ++i) {
        int index = rand() % arr.size();
        if (arr[index] > mean) {
            return true;
        }
    }
    return false;
}

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void removeRandomNodes(int num_nodes_to_remove) {
        srand(time(0));
        vector<bool> removed(V, false);

        for (int i = 0; i < num_nodes_to_remove; ++i) {
            int node = rand() % V;
            if (!removed[node]) {
                removed[node] = true;
                cout << "Removing node: " << node << endl;
            } else {
                --i; // retry if the node is already removed
            }
        }

        cout << "Remaining nodes:" << endl;
        for (int i = 0; i < V; ++i) {
            if (!removed[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

bool containsSubstring(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    srand(time(0));

    for (int i = 0; i < n - m + 1; ++i) {
        bool found = true;
        for (int j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

class NQueens {
    int N;
    vector<int> board;

    bool isSafe(int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
                return false;
            }
        }
        return true;
    }

    bool solveRecursive(int row) {
        if (row == N) return true;  // all queens placed successfully

        vector<int> available;
        for (int col = 0; col < N; ++col) {
            if (isSafe(row, col)) {
                available.push_back(col);
            }
        }

        while (!available.empty()) {
            int idx = rand() % available.size();
            int col = available[idx];
            available.erase(available.begin() + idx);  // remove chosen column
            board[row] = col;
            if (solveRecursive(row + 1)) return true;
            board[row] = -1;  // backtrack
        }

        return false;
    }

public:
    NQueens(int N) : N(N), board(N, -1) {}

    bool solve() {
        srand(time(0));
        for (int attempts = 0; attempts < 100; ++attempts) {  // try up to 100 times
            if (solveRecursive(0)) return true;
            board.assign(N, -1);  // reset board
        }
        return false;
    }

    void printSolution() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
};


int main() {
    // srand(time(0));
    // int num_trials = 1000000;
    // double needle_length = 1.0;
    // double line_distance = 1.0;

    // cout << "Estimated value of Pi: " << buffonNeedle(num_trials, needle_length, line_distance) << endl;
    
    // srand(time(0));
    // int num_trials = 1000000;
    // double radius = 1.0;

    // cout << "Probability: " << targetSquareCircle(num_trials, radius) << endl;

    // srand(time(0));
    // int num_trials = 1000000;
    // double a = 0.0;
    // double b = M_PI;

    // cout << "Approximate integral: " << monteCarloIntegration(num_trials, a, b, f) << endl;
    
    // vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // cout << "Element greater than mean found: " << (findElementGreaterThanMean(arr) ? "Yes" : "No") << endl;
    
    // Graph g(10);
    // g.addEdge(0, 1);
    // g.addEdge(0, 2);
    // g.addEdge(1, 3);
    // g.addEdge(3, 4);
    // g.addEdge(4, 5);
    // g.addEdge(5, 6);
    // g.addEdge(6, 7);
    // g.addEdge(7, 8);
    // g.addEdge(8, 9);
    // g.addEdge(9, 0);

    // int nodes_to_remove = 3;
    // g.removeRandomNodes(nodes_to_remove);

    // string text = "this is a simple example";
    // string pattern = "example";

    // cout << "Pattern found: " << (containsSubstring(text, pattern) ? "Yes" : "No") << endl;
    
    int N = 6;
    NQueens queens(N);

    if (queens.solve()) {
        queens.printSolution();
    } else {
        cout << "No solution found" << endl;
    }

}
