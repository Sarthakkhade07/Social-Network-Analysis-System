#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> userID;
vector<string> idToUser;
vector<vector<int>> graph;

int getUserID(const string& name) {
    if (userID.count(name)) return userID[name];
    int id = userID.size();
    userID[name] = id;
    idToUser.push_back(name);
    graph.push_back({});
    return id;
}

// BFS Shortest Path
void shortestPath(string start, string target) {
    if (!userID.count(start) || !userID.count(target)) {
        cout << "User not found\n";
        return;
    }

    int s = userID[start];
    int t = userID[target];

    vector<int> parent(graph.size(), -1);
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);

                if (v == t) {
                    vector<int> path;
                    for (int cur = t; cur != -1; cur = parent[cur])
                        path.push_back(cur);
                    reverse(path.begin(), path.end());

                    cout << "Shortest Path: ";
                    for (int id : path)
                        cout << idToUser[id] << " ";
                    cout << "\n";
                    return;
                }
            }
        }
    }
    cout << "No connection found\n";
}

// Mutual Friends
void mutualFriends(string a, string b) {
    if (!userID.count(a) || !userID.count(b)) {
        cout << "User not found\n";
        return;
    }

    int u = userID[a];
    int v = userID[b];

    unordered_set<int> fa(graph[u].begin(), graph[u].end());
    bool found = false;

    cout << "Mutual Friends: ";
    for (int x : graph[v]) {
        if (fa.count(x)) {
            cout << idToUser[x] << " ";
            found = true;
        }
    }
    if (!found) cout << "None";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        string u, v;
        cin >> u >> v;
        int id1 = getUserID(u);
        int id2 = getUserID(v);
        graph[id1].push_back(id2);
        graph[id2].push_back(id1);
    }

    while (true) {
        string cmd;
        cin >> cmd;

        if (cmd == "PATH") {
            string a, b;
            cin >> a >> b;
            shortestPath(a, b);
        }
        else if (cmd == "MUTUAL") {
            string a, b;
            cin >> a >> b;
            mutualFriends(a, b);
        }
        else if (cmd == "EXIT") {
            break;
        }
    }
    return 0;
}

